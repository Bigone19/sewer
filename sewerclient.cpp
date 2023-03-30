#include "sewerclient.h"
#include "ui_sewerclient.h"
#include "table.h"
#include "projectdlg.h"

#include <QDateTime>
#include <QBrush>
#include <QPixmap>
#include <QMenu>
#include <QInputDialog>

// combox defect name map [3/4/2023]
const unordered_map<string, int> g_mapDefectNameIdx =
{
	{"RB", 1}, {"OB", 2}, {"PF", 3}, {"DE", 4},
	{"FS", 5}, {"IS", 6}, {"RO", 7}, {"IN", 8},
	{"AF", 9}, {"BE", 10}, {"FO", 11}, {"GR", 12},
	{"PH", 13}, {"PB", 14}, {"OS", 15}, {"OP", 16},
	{"OK", 17}
};

SewerClient::SewerClient(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SewerClient)
	, m_isDetect(false)
{
	m_currTabIdx = 0;
	m_clsNames.clear();
	setDocxPath();

    ui->setupUi(this);
	ui->filePostion->setEnabled(false);
	ui->btnDetect->setEnabled(false);
	ui->btnSelectFile->setEnabled(false);
	ui->btnDocxOutput->setEnabled(false);
	ui->imgTabWidget->setTabVisible(0, false);
	ui->imgTabWidget->setFocusPolicy(Qt::NoFocus);
	// 设置 listWidget 对象的上下文菜单策略为自定义 [3/23/2023]
	ui->listWidgetProject->setContextMenuPolicy(Qt::CustomContextMenu);

	connect(ui->listWidgetProject, SIGNAL(customContextMenuRequested(const QPoint&)),
		this, SLOT(on_listWidgetProject_customContextMenuRequested(const QPoint&)));

	// 项目配置关联数据库 [3/13/2023]
	m_projectDB = dynamic_cast<CProjectDB*>(CDatabaseFactory::createDB(PROJECT_DB));
	// 加载已保存项目列表 [3/14/2023]
	m_projectDB->getAllProjects(m_lstProjects);
	ui->listWidgetProject->addItems(m_lstProjects);
	
	m_imageDB = dynamic_cast<CImageDB*>(CDatabaseFactory::createDB(IMAGE_DB));
	// 加载图片信息 [3/17/2023]
	m_imageDB->loadMapNameIdx();
	m_mapDB = dynamic_cast<CMapDB*>(CDatabaseFactory::createDB(MAP_DB));
	m_mapDB->loadAllMapInfo();
}

SewerClient::~SewerClient()
{
	m_mapDB->closeDatabase();
	m_imageDB->closeDatabase();
	m_projectDB->closeDatabase();
	m_lstProjects.clear();
	m_vecDetectInfo.clear();
	m_detectResVec.clear();
	m_clsNames.clear();
    m_fileList.clear();
	m_vecImgInfo.clear();
    delete ui;
}

void SewerClient::on_btnSelectFile_clicked()
{
	QString filters = "file(*.jpg *.png *.dng *.JPEG *.jpeg)";
	m_fileList = QFileDialog::getOpenFileNames(this, "打开文件", "", filters);
	// 如果没有点击检测按钮则清空文件信息列表 [2/16/2023]
	if (!m_isDetect)
	{
		m_lstFileInfo.clear();
	}
	if (m_fileList.size() > 0)
	{
		setImgInfo(); // 配置选择图片信息 [2/4/2023]
		// 文本框显示 [2/11/2023]
		if (m_lstFileInfo.size() != 1)
		{
			QString fileDirPath = m_fileList.at(0).left(m_fileList.at(0).lastIndexOf("/") + 1);
			ui->filePostion->setText(fileDirPath);
		}
		else
		{
			ui->filePostion->setText(m_fileList.at(0));
		}

		if (!m_fileList.at(0).isEmpty())
		{
			// 检测按键 [2/27/2023]
			ui->btnDetect->setEnabled(true);
		}
	}
}

void SewerClient::removeImgWidget()
{
	int tabCount = ui->imgTabWidget->count() - 1;
	for (int index = tabCount; index > 0; index--)
	{
		QWidget* widget = ui->imgTabWidget->widget(index);
		ui->imgTabWidget->removeTab(index);
		delete widget;
	}
}

