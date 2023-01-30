#ifndef SEWERCLIENT_H
#define SEWERCLIENT_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class SewerClient; }
QT_END_NAMESPACE

class SewerClient : public QMainWindow
{
    Q_OBJECT

public:
    SewerClient(QWidget *parent = nullptr);
    ~SewerClient();

private:
    Ui::SewerClient *ui;
};
#endif // SEWERCLIENT_H
