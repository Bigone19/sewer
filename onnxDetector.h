#pragma once
#ifndef __ONNXDETECTOR_H__
#define __ONNXDETECTOR_H__

#include <QObject>
#include <QDebug>
#include <onnxruntime_cxx_api.h>

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
	void setWeightPath();
	/**
	* @brief: �������·��
	* @param: 
	* @date: 2023/02/02
	*/
	void setClsNamePath();
private:
	Ort::Env m_env;
	Ort::SessionOptions m_sessionOptions;
	Ort::Session m_session;

	QString m_resultDirPath;	// ������Ŀ¼·��

	string m_weightPath;		// Ȩ��λ��

	QString m_clsNameDirPath;	// �������Ŀ¼·��
	string m_clsNamePath;		// �������·��

};

#endif