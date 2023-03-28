#pragma once
#ifndef __DETECTORFACTORY_H__
#define __DETECTORFACTORY_H__

#include "onnxDetector.h"

/************************************************************************/
/* ¼ì²âÆ÷¹¤³§Àà                                                         */
/* 2023/03/28                                                           */
/************************************************************************/

enum DETECTOR_TYPE
{
	RESNET = 0,
	YOLO
};

class CDetectorFactory
{
public:
	static QObject* createDetector(DETECTOR_TYPE type)
	{
		static const std::unordered_map<DETECTOR_TYPE, std::function<QObject* ()>> mapDetector =
		{
			{RESNET, []() {return new CDetector(); }}
			// TODO: YOLO [3/28/2023]
		};
		if (mapDetector.find(type) != mapDetector.end())
		{
			return mapDetector.at(type)();
		}
		else
		{
			return nullptr;
		}
	}
};

#endif // !__DETECTORFACTORY_H__
