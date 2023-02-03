#include "sewerclient.h"
#include "ui_sewerclient.h"

SewerClient::SewerClient(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SewerClient)
{
    ui->setupUi(this);

	ui->btnDetect->setEnabled(false);
}

SewerClient::~SewerClient()
{
	m_detectResVec.clear();
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
		qDebug() << SUCCEED_CODE_1;
		for (QFileInfo& info : m_lstFileInfo)
		{
			string imgPath = info.absoluteFilePath().toStdString(); // 待检测图片绝对路径 [2/4/2023]
			string imgName = info.fileName().toStdString();		// 图片文件名称 [2/4/2023]
			string dstImgPath;		// 处理完成移动后图片路径 [2/4/2023]
			m_detector->imgName2ResName(imgName, dstImgPath);

			try
			{
				Mat srcImg = imread(imgPath);
				m_detectResVec = m_detector->getDetectRes(srcImg);
				imwrite(dstImgPath, srcImg);
			}
			catch (const cv::Exception& e)
			{
				qDebug() << QString::fromLocal8Bit("图片读取出现错误: ") << e.what() << Qt::endl;
				continue;
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

