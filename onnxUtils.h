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
	int64_t s_numChannels;		// ͨ����
	int64_t s_width;			// ��
	int64_t s_height;			// ��
	int64_t s_numClasses;		// �����Ŀ
	// ����Ԫ������
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
	* @brief: ��ȡ��ʼ������˸����ļ��г�ʼ�������ĵ���init.cfg��
	* @param:
	* @return:
	* ��ʽ: [0]: ԭʼͼƬ·��;[1]������ɺ󱸷�ͼƬ·��;
	* [2]: Ȩ���ļ���·��;[3]: ������·��;[4]: �������·��
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
