#include "onnxDetector.h"

CDetector::CDetector(Config& config, QObject* parent /*= nullptr*/)
	: QObject(parent)
	, m_env(nullptr)
	, m_sessionOptions(nullptr)
	, m_session(nullptr)
{
}

CDetector::~CDetector()
{

}

void CDetector::setRawImgDir()
{
	QString dirPath = g_vecDirPath.at(0);
	if (dirPath.isEmpty())
	{
		qDebug() << ERROR_CODE_1;
	}
	QDir tmpDir(dirPath);
	m_rawImgDir = dirPath;
}
