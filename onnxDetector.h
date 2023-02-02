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
// <============ 获取文件夹名称 ==============>
const vector<QString> g_vecDirPath = fileUtils::loadInitFile();

class CDetector : public QObject
{
	Q_OBJECT
public:
	CDetector(Config& config, QObject* parent = nullptr);
	~CDetector();

private:
	/**
	* @brief: 设置图片处理结果目录
	* @param:
	* @date: 2023/02/02
	*/
	void setResultDir();
	/**
	* @brief: 设置图权重路径
	* @param: 
	* @date: 2023/02/02
	*/
	bool setWeightPath();
	/**
	* @brief: 类别名称路径
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

	QString m_resultDirPath;		// 处理结果目录路径
#ifdef _WIN32
	wstring m_weightPath;			// 权重位置
#else
	string m_weightPath;			// 权重位置
#endif
	string m_clsNamePath;			// 类别名称路径

	vector<string> m_clsNameVec;	// 检测类别名称
};

#endif