#ifndef PROJECTDLG_H
#define PROJECTDLG_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class projectDlg;
}
QT_END_NAMESPACE

class SewerClient;
class projectDlg : public QWidget
{
    Q_OBJECT

public:
	explicit projectDlg(QWidget* parent = nullptr);
	explicit projectDlg(SewerClient* client, QWidget* parent = nullptr);
    ~projectDlg();

private slots:
    /**
    * @brief: 提交项目名称
    * @param: 
    * @date: 2023/02/12
    */
    void on_btnProjectName_clicked();

private:
    Ui::projectDlg *ui;

    QString m_projectName;      // 项目名称 [2/12/2023]
    SewerClient* m_client;      // 主窗口 [2/12/2023]
    
    friend class SewerClient;
};

#endif // PROJECTCFG_H
