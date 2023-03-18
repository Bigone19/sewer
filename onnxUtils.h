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
	int64_t _numChannels;		// 通道数
	int64_t _width;			// 宽
	int64_t _height;			// 高
	int64_t _numClasses;		// 类别数目
	// 输入元素数量
	int64_t _numInputElements = this->_numChannels * this->_height * this->_width;

	Config& operator=(const Config& cfg)
	{
		this->_numChannels = cfg._numChannels;
		this->_width = cfg._width;
		this->_height = cfg._height;
		this->_numClasses = cfg._numClasses;
		this->_numInputElements = cfg._numInputElements;
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
	* [5]: docx结果位置
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
