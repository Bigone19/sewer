#ifndef PROJECTCFG_H
#define PROJECTCFG_H

#include <QWidget>

namespace Ui {
class projectCfg;
}
class SewerClient;
class projectCfg : public QWidget
{
    Q_OBJECT

public:
	explicit projectCfg(QWidget* parent = nullptr);
	explicit projectCfg(SewerClient* client, QWidget* parent = nullptr);
    ~projectCfg();

private slots:
    /**
    * @brief: 提交项目名称
    * @param: 
    * @date: 2023/02/12
    */
    void on_btnProjectName_clicked();

private:
    Ui::projectCfg *ui;

    QString m_projectName;      // 项目名称 [2/12/2023]
    SewerClient* m_client;      // 主窗口 [2/12/2023]
    
    friend class SewerClient;
};

#endif // PROJECTCFG_H
