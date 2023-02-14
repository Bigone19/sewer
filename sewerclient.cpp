#include "sewerclient.h"
#include "ui_sewerclient.h"
#include "table.h"
#include "projectcfg.h"

#include <QDateTime>

SewerClient::SewerClient(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SewerClient)
	, m_isDetect(false)
{
	m_clsNames.clear();
	setDocxPath();

    ui->setupUi(this);
	ui->filePostion->setEnabled(false);
	ui->btnDetect->setEnabled(false);
	// 未创建项目名称前不能上传图片 [2/12/2023]
	ui->btnSelectFile->setEnabled(false);
}

SewerClient::~SewerClient()
{
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
	if (m_fileList.size() > 0)
	{
		setImgInfo(); // 配置选择图片信息 [2/4/2023]
		// 文本框显示 [2/11/2023]
		if (m_fileList.size() != 1)
		{
			QString fileDirPath = m_fileList.at(0).left(m_fileList.at(0).lastIndexOf("/") + 1);
			ui->filePostion->setText(fileDirPath);
		}
		ui->filePostion->setText(m_fileList.at(0));

		if (!m_fileList.at(0).isEmpty())
		{
			ui->btnDetect->setEnabled(true);
		}
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
		// 遍历检测图片列表并写入docx [2/10/2023]
		writeDocx();
		// 清空文件列表 [2/10/2023]
		m_lstFileInfo.clear();
		// 清空文本框 [2/11/2023]
		ui->filePostion->clear();
		ui->btnDetect->setEnabled(false);
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

	for (QFileInfo& info : m_lstFileInfo)
	{
		string imgPath = info.absoluteFilePath().toStdString(); // 待检测图片绝对路径 [2/4/2023]
		string imgName = info.baseName().toStdString() + "_";		// 图片文件名称 [2/4/2023]
		string dstImgPath;		// 处理完成移动后图片路径 [2/4/2023]
		try
		{
			Mat srcImg = imread(imgPath);
			Mat dstImg = srcImg.clone();
			qDebug() << QString::fromLocal8Bit("detecting image: %1").arg(QString::fromStdString(imgName));
			m_detectResVec = m_detector->getDetectRes(srcImg);
			// 检测到置信值最高的缺陷类别（后续需要更新到可根据用户需求更改） [2/9/2023]
			auto& resCls = m_detectResVec.at(0);
			// 检测到缺陷类别名称 [2/9/2023]
			string defectName = m_clsNames.at(resCls.first);
			// 图片文件后缀名 [2/9/2023]
			string suffixName = info.suffix().toStdString();
			// 文件名添加检测类别 [2/5/2023]
			imgName += (defectName + "." + suffixName);
			m_detector->imgName2ResName(imgName, dstImgPath);
			// resize [2/16/2023]
			autoScaleImg(dstImg);
			// 写入图片 [2/6/2023]
			imwrite(dstImgPath, dstImg);
			// docx写入项目文件夹 [2/12/2023]
			Table* pTable = m_docx->addTemplate(dstImgPath, defectName);
		}
		catch (const cv::Exception& e)
		{
			qDebug() << QString::fromLocal8Bit("图片读取出现错误: ") << e.what() << Qt::endl;
			continue;
		}
	}
	m_docx->save(m_docxName);
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
	Size resizeScale(320, 320);
	double imgScale = w >= h ? (h / w) : (w / h);
	w >= h ? resizeScale.height *= imgScale : resizeScale.width *= imgScale;
	cv::resize(srcImg, srcImg, resizeScale);
}

void SewerClient::on_btnNewProject_clicked()
{
	// 添加项目弹窗 [2/12/2023]
	m_wProject = new projectCfg(this);
	Qt::WindowFlags flags = Qt::Dialog;
	m_wProject->setWindowFlags(flags);
	m_wProject->show();
}

