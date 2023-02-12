#include "projectcfg.h"
#include "ui_projectcfg.h"
#include "sewerclient.h"
#include "ui_sewerclient.h"

#include <QMessageBox>

projectCfg::projectCfg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::projectCfg)
{
    ui->setupUi(this);
}

projectCfg::projectCfg(SewerClient* client, QWidget* parent /*= nullptr*/) 
    : QWidget(parent)
    , ui(new Ui::projectCfg)
    , m_client(client)
{
	ui->setupUi(this);
}

projectCfg::~projectCfg()
{
    delete ui;
}

void projectCfg::on_btnProjectName_clicked()
{
    m_projectName = ui->editProjectName->text();
    if (m_projectName.isEmpty())
    {
        QMessageBox::warning(this, QString::fromUtf8("项目名称不为空"), QString::fromUtf8("项目名称不为空"));
    }
    m_client->ui->btnSelectFile->setEnabled(true);
    this->close();
}

