#include "projectdlg.h"
#include "ui_projectdlg.h"
#include "sewerclient.h"
#include "ui_sewerclient.h"
#include "projectcfg.h"

#include <QMessageBox>

projectDlg::projectDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::projectDlg)
{
    ui->setupUi(this);
}

projectDlg::projectDlg(SewerClient* client, QWidget* parent /*= nullptr*/) 
    : QWidget(parent)
    , ui(new Ui::projectDlg)
    , m_client(client)
{
	ui->setupUi(this);
}

projectDlg::~projectDlg()
{
    delete ui;
}

void projectDlg::on_btnProjectName_clicked()
{
    QString projectName = ui->editProjectName->text();
    if (projectName.isEmpty())
    {
        QMessageBox::warning(this, QString::fromUtf8("项目名称不为空"), QString::fromUtf8("项目名称不为空"));
    }
    m_client->ui->btnSelectFile->setEnabled(true);
    // 添加项目后更新list [3/9/2023]
    m_client->ui->listWidgetProject->addItem(projectName);
    m_client->m_currProjectName = projectName;
    // 写入数据库 [3/14/2023]
    m_client->m_projectDB->insertData(projectName);
    this->close();
}

