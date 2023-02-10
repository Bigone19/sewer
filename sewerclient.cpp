#include "sewerclient.h"
#include "ui_sewerclient.h"
#include "table.h"

SewerClient::SewerClient(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SewerClient)
{
	m_clsNames.clear();

    ui->setupUi(this);
	ui->btnDetect->setEnabled(false);
}

SewerClient::~SewerClient()
{
	m_detectResVec.clear();
	m_clsNames.clear();
    m_fileList.clear();
    delete ui;
}

void SewerClient::on_btnSelectFile_clicked()
{
	QString filters = "file(*.jpg *.png *.dng *.JPEG *.jpeg)";
	m_fileList = QFileDialog::getOpenFileNames(this, "打开文件", "", filters);
	if (m_fileList.size() > 0)
	{
		setImgInfo(); // 配置选择图片信息 [2/4/2023]
		QString fileDirPath = m_fileList.at(0).left(m_fileList.at(0).lastIndexOf("/") + 1);
		ui->filePostion->setText(fileDirPath);
		if (!fileDirPath.isEmpty())
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
			// 写入图片 [2/6/2023]
			imwrite(dstImgPath, dstImg);
			// 写入docx [2/10/2023]
			m_docx = new CDox("default.docx");
			Table* pTable = m_docx->addTemplate(dstImgPath, defectName);
			m_docx->save("default.docx");
		}
		catch (const cv::Exception& e)
		{
			qDebug() << QString::fromLocal8Bit("图片读取出现错误: ") << e.what() << Qt::endl;
			continue;
		}
	}
}

