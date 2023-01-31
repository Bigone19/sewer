#ifndef SEWERCLIENT_H
#define SEWERCLIENT_H

#include <QMainWindow>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class SewerClient; }
QT_END_NAMESPACE

class SewerClient : public QMainWindow
{
    Q_OBJECT

public:
    SewerClient(QWidget *parent = nullptr);
    ~SewerClient();

private slots:
    void on_btnSelectFile_clicked();

private:
    Ui::SewerClient *ui;

    QStringList m_fileList;
};
#endif // SEWERCLIENT_H
