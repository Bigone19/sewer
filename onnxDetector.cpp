#include "onnxDetector.h"

CDetector::CDetector(Config& config, QObject* parent /*= nullptr*/)
	: QObject(parent)
	, m_env(nullptr)
	, m_sessionOptions(nullptr)
	, m_session(nullptr)
{
	// update [2/2/2023 Administrator]
	setResultDir();
	setWeightPath(); // model_troch_export.onnx
}

CDetector::~CDetector()
{

}

void CDetector::setResultDir()
{
	QString dirPath = g_vecDirPath.at(3);
	if (dirPath.isEmpty())
	{
		qDebug() << __FUNCTION__ << ERROR_CODE_1;
	}
	QDir tmpDir(dirPath);
	if (!tmpDir.exists())
	{
		tmpDir.mkdir(dirPath);
		qDebug() << __FUNCTION__ << QString::fromLocal8Bit("已设置备份图片路径 ");
	}
	m_resultDirPath = dirPath;
}

/************************************************************************/
/* 获取model_troch_export.onnx位置                                      */
/* add date: 2023/2/2                                                  */
/************************************************************************/
void CDetector::setWeightPath()
{
	QString dirPath = g_vecDirPath.at(2);
	if (dirPath.isEmpty())
	{
		qDebug() << __FUNCTION__ << ERROR_CODE_1;
	}
	QDir tmpDir(dirPath);
	if (!tmpDir.exists())
	{
		qDebug() << __FUNCTION__ << ERROR_CODE_2;
		return;
	}
	QString weightPath = dirPath + "model_troch_export.onnx";
	QFile tmpFile(weightPath);
	if (!tmpFile.exists())
	{
		qDebug() << __FUNCTION__ << ERROR_CODE_3;
		return;
	}
	m_weightPath = weightPath.toStdString();
}

void CDetector::setClsNamePath()
{
	QString dirPath = g_vecDirPath.at(4);
	if (dirPath.isEmpty())
	{
		qDebug() << __FUNCTION__ << ERROR_CODE_1;
	}
	QDir tmpDir(dirPath);
	if (!tmpDir.exists())
	{
		qDebug() << __FUNCTION__ << ERROR_CODE_4;
		return;
	}
	QString weightPath = dirPath + "";
	QFile tmpFile(weightPath);

}
