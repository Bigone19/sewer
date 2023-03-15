#pragma once
#ifndef __PROJECTCFG_H__
#define __PROJECTCFG_H__

/************************************************************************/
/* 写入检测项目配置写入数据库                                           */
/* 2023/03/11                                                           */
/************************************************************************/

#include <QtCore>
#include <unordered_map>

#include "sqlUtils.h"

using std::vector;
using std::unordered_map;

// 项目属性结构体 [3/13/2023]
struct ImageInfo
{
	QString s_path;
	QString s_defectName;
	int s_defectLevel = 0;

	ImageInfo& operator=(const ImageInfo& info)
	{
		this->s_path = info.s_path;
		this->s_defectName = info.s_defectName;
		this->s_defectLevel = info.s_defectLevel;
		return *this;
	}
};

// 项目数据 [3/13/2023]
class CProjectDB : public CSqlUtils
{
public:
	CProjectDB();
	virtual ~CProjectDB();

	// CRUD [3/13/2023]
	void insertData(const QString& name);
	void deleteData(const QString& name);
	void updateName(const QString& name);
	void getAllProjects(QStringList& lstProjects);
	/**
	* @brief: 打开数据库
	* @param: 
	* @date: 2023/03/14
	*/
	bool openDatabase();
	/**
	* @brief: 关闭数据库
	* @param: 
	* @date: 2023/03/13
	*/
	void closeDatabase();
private:
	/**
	* @brief: 创建表
	* @param: 
	* @date: 2023/03/13
	*/
	bool createProjectTable();
	/**
	* @brief: 更新名称-ID映射关系
	* @param: 
	* @date: 2023/03/16
	*/
	void updateMap();
private:
	unordered_map<QString, int> m_mapNameIdx;	// 名称-ID映射关系 [3/16/2023]
};

// 项目中检测修改完成的图片数据 [3/13/2023]
class CImageDB : public CSqlUtils
{
public:
	CImageDB();
	virtual ~CImageDB();

	// CRUD [3/13/2023]
	void insertData(const QString& strPath, const QString&  defectName, int defectLevel);
	void deleteData(const QString& strPath);
	void updateDefectName(const QString& strPath, const QString& defectName);
	void updateDefectLevel(const QString& strPath, int defectLevel);
	ImageInfo searchData(const QString& strPath);

	bool openDatabase();
	void closeDatabase();
private:
	bool createImageTable();
};

// 映射关系表 [3/13/2023]
class CMapDB : public CSqlUtils
{
public:
	CMapDB();
	virtual ~CMapDB();

	// CRUD [3/15/2023]
	void insertData(int projectIdx, int imageIdx);
	void getAllMapInfo(unordered_map<int, vector<int> >& mapProjectImage);
	void deleteDataFromImg(int imageIdx);
	void deleteDataFromProject(int projectIdx);
	void updateImageIdx(int projectIdx, int imageIdx);

	bool openDatabase();
	void closeDatabase();
private:
	bool createMapTable();
};

#endif // !__PROJECTCFG_H__
