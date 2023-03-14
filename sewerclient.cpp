#include "sewerclient.h"
#include "ui_sewerclient.h"
#include "table.h"
#include "projectdlg.h"
#include "projectcfg.h"

#include <QDateTime>
#include <QBrush>
#include <QPixmap>

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
	ui->imgTab->setAutoFillBackground(true);

	// 项目配置关联数据库 [3/13/2023]
	m_projectDB = new CProjectDB();
	// 加载已保存项目列表 [3/14/2023]
	m_projectDB->getAllProjects(m_lstProjects);
	ui->listWidgetProject->addItems(m_lstProjects);
	
	m_imageDB = new CImageDB();
	m_mapDB = new CMapDB();
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
	delete m_wProject;
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


void SewerClient::on_btnDetect_clicked()
{
	if (!ui->imgTab->children().isEmpty())
	{
		QObject* tmpLabel = ui->imgTab->children().at(0);
		delete tmpLabel;
	}
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
		m_detector = new CDetector();
		if (m_clsNames.empty())
		{
			m_detector->getClsNames(m_clsNames);
		}
		qDebug() << SUCCEED_CODE_1;
		// 开始检测 [2/26/2023]
		detectInfoUtil(m_lstFileInfo[0]);
		if (m_lstFileInfo.size() > 1)
		{
			for (int i = 1; i < m_lstFileInfo.size(); i++)
			{
				QFileInfo info = m_lstFileInfo[i];
				detectInfoUtil(info, true);
			}
		}
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
	m_docxName = (m_projectDirPath + "/" + m_wProject->m_projectName + ".docx");
	// 打开docx模板 [2/14/2023]
	m_docx = new CDox("default.docx");
	// 绘制表格 [2/26/2023]
	m_imageDB->openDatabase();
	for (auto& info : m_vecDetectInfo)
	{
		Table* pTable = m_docx->addTemplate(info.s_imagePath, info.s_defectName, info.s_defectLevel);
		// 写入数据库 [3/15/2023]
		m_imageDB->insertData(QString::fromStdString(info.s_imagePath), 
			QString::fromStdString(info.s_defectName), info.s_defectLevel);
	}
	m_imageDB->closeDatabase();
	m_docx->save(m_docxName);
}

void SewerClient::detectInfoUtil(QFileInfo& info, bool isMuti /*=false*/)
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
		displayImg(dstImgPath, isMuti);
		// <图片路径-缺陷名称>映射关系改为结构体 [3/15/2023]
		m_vecDetectInfo.emplace_back(DetectInfo(dstImgPath, defectName, defectLevel, resCls.second));
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
	QString dirPath = m_docxDirPath + m_wProject->m_projectName + "_" + currTime;
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

void SewerClient::displayImg(string& imgPath, bool isMuti/*=false*/)
{
	size_t pos = imgPath.find_last_of('/');
	QString strImgName = QString::fromStdString(imgPath.substr(pos + 1));
	QImage img;
	img.load(QString::fromStdString(imgPath));
	QPalette palette = ui->imgTab->palette();

	if (!isMuti)
	{
		// 更换显示图片方式 [3/2/2023]
		ui->imgTabWidget->setTabVisible(0, true);
		ui->imgTabWidget->setTabText(0, strImgName);
		QLabel* tmpLabel = new QLabel(ui->imgTab);
		QPixmap pic(QString::fromStdString(imgPath));
		tmpLabel->setPixmap(pic);
		QVBoxLayout* tmpVBoxLayout = new QVBoxLayout(ui->imgTab);
		tmpVBoxLayout->addWidget(tmpLabel);
		tmpVBoxLayout->deleteLater();
	}
	else
	{
		QWidget* tmpWidget = new QWidget(ui->imgTabWidget);
		tmpWidget->setFixedSize(img.size());
		QLabel* tmpLabel = new QLabel(tmpWidget);
		QPixmap pic(QString::fromStdString(imgPath));
		tmpLabel->setPixmap(pic);
		QVBoxLayout* tmpVBoxLayout = new QVBoxLayout(tmpWidget);
		tmpVBoxLayout->addWidget(tmpLabel);
		ui->imgTabWidget->addTab(tmpWidget, strImgName);
	}
}

int SewerClient::setDetectLevel(float confVal)
{
	// TODO: 优化算法模型后更新 [3/15/2023]
	if (confVal <= -3)
	{
		return 4;
	}
	else if (confVal <= 0)
	{
		return 3;
	}
	else if (confVal <= 3)
	{
		return 2;
	}
	else
	{
		return 1;
	}
}

void SewerClient::on_btnNewProject_clicked()
{
	// 添加项目弹窗 [2/12/2023]
	m_wProject = new projectDlg(this);
	Qt::WindowFlags flags = Qt::Dialog;
	m_wProject->setWindowFlags(flags);
	m_wProject->show();
}

void SewerClient::on_btnDocxOutput_clicked()
{
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
	m_vecDetectInfo[m_currTabIdx].s_defectName = m_clsNames.at(com_idx);
}

void SewerClient::on_imgTabWidget_currentChanged(int index)
{
	m_currTabIdx = index;
	string defectName = m_vecDetectInfo.at(index).s_defectName;
	int com_defectNameIdx = g_mapDefectNameIdx.at(defectName);
	// 切换标签后更新名称combox [3/9/2023]
	ui->comBoxName->setCurrentIndex(com_defectNameIdx);
	// 更新等级combox [3/15/2023]
	ui->comBoxLevel->setCurrentIndex(m_vecDetectInfo[index].s_defectLevel);
	// 更新置信值 [3/15/2023]
	ui->lineEditSimilarity->setText(QString::number(m_vecDetectInfo[index].s_confVal));
}

void SewerClient::on_listWidgetProject_doubleClicked(const QModelIndex &index)
{
	// TODO: 双击listwidget修改项目名称功能 [3/15/2023]
}


void SewerClient::on_comBoxLevel_activated(int index)
{
	// 更新缺陷等级 [3/15/2023]
	m_vecDetectInfo[m_currTabIdx].s_defectLevel = index;
}

