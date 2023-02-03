//  [2/2/2023]
#pragma once
#ifndef __ONNXCONFIG_H__
#define __ONNXCONFIG_H__

/************************************************************************/
/* onnx配置结构体、配置文件读取                                         */
/* 2023/02/02                                                           */
/************************************************************************/

#include <utility>
#include <vector>
#include <string>
#include <fstream>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/dnn.hpp>

#include <QtCore>

using namespace cv;
using std::vector;
using std::string;
using std::wstring;
using std::ifstream;

struct Config
{
	int64_t s_numChannels;		// 通道数
	int64_t s_width;			// 宽
	int64_t s_height;			// 高
	int64_t s_numClasses;		// 类别数目
	// 输入元素数量
	int64_t s_numInputElements = this->s_numChannels * this->s_height * this->s_width;

	Config& operator=(const Config& cfg)
	{
		this->s_numChannels = cfg.s_numChannels;
		this->s_width = cfg.s_width;
		this->s_height = cfg.s_height;
		this->s_numClasses = cfg.s_numClasses;
		this->s_numInputElements = cfg.s_numInputElements;
		return *this;
	}
};

namespace fileUtils
{
	/**
	* @brief: 读取初始化服务端各个文件夹初始化配置文档（init.cfg）
	* @param:
	* @return:
	* 格式: [0]: 原始图片路径;[1]处理完成后备份图片路径;
	* [2]: 权重文件夹路径;[3]: 处理结果路径;[4]: 类别名称路径
	*/
	vector<QString> loadInitFile(const string& initialFilePath);
}

namespace onnxUtils
{
	/**
	* @brief: 加载检测类名
	* @param: 
	* @date: 2023/02/02
	*/
	vector<string> loadClsNames(const string& path);
}
#endif
