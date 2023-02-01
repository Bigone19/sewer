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
}
