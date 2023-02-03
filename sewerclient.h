#ifndef SEWERCLIENT_H
#define SEWERCLIENT_H

#include <QMainWindow>
#include <QFileDialog>
// update [2/2/2023 ]
#include "onnxDetector.h"

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
    /**
    * @brief: 选择文件槽
    * @param: 
    * @date: 2023/02/03
    */
    void on_btnSelectFile_clicked();
    /**
    * @brief: 检测目标槽
    * @param: 
    * @date: 2023/02/03
    */
    void on_btnDetect_clicked();

private:
    /**
    * @brief: 检测函数入口
    * @param: 
    * @date: 2023/02/03
    */
    bool imgDetect();

private:
    Ui::SewerClient *ui;

    CDetector* m_detector;      // onnx检测器 [2/3/2023]

    QStringList m_fileList;
};
#endif // SEWERCLIENT_H
