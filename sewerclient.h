#ifndef SEWERCLIENT_H
#define SEWERCLIENT_H

#include <QMainWindow>
#include <QFileDialog>
#include <unordered_map>

// update [2/2/2023 ]
#include "onnxDetector.h"
// docx [2/6/2023]
#include "docxUtils.h"

using namespace DocxUtils;
using std::unordered_map;

QT_BEGIN_NAMESPACE
namespace Ui { class SewerClient; }
QT_END_NAMESPACE

class projectCfg;
class SewerClient : public QMainWindow
{
    Q_OBJECT

public:
    SewerClient(QWidget* parent = nullptr);
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
    /**
    * @brief: 添加新工程
    * @param: 
    * @date: 2023/02/12
    */
    void on_btnNewProject_clicked();
    /**
    * @brief: 导出docx文档
    * @param: 
    * @date: 2023/02/26
    */
    void on_btnDocxOutput_clicked();
    /**
    * @brief: 名称combox
    * @param: 
    * @date: 2023/02/28
    */
    void on_comBoxName_activated(int index);

private:
    /**
    * @brief: 设置检测完成后combox选项
    * @param: 
    * @date: 2023/02/28
    */
    void setDetectInfo(pair<size_t, float>& defectInfo);
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
    /**
    * @brief: 遍历图片并写入docx
    * @param: 
    * @date: 2023/02/10
    */
    void writeDocx();
    /**
    * @brief: 检测信息工具
    * @param: 
    * @date: 2023/02/18
    */
    void detectInfoUtil(QFileInfo& info, bool isMuti =false);
    /**
    * @brief: 设置docx结果路径
    * @param: 
    * @date: 2023/02/12
    */
    void setDocxPath();
    /**
    * @brief: 创建项目文件夹
    * @param: 
    * @date: 2023/02/12
    */
    void setProjectDir();
    /**
    * @brief: 自适应比例缩放图片
    * @param: 
    * @date: 2023/02/16
    */
    void autoScaleImg(Mat& srcImg);
    /**
    * @brief: 展示检测后的图片
    * @param isMuti: 是否多个图片
    * @date: 2023/02/17
    */
    void displayImg(string& imgPath, bool isMuti=false);
private:
    Ui::SewerClient *ui;

    CDetector* m_detector;      // onnx检测器 [2/3/2023]
    vector<pair<size_t, float> > m_detectResVec;    // 检测结果列表 [2/4/2023]

    QStringList m_fileList;     // 选择文件列表 [2/4/2023]
    QFileInfoList m_lstFileInfo;
    vector<string> m_clsNames;  // 类别名称列表 [2/5/2023]

    CDox* m_docx;   // 写入docx [2/10/2023]

    QString m_docxName;         // docx文件名 [2/12/2023]
    QString m_docxDirPath;      // docx结果文件夹路径 [2/12/2023]
    QString m_projectDirPath;   // 项目文件夹路径 [2/14/2023]
    projectCfg* m_wProject;     // 弹出项目窗口 [2/12/2023]

    bool m_isDetect;            // 是否点击检测按钮 [2/16/2023]

    unordered_map<string, string> m_mapImgDefect;   //  [2/26/2023]

    friend class projectCfg;
};
#endif // SEWERCLIENT_H
