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
    m_fileList.clear();
    delete ui;
}

void SewerClient::on_btnSelectFile_clicked()
{
	QString filters = "file(*.jpg *.png *.dng *.JPEG *.jpeg)";
	m_fileList = QFileDialog::getOpenFileNames(this, "打开文件", "", filters);
	if (m_fileList.size() > 0)
	{
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
		assert("ONNX检测器加载失败");
		return;
	}
}

bool SewerClient::imgDetect()
{
	return false;
}

