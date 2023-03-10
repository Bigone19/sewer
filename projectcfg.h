#pragma once
#ifndef __PROJECTCFG_H__
#define __PROJECTCFG_H__

/************************************************************************/
/* 写入检测项目配置保存为yaml                                                                     */
/* 2023/03/11                                                           */
/************************************************************************/

#include "yaml-cpp/yaml.h"

using namespace YAML;

class CProjectCfg
{
public:
	CProjectCfg();
	virtual ~CProjectCfg();
private:
};

#endif // !__PROJECTCFG_H__
