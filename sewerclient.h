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
    /**
    * @brief: 配置选择图片信息
    * @param: 
    * @date: 2023/02/04
    */
    void setImgInfo();
private:
    Ui::SewerClient *ui;

    CDetector* m_detector;      // onnx检测器 [2/3/2023]
    vector<pair<size_t, float> > m_detectResVec;    // 检测结果列表 [2/4/2023]

    QStringList m_fileList;     // 选择文件列表 [2/4/2023]
    QFileInfoList m_lstFileInfo;
    vector<string> m_clsNames;  // 类别名称列表 [2/5/2023]
};
#endif // SEWERCLIENT_H
