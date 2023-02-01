#pragma once
#ifndef __ONNXDETECTOR_H__
#define __ONNXDETECTOR_H__

#include <QObject>
#include <QDebug>
#include <onnxruntime_cxx_api.h>

#include "onnxUtils.h"

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
	* @brief: ���ô����ͼƬ�ļ���·��
	* @param: 
	*/
	void setRawImgDir();

private:
	Ort::Env m_env;
	Ort::SessionOptions m_sessionOptions;
	Ort::Session m_session;

	QString m_rawImgDir;		// ԭʼ�����ͼƬ·��

	QString m_resultDirPath;	// ������Ŀ¼·��

	QString m_weightDirPath;	// Ȩ��Ŀ¼λ��
	string m_weightPath;		// Ȩ��λ��

	QString m_clsNameDirPath;	// �������Ŀ¼·��
	string m_clsNamePath;		// �������·��

};

#endif