void SewerClient::getProjectImgInfo(const QString& projectName)
{
	auto proIter = m_projectDB->m_mapNameIdx.find(projectName);
	if (proIter != m_projectDB->m_mapNameIdx.end())
	{
		int projectId = proIter->second;
		auto imgIt = m_mapDB->m_mapProImgIdx.find(projectId);
		if (imgIt != m_mapDB->m_mapProImgIdx.end())
		{
			vector<int> vecImage = imgIt->second;
			m_vecImgInfo.clear();
			// 清空检测图片信息 [3/26/2023]
			m_vecDetectInfo.clear();
#if 0
			if (m_currProjectIdx != projectId)
			{
				// 更换检测项目后清空检测图片信息 [3/26/2023]
			}
			else
			{
				// TODO: 添加获取当前检测信息逻辑 [3/26/2023]
			}
#endif
			m_vecImgInfo.reserve(vecImage.size());
			// 遍历获取图片信息 [3/25/2023]
			for (int& imgId : vecImage)
			{
				ImageInfo info = m_imageDB->searchData(imgId);
				m_vecImgInfo.emplace_back(info);
				m_vecDetectInfo.emplace_back(DetectInfo(info));
			}
		}
	}
}


void SewerClient::updateDisplay()
{
	int idx = 0;
	for (ImageInfo& info : m_vecImgInfo)
	{
		string imgPath = info._absPath.toStdString();
		displayImg(imgPath);
	}
}

void SewerClient::on_btnDetect_clicked()
{
	if (!imgDetect())
	{
		qDebug() << ERROR_CODE_8 << Qt::endl;
		return;
	}
	m_isDetect = true;
	// 清空文本框 [2/11/2023]
	ui->filePostion->clear();
	ui->btnDetect->setEnabled(false);
	ui->btnDocxOutput->setEnabled(true);
	m_lstFileInfo.clear();
}

void SewerClient::setDetectInfo(pair<size_t, float>& defectInfo)
{
	size_t df_idx = defectInfo.first;
	float conf_val = defectInfo.second;
	ui->comBoxName->setCurrentIndex(df_idx + 1);
	ui->lineEditSimilarity->setText(QString::number(conf_val));
}

bool SewerClient::imgDetect()
{
	try
	{
		m_detector = dynamic_cast<CDetector*>(CDetectorFactory::createDetector(RESNET));
		if (m_clsNames.empty())
		{
			m_detector->getClsNames(m_clsNames);
		}
		qDebug() << SUCCEED_CODE_1;
		// 开始检测 [2/26/2023]
		for (int i = 0; i < m_lstFileInfo.size(); i++)
		{
			QFileInfo info = m_lstFileInfo[i];
			detectInfoUtil(info, i);
		}
		// 检测完成后跳转到tab [3/28/2023]
		ui->imgTabWidget->setCurrentIndex(1);
	}
	catch (const std::exception& e)
	{
		qDebug() << QString::fromLocal8Bit("出现错误: ") << e.what() << Qt::endl;
		return false;
	}
	return true;
}

void SewerClient::setImgInfo()
{
	m_isDetect = false;
	for (QString& imgPath : m_fileList)
	{
		QFileInfo imgInfo(imgPath);
		if (!imgInfo.exists())
		{
			qDebug() << ERROR_CODE_9;
			return;
		}
		m_lstFileInfo.append(imgInfo);
	}
}

void SewerClient::writeDocx()
{
	// 项目对应的docx文件名称 [2/12/2023]
	QString currTime = QDateTime::currentDateTime().toString("yyyyMMdd_hh:mm");
	setProjectDir();
	m_docxName = (m_projectDirPath + "/" + m_currProjectName + ".docx");
	// 打开docx模板 [2/14/2023]
	m_docx = new CDox("default.docx");
	// 绘制表格 [2/26/2023]
	for (auto& info : m_vecDetectInfo)
	{
		Table* pTable = m_docx->addTemplate(info._absPath, info._defectName, info._defectLevel);
		// 写入数据库 [3/15/2023]
		ImageInfo tmpInfo =
		{
			QString::fromStdString(info._imgName),
			QString::fromStdString(info._absPath),
			QString::fromStdString(info._defectName),
			info._defectLevel,
			info._confVal
		};
		m_imageDB->insertData(tmpInfo);
		// 添加映射关系获得图片id [3/18/2023]
		m_mapDB->insertData(m_currProjectIdx, m_imageDB->m_lastImgIdx);
	}
	m_docx->save(m_docxName);
}

void SewerClient::detectInfoUtil(QFileInfo& info, int imgIdx /*=0*/)
{
	string imgPath = info.absoluteFilePath().toStdString(); // 待检测图片绝对路径 [2/4/2023]
	string imgName = info.baseName().toStdString();		// 图片文件名称 [2/4/2023]
	string dstImgPath;		// 处理完成移动后图片路径 [2/4/2023]
	try
	{
		Mat srcImg = imread(imgPath);
		Mat dstImg = srcImg.clone();
		qDebug() << QString::fromLocal8Bit("detecting image: %1").arg(QString::fromStdString(imgName));
		m_detectResVec = m_detector->getDetectRes(srcImg);
		// 检测到置信值最高的缺陷类别（后续需要更新到可根据用户需求更改） [2/9/2023]
		auto& resCls = m_detectResVec.at(0);
		// 获取缺陷等级 [3/15/2023]
		int defectLevel = setDetectLevel(resCls.second);
		ui->comBoxLevel->setCurrentIndex(defectLevel);
		// 检测后填充combox [2/28/2023]
		setDetectInfo(resCls);
		// 检测到缺陷类别名称 [2/9/2023]
		string defectName = m_clsNames.at(resCls.first);
		// 图片文件后缀名 [2/9/2023]
		string suffixName = info.suffix().toStdString();
		// 文件名添加检测类别 [2/5/2023]
		imgName += ("_" + defectName + "." + suffixName);
		m_detector->imgName2ResName(imgName, dstImgPath);
		// resize [2/16/2023]
		autoScaleImg(dstImg);
		imwrite(dstImgPath, dstImg);
		// 图片展示 [2/17/2023]
		displayImg(dstImgPath);
		// <图片路径-缺陷名称>映射关系改为结构体 [3/15/2023]
		m_vecDetectInfo.emplace_back(DetectInfo(imgName, dstImgPath, defectName, defectLevel, resCls.second));
	}
	catch (const cv::Exception& e)
	{
		qDebug() << QString::fromLocal8Bit("图片读取出现错误: ") << e.what() << Qt::endl;
		return;
	}
}

void SewerClient::setDocxPath()
{
	QString dirPath = g_vecDirPath.at(5);
	if (dirPath.isEmpty())
	{
		qDebug() << __FUNCTION__ << ERROR_CODE_1;
		return;
	}
	QDir tmpDir(dirPath);
	if (!tmpDir.exists())
	{
		tmpDir.mkdir(dirPath);
		qDebug() << __FUNCTION__ << QString::fromLocal8Bit("已设置docx结果路径 ");
	}
	m_docxDirPath = dirPath;
}

void SewerClient::setProjectDir()
{
	QString currTime = QDateTime::currentDateTime().toString("yyyyMMdd");
	QString dirPath = m_docxDirPath + m_currProjectName + "_" + currTime;
	QDir tmpDir(dirPath);
	if (!tmpDir.exists())
	{
		// 创建项目文件夹 [2/14/2023]
		if (!tmpDir.mkdir(dirPath))
		{
			qDebug() << __FUNCTION__ << ERROR_CODE_10;
		}
		else
		{
			qDebug() << __FUNCTION__ << SUCCEED_CODE_2;
		}
	}
	m_projectDirPath = dirPath;
}

void SewerClient::autoScaleImg(Mat& srcImg)
{
	double w = srcImg.cols / 1.0f;
	double h = srcImg.rows / 1.0f;
	Size resizeScale(224, 224);
	double imgScale = w >= h ? (h / w) : (w / h);
	w >= h ? resizeScale.height *= imgScale : resizeScale.width *= imgScale;
	cv::resize(srcImg, srcImg, resizeScale);
}

void SewerClient::displayImg(string& imgPath)
{
	// 从路径中获取文件名
	const auto pos = imgPath.find_last_of('/');
	const QString strImgName = QString::fromStdString(imgPath.substr(pos + 1));

	// 加载图片
	QImage img;
	img.load(QString::fromStdString(imgPath));

	// 添加图片，创建 widget 并添加对应的图片信息
	addImgWidget(strImgName, img);
}

int SewerClient::setDetectLevel(float confVal)
{
	// TODO: 优化算法模型后更新 [3/15/2023]
	return (confVal < 3) + (confVal < 0) + (confVal < -3) + 1;
}

void SewerClient::addImgWidget(const QString& imgName, const QImage& img)
{
	QWidget* widget = new QWidget(ui->imgTabWidget);
	widget->setFixedSize(img.size());

	QLabel* label = new QLabel(widget);
	label->setPixmap(QPixmap::fromImage(img));
	label->setAlignment(Qt::AlignCenter);

	QVBoxLayout* layout = new QVBoxLayout(widget);
	layout->addWidget(label);
	widget->setLayout(layout);
	int ret = ui->imgTabWidget->addTab(widget, imgName);
}

void SewerClient::on_btnNewProject_clicked()
{
	removeImgWidget();
	// 添加项目弹窗 [2/12/2023]
	m_wProject = new projectDlg(this);
	Qt::WindowFlags flags = Qt::Dialog;
	m_wProject->setWindowFlags(flags);
	m_wProject->show();
}

