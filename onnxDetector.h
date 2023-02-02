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

//  [2/2/2023 Administrator]
// <============ ��ȡ�ļ������� ==============>
const vector<QString> g_vecDirPath = fileUtils::loadInitFile();

class CDetector : public QObject
{
	Q_OBJECT
public:
	CDetector(Config& config, QObject* parent = nullptr);
	~CDetector();

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
	Ort::SessionOptions m_sessionOptions;
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