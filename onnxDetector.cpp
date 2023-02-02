#include "onnxDetector.h"

CDetector::CDetector(Config& config, QObject* parent /*= nullptr*/)
	: QObject(parent)
	, m_env(nullptr)
	, m_sessionOptions(nullptr)
	, m_session(nullptr)
{
	// load config [2/3/2023 Administrator]
	m_inputShape = { 1, config.s_numChannels, config.s_height, config.s_width };
	m_outputShape = { 1, config.s_numClasses };

	// confirm dir & file path [2/2/2023 Administrator]
	setResultDir();
	if (setWeightPath() /* model_troch_export.onnx */)
	{
#ifdef _WIN32
		m_session = Ort::Session(m_env, m_weightPath.c_str(), Ort::SessionOptions{ nullptr });
#else
		m_session = Ort::Session(m_env, m_weightPath.c_str(), Ort::SessionOptions{ nullptr });
#endif
	}
	else
	{
		qDebug() << ERROR_CODE_6;
		assert("加载权重文件错误：没有找到权重文件");
	}
	if (setClsNamePath())
	{
		m_clsNameVec = onnxUtils::loadClsNames(m_clsNamePath);
	}
	else
	{
		qDebug() << ERROR_CODE_7;
		assert("加载类别文件错误：没有找到类别名称文件");
	}
}

CDetector::~CDetector()
{
	m_env.release();
	m_sessionOptions.release();
	m_session.release();

	fill(begin(m_inputShape), end(m_inputShape), 0);
	fill(begin(m_outputShape), end(m_outputShape), 0);
	m_clsNameVec.clear();
}

void CDetector::setResultDir()
{
	QString dirPath = g_vecDirPath.at(3);
	if (dirPath.isEmpty())
	{
		qDebug() << __FUNCTION__ << ERROR_CODE_1;
		return;
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
bool CDetector::setWeightPath()
{
	QString dirPath = g_vecDirPath.at(2);
	if (dirPath.isEmpty())
	{
		qDebug() << __FUNCTION__ << ERROR_CODE_1;
		return false;
	}
	QDir tmpDir(dirPath);
	if (!tmpDir.exists())
	{
		qDebug() << __FUNCTION__ << ERROR_CODE_2;
		return false;
	}
	QString weightPath = dirPath + "model_troch_export.onnx";
	QFile tmpFile(weightPath);
	if (!tmpFile.exists())
	{
		qDebug() << __FUNCTION__ << ERROR_CODE_3;
		return false;
	}
#ifdef _WIN32
	m_weightPath = stringToWstring(weightPath.toStdString());
#else
	m_weightPath = weightPath.toStdString();
#endif
	return true;
}

bool CDetector::setClsNamePath()
{
	QString dirPath = g_vecDirPath.at(4);
	if (dirPath.isEmpty())
	{
		qDebug() << __FUNCTION__ << ERROR_CODE_1;
		return false;
	}
	QDir tmpDir(dirPath);
	if (!tmpDir.exists())
	{
		qDebug() << __FUNCTION__ << ERROR_CODE_4;
		return false;
	}
	QString namesPath = dirPath + "sewer.names";
	QFile tmpFile(namesPath);
	if (!tmpFile.exists())
	{
		qDebug() << __FUNCTION__ << ERROR_CODE_5;
		return false;
	}
	m_clsNamePath = namesPath.toStdString();
	return true;
}

wstring CDetector::stringToWstring(const string& str)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	return converter.from_bytes(str);
}