void SewerClient::on_btnDocxOutput_clicked()
{
	// 当前项目id [3/17/2023]
	m_currProjectIdx = m_projectDB->m_mapNameIdx[m_currProjectName];
	// 写入docx [2/26/2023]
	writeDocx();
	m_lstFileInfo.clear();
	ui->btnDocxOutput->setEnabled(false);
}

void SewerClient::on_comBoxName_activated(int index)
{
	// combox修改缺陷类别id [3/15/2023]
	int com_idx = (index - 1);
	// 更新标签后修改combox功能 [3/9/2023]
	m_vecDetectInfo[m_currTabIdx]._defectName = m_clsNames.at(com_idx);
}

void SewerClient::on_imgTabWidget_currentChanged(int index)
{
	m_currTabIdx = index == 0 ? 0 : (index - 1);
	string defectName = m_vecDetectInfo.at(m_currTabIdx)._defectName;
	int com_defectNameIdx = g_mapDefectNameIdx.at(defectName);
	// 切换标签后更新名称combox [3/9/2023]
	ui->comBoxName->setCurrentIndex(com_defectNameIdx);
	// 更新等级combox [3/15/2023]
	ui->comBoxLevel->setCurrentIndex(m_vecDetectInfo[m_currTabIdx]._defectLevel);
	// 更新置信值 [3/15/2023]
	ui->lineEditSimilarity->setText(QString::number(m_vecDetectInfo[m_currTabIdx]._confVal));
}

void SewerClient::on_listWidgetProject_doubleClicked(const QModelIndex &index)
{
	// 清空tab [3/26/2023]
	removeImgWidget();
	// 双击listwidget跳转到项目内容功能 [3/24/2023]
	if (!index.isValid())
	{
		return;
	}
	QListWidgetItem* item = ui->listWidgetProject->item(index.row());
	QString projectName = item->text();	// 检测项目名称 [3/25/2023]
	// 通过映射获取存储的信息 [3/24/2023]
	getProjectImgInfo(projectName);
	// 根据获取的检测项目图片信息更新显示 [3/26/2023]
	if (!m_vecImgInfo.empty())
	{
		updateDisplay();
		ui->imgTabWidget->setCurrentIndex(1);
	}
	// 可继续添加图片 [3/29/2023]
	ui->btnSelectFile->setEnabled(true);
	m_currProjectName = projectName;
}


void SewerClient::on_comBoxLevel_activated(int index)
{
	// 更新缺陷等级 [3/15/2023]
	m_vecDetectInfo[m_currTabIdx]._defectLevel = index;
}

void SewerClient::on_listWidgetProject_customContextMenuRequested(const QPoint& pos)
{
	QListWidgetItem* item = ui->listWidgetProject->itemAt(pos);
	if (!item)
	{
		return;
	}
	QMenu* menu = new QMenu(this);

	QAction* renameAction = new QAction(tr("重命名"), this);	// 检测项目重命名 [3/27/2023]
	QAction* deleteAction = new QAction(tr("删除"), this);
	
	menu->addAction(renameAction);
	menu->addAction(deleteAction);

	menu->popup(ui->listWidgetProject->viewport()->mapToGlobal(pos));
	menu->setAttribute(Qt::WA_DeleteOnClose);	// 菜单关闭时自动释放内存 [3/24/2023]

	// 当用户点击 删除 菜单项时执行该槽函数 [3/23/2023]
	connect(deleteAction, &QAction::triggered, this, &SewerClient::deleteProjectItem);
	// 链接槽函数 [3/27/2023]
	connect(renameAction, &QAction::triggered, this, &SewerClient::renameProjectItem);
}

void SewerClient::deleteProjectItem()
{
	QAction* action = qobject_cast<QAction*>(sender());
	QListWidgetItem* item = ui->listWidgetProject->currentItem();
	// 从 QListWidget 中移除 item，释放占用的内存 [3/23/2023]
	ui->listWidgetProject->takeItem(ui->listWidgetProject->row(item));
	QString projectName = item->text();
	m_projectDB->deleteData(projectName);
	delete item;
}

void SewerClient::renameProjectItem()
{
	QListWidgetItem* item = ui->listWidgetProject->currentItem();
	// 实现重命名功能 [3/27/2023]
	QString oldName = item->text();

	QInputDialog dialog(this);
	dialog.setWindowTitle(tr("检测项目重命名"));
	dialog.setLabelText(tr("新名称"));
	dialog.setTextValue(oldName);

	if (dialog.exec() == QDialog::Accepted)
	{
		QString newName = dialog.textValue();
		if (!newName.isEmpty())
		{
			item->setText(newName);
			m_projectDB->updateName(oldName, newName);
		}
	}
}
