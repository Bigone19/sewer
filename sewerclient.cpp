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
	m_fileList = QFileDialog::getOpenFileNames(this, "Ñ¡ÔñÎÄ¼ş", "", filters);
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

