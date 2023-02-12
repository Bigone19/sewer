#include "projectcfg.h"
#include "ui_projectcfg.h"

projectCfg::projectCfg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::projectCfg)
{
    ui->setupUi(this);
}

projectCfg::~projectCfg()
{
    delete ui;
}
