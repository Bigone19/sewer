#include "onnxDetector.h"

CDetector::CDetector(QObject* parent /*= nullptr*/)
	: QObject(parent)
	, m_session(nullptr)
{
	// confirm dir & file path [2/2/2023]
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
	}
	if (setClsNamePath())
	{
		m_clsNameVec = onnxUtils::loadClsNames(m_clsNamePath);
	}
	else
	{
		qDebug() << ERROR_CODE_7;
	}
}

CDetector::~CDetector()
{
	m_env.release();
	m_runOptions.release();
	m_session.release();

	m_clsNameVec.clear();
}

vector<pair<size_t, float>> CDetector::getDetectRes(Mat& srcImage)
{
	cv::cvtColor(srcImage, srcImage, COLOR_BGR2RGB);
	cv::resize(srcImage, srcImage, Size(224, 224));
	srcImage = srcImage.reshape(1, 1);

	vector<float> vec;
	srcImage.convertTo(vec, CV_32FC1, 1. / 255);
	vector<float> imageVec;

	for (size_t ch = 0; ch < 3; ++ch)
	{
		for (size_t i = ch; i < vec.size(); i += 3)
		{
			imageVec.emplace_back(vec[i]);
		}
	}
	// load config [2/3/2023]
	array<int64_t, 4> inputShape = { 1, g_cfg.s_numChannels, g_cfg.s_height, g_cfg.s_width };
	array<int64_t, 2> outputShape = { 1, g_cfg.s_numClasses };

	array<float, g_cfg.s_numInputElements> input;
	array<float, g_cfg.s_numClasses> results;

	auto memory_info = Ort::MemoryInfo::CreateCpu(OrtDeviceAllocator, OrtMemTypeCPU);
	auto inputTensor = Ort::Value::CreateTensor<float>(memory_info, input.data(), input.size(), inputShape.data(), inputShape.size());
	auto outputTensor = Ort::Value::CreateTensor<float>(memory_info, results.data(), results.size(), outputShape.data(), outputShape.size());

	std::copy(imageVec.begin(), imageVec.end(), input.begin());

	// define names
	Ort::AllocatorWithDefaultOptions ort_alloc;
	const char* inputName = m_session.GetInputName(0, ort_alloc);
	const char* outputName = m_session.GetOutputName(0, ort_alloc);
	const std::array<const char*, 1> inputNames = { inputName };
	const std::array<const char*, 1> outputNames = { outputName };

	// run inference
	try
	{
		m_session.Run(m_runOptions, inputNames.data(), &inputTensor, 1, outputNames.data(), &outputTensor, 1);
	}
	catch (Ort::Exception& e)
	{
		assert(e.what());
	}

	// sort results
	vector<pair<size_t, float>> indexValuePairs;

	for (size_t i = 0; i < results.size(); ++i)
	{
		indexValuePairs.emplace_back(i, results[i]);
	}
	std::sort(indexValuePairs.begin(), indexValuePairs.end(), [](const auto& lhs, const auto& rhs) { return lhs.second > rhs.second; });

	for (size_t i = 0; i < 5; ++i)
	{
		const auto& result = indexValuePairs[i];
		qDebug() << i + 1 << ": " << QString::fromLocal8Bit(m_clsNameVec[result.first]) << " " << result.second << Qt::endl;
	}

	return indexValuePairs;
}

void CDetector::imgName2ResName(const string& imgName, string& resName)
{
	resName = m_resultDirPath.toStdString() + imgName;
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
