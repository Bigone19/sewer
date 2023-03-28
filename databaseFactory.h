#pragma once
#ifndef __DATABASEFACTORY_H__
#define __DATABASEFACTORY_H__

#include "projectcfg.h"

/************************************************************************/
/* 数据库工厂类                                                         */
/* 2023/03/27                                                           */
/************************************************************************/

enum DATABASE_TYPE
{
	PROJECT_DB = 0,
	IMAGE_DB,
	MAP_DB
};

class CDatabaseFactory
{
	using CreateSqlOpFunc = std::function<CSqlOperation* ()>;

public:
	static CSqlOperation* createDB(DATABASE_TYPE type)
	{
		// 数据库类型映射 [3/27/2023]
		static const std::unordered_map<DATABASE_TYPE, CreateSqlOpFunc> mapDatabase =
		{
			{PROJECT_DB, &CProjectDB::getInstance},
			{IMAGE_DB, &CImageDB::getInstance},
			{MAP_DB, &CMapDB::getInstance}
		};
		// 获取数据库单例 [3/27/2023]
		unordered_map<DATABASE_TYPE, CreateSqlOpFunc>::const_iterator iter = mapDatabase.find(type);
		if (iter != mapDatabase.end())
		{
			return iter->second();
		}
		else
		{
			return nullptr;
		}
	}
};

#endif // !__DATABASEFACTORY_H__
