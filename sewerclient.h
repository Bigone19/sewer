#ifndef SEWERCLIENT_H
#define SEWERCLIENT_H

#include <QMainWindow>
#include <QFileDialog>
#include <map>

// update [2/2/2023 ]
#include "detectorFactory.h"
// docx [2/6/2023]
#include "docxUtils.h"
#include "databaseFactory.h"

using namespace DocxUtils;

QT_BEGIN_NAMESPACE
namespace Ui { class SewerClient; }
QT_END_NAMESPACE

struct DetectInfo
{
    string _imgName;       // 图片名称 [3/17/2023]
    string _absPath;       // 图片路径 [3/15/2023]
    string _defectName;    // 缺陷名称 [3/15/2023]
    int _defectLevel = 0;      // 缺陷等级 [3/15/2023]
    float _confVal = 0.0f;        // 置信值 [3/15/2023]

    DetectInfo(const string& strName, const string& strAbsPath, 
        const string& strDetectName, int defectLevel, float conVal)
        : _imgName(strName)
        , _absPath(strAbsPath)
        , _defectName(strDetectName)
        , _defectLevel(defectLevel)
        , _confVal(conVal)
    {}

    DetectInfo(const ImageInfo& info)
        : _imgName(info._name.toStdString())
        , _absPath(info._absPath.toStdString())
        , _defectName(info._defectName.toStdString())
        , _defectLevel(info._defectLevel)
        , _confVal(info._confVal)
    {}
};

class projectDlg;
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
    /**
    * @brief: 切换tab事件
    * @param: 
    * @date: 2023/03/03
    */
    void on_imgTabWidget_currentChanged(int index);
    /**
    * @brief: 双击打开检测工程结果文件夹
    * @param: 
    * @date: 2023/03/09
    */
    void on_listWidgetProject_doubleClicked(const QModelIndex &index);
    /**
    * @brief: 更新缺陷等级
    * @param: 
    * @date: 2023/03/15
    */
    void on_comBoxLevel_activated(int index);
    /**
    * @brief: 自定义listwidget槽函数、弹出右键菜单
    * @param: 
    * @date: 2023/03/23
    */
    void on_listWidgetProject_customContextMenuRequested(const QPoint& pos);
    // 删除检测项目 [3/27/2023]
    void deleteProjectItem();
    // 重命名检测项目 [3/27/2023]
    void renameProjectItem();
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
    void detectInfoUtil(QFileInfo& info, int imgIdx=0);
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
    void displayImg(string& imgPath);
    /**
    * @brief: 设置缺陷等级
    * @param: 
    * @date: 2023/03/15
    */
    int setDetectLevel(float confVal);
    // （可复用）辅助函数：在图片 Tab 中添加一个包含图片信息的 widget
    void addImgWidget(const QString& imgName, const QImage& img);
    // （可复用）辅助函数：移除tab [3/18/2023]
    void removeImgWidget();
    // 获取检测项目存储信息 [3/26/2023]
    void getProjectImgInfo(const QString& projectName);
    /**
    * @brief: （可复用）辅助函数：根据获取的检测项目图片信息更新显示
    * @param: 
    * @date: 2023/03/26
    */
    void updateDisplay();
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

    projectDlg* m_wProject;     // 弹出项目窗口 [2/12/2023]
    QString m_projectName;      // 当前项目名称 [3/29/2023]

    bool m_isDetect;            // 是否点击检测按钮 [2/16/2023]

    vector<DetectInfo> m_vecDetectInfo;             // 检测图片信息 [3/15/2023]
    int m_currTabIdx;  // 当前tab id [3/9/2023]

    QStringList m_lstProjects;      // 已保存项目列表 [3/14/2023]

	CProjectDB* m_projectDB;        // 项目配置数据库写入 [3/13/2023]
    CImageDB* m_imageDB;            // 检测后图片数据库写入 [3/14/2023]
    CMapDB* m_mapDB;                // 映射关系数据库 [3/15/2023]

    int m_currProjectIdx;           // 当前项目在数据库中id [3/17/2023]
    QString m_currProjectName;      // 当前项目名称 [3/17/2023]
    vector<ImageInfo> m_vecImgInfo; // 选中检测项目下检测图片信息列表 [3/26/2023]

    friend class projectDlg;
    friend class CProjectDB;
    friend class CImageDB;
    friend class CMapDB;
};
#endif // SEWERCLIENT_H
