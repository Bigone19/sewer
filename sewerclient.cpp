#include "sewerclient.h"
#include "ui_sewerclient.h"

SewerClient::SewerClient(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SewerClient)
{
    ui->setupUi(this);
}

SewerClient::~SewerClient()
{
    delete ui;
}

