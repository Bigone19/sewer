#pragma once
#ifndef __ONNXDETECTOR_H__
#define __ONNXDETECTOR_H__

#include <QObject>
#include <QDebug>
#include <onnxruntime_cxx_api.h>

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
	void setWeightPath();
	/**
	* @brief: 类别名称路径
	* @param: 
	* @date: 2023/02/02
	*/
	void setClsNamePath();
private:
	Ort::Env m_env;
	Ort::SessionOptions m_sessionOptions;
	Ort::Session m_session;

	QString m_resultDirPath;	// 处理结果目录路径

	string m_weightPath;		// 权重位置

	QString m_clsNameDirPath;	// 类别名称目录路径
	string m_clsNamePath;		// 类别名称路径

};

#endif