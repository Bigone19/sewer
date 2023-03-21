//  [2/2/2023]
#pragma once
#ifndef __ONNXCONFIG_H__
#define __ONNXCONFIG_H__

/************************************************************************/
/* onnx���ýṹ�塢�����ļ���ȡ                                         */
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
	int64_t _numChannels;		// ͨ����
	int64_t _width;			// ��
	int64_t _height;			// ��
	int64_t _numClasses;		// �����Ŀ
	// ����Ԫ������
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
	* @brief: ��ȡ��ʼ������˸����ļ��г�ʼ�������ĵ���init.cfg��
	* @param:
	* @return:
	* ��ʽ: [0]: ԭʼͼƬ·��;[1]������ɺ󱸷�ͼƬ·��;
	* [2]: Ȩ���ļ���·��;[3]: ������·��;[4]: �������·��
	* [5]: docx���λ��
	*/
	vector<QString> loadInitFile(const string& initialFilePath);
}

namespace onnxUtils
{
	/**
	* @brief: ���ؼ������
	* @param: 
	* @date: 2023/02/02
	*/
	vector<string> loadClsNames(const string& path);
}

#endif
