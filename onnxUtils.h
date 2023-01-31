#pragma once
#ifndef __ONNXCONFIG_H__
#define __ONNXCONFIG_H__

#include <utility>

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

#endif