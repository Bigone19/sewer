#pragma once
#ifndef __ONNXDETECTOR_H__
#define __ONNXDETECTOR_H__

#include <QObject>
#include <QDebug>
#include <onnxruntime_cxx_api.h>

#include <locale>
#include <codecvt>

#include "onnxUtils.h"
#include "config.h"

using std::array;
using std::fill;
using std::begin;
using std::end;
using std::pair;

// ��Ŀ·�� [2/5/2023]
const QString g_projectPath = QDir::currentPath();
// �ļ���·����ʼ�� [2/5/2023]
const string g_initFilePath = g_projectPath.toStdString() + "/init_dir.cfg";
// ��ȡ�ļ������� [2/4/2023]
const vector<QString> g_vecDirPath = fileUtils::loadInitFile(g_initFilePath);

// ȫ��onnx���ýṹ�� [2/3/2023]
constexpr Config g_cfg = { 3, 224, 224, 17 };

class CDetector : public QObject
{
	Q_OBJECT
public:
	CDetector(QObject* parent = nullptr);
	~CDetector();
	/**
	* @brief: ���ͼƬ�������
	* @param: 
	* @date: 2023/02/03
	*/
	vector<pair<size_t, float> > getDetectRes(Mat& srcImage);
	/**
	* @brief: �����ɺ�ʶ��������·���޸�Ϊ��������Ŀ¼
	* @param: 
	* @date: 2023/02/04
	*/
	// ����Ӽ�⵽ȱ������ [2/4/2023]
	void imgName2ResName(const string& imgName, string& resName);
private:
	/**
	* @brief: ����ͼƬ������Ŀ¼
	* @param:
	* @date: 2023/02/02
	*/
	void setResultDir();
	/**
	* @brief: ����ͼȨ��·��
	* @param: 
	* @date: 2023/02/02
	*/
	bool setWeightPath();
	/**
	* @brief: �������·��
	* @param: 
	* @date: 2023/02/02
	*/
	bool setClsNamePath();
	/**
	* @brief:
	* @param:
	* @date: 2023/02/03
	*/
	inline wstring stringToWstring(const string& str);
private:
	Ort::Env m_env;
	Ort::RunOptions m_runOptions;
	Ort::Session m_session;

	QString m_resultDirPath;		// ������Ŀ¼·��
#ifdef _WIN32
	wstring m_weightPath;			// Ȩ��λ��
#else
	string m_weightPath;			// Ȩ��λ��
#endif
	string m_clsNamePath;			// �������·��

	vector<string> m_clsNameVec;	// ����������
};
#endif
