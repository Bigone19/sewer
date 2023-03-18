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

// 检测图片属性 [3/13/2023]
struct ImageInfo
{
	int _idx = -1;
	QString _name;	// 文件名称 [3/17/2023]
	QString _absPath;
	QString _defectName;
	int _defectLevel = 0;

	ImageInfo() {}

	ImageInfo(int idx, const QString& strName, const QString& strPath,
		const QString& defectName, int defectLevel)
		: _idx(idx)
		, _name(strName)
		, _absPath(strPath)
		, _defectName(defectName)
		, _defectLevel(defectLevel)
	{}

	ImageInfo(const QString& strName, const QString& strPath, 
		const QString& defectName, int defectLevel)
		: _name(strName)
		, _absPath(strPath)
		, _defectName(defectName)
		, _defectLevel(defectLevel)
	{}

	ImageInfo& operator=(const ImageInfo& info)
	{
		this->_idx = info._idx;
		this->_name = info._name;
		this->_absPath = info._absPath;
		this->_defectName = info._defectName;
		this->_defectLevel = info._defectLevel;
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
	void insertData(const QString& name);	// 插入数据更新映射 [3/17/2023]
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
	* @brief: 初始化表
	* @param: 
	* @date: 2023/03/13
	*/
	bool initialProjectTable();
	/**
	* @brief: 更新名称-ID映射关系
	* @param: 
	* @date: 2023/03/16
	*/
	void updateMap(const QString& proName);
private:
	unordered_map<QString, int> m_mapNameIdx;	// 名称-ID映射关系 [3/16/2023]

	friend class SewerClient;
};

// 项目中检测修改完成的图片数据 [3/13/2023]
class CImageDB : public CSqlUtils
{
public:
	CImageDB();
	virtual ~CImageDB();

	// CRUD [3/13/2023]
	void insertData(const QString& strName,const QString& strPath, const QString&  defectName, int defectLevel);
	void insertData(ImageInfo& info);	// overload [3/17/2023]
	void deleteData(const QString& strPath);
	void updateDefectName(const QString& strPath, const QString& defectName);
	void updateDefectLevel(const QString& strPath, int defectLevel);
	ImageInfo searchData(const QString& strPath);
	/**
	* @brief: 获取图片名称-属性映射
	* @param: 
	* @date: 2023/03/17
	*/
	void loadMapNameIdx();

	bool openDatabase();
	void closeDatabase();
private:
	/**
	* @brief: 获取最后添加图片ID
	* @param: 
	* @date: 2023/03/18
	*/
	void getLastImageID();
	// 初始化 [3/18/2023]
	bool initialImageTable();
private:
	unordered_map<QString, ImageInfo> m_mapNameIdx;	// 名称-ID映射关系 [3/17/2023]
	int m_lastImgIdx;	// 最后插入图片ID [3/18/2023]

	friend class SewerClient;
};

// 映射关系表 [3/13/2023]
class CMapDB : public CSqlUtils
{
public:
	CMapDB();
	virtual ~CMapDB();

	// CRUD [3/15/2023]
	void insertData(int projectIdx, int imageIdx);
	// 项目-图片映射 [3/17/2023]
	void loadAllMapInfo();
	void deleteDataFromImg(int imageIdx);
	void deleteDataFromProject(int projectIdx);
	void updateImageIdx(int projectIdx, int imageIdx);

	bool openDatabase();
	void closeDatabase();
private:
	bool initialMapTable();
private:
	unordered_map<int, vector<int> > m_mapProImgIdx;		// 项目图片 [3/17/2023]
};

#endif // !__PROJECTCFG_H__
