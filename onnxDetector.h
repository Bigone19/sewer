#pragma once
#ifndef __ONNXDETECTOR_H__
#define __ONNXDETECTOR_H__

#include <QObject>
#include <QDebug>
#include <onnxruntime_cxx_api.h>

#include "onnxUtils.h"

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
	* @brief: 设置待检测图片文件夹路径
	* @param: 
	*/
	void setRawImgDir();

private:
	Ort::Env m_env;
	Ort::SessionOptions m_sessionOptions;
	Ort::Session m_session;

	QString m_rawImgDir;		// 原始待检测图片路径

	QString m_resultDirPath;	// 处理结果目录路径

	QString m_weightDirPath;	// 权重目录位置
	string m_weightPath;		// 权重位置

	QString m_clsNameDirPath;	// 类别名称目录路径
	string m_clsNamePath;		// 类别名称路径

};

#endif