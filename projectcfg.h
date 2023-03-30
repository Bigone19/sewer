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
#include "sqlOperation.h"

using std::vector;
using std::unordered_map;

// 检测图片属性 [3/13/2023]
struct ImageInfo
{
	int _idx = -1;
	QString _name;			// 文件名称 [3/17/2023]
	QString _absPath;		// 图片路径 [3/26/2023]
	QString _defectName;	// 缺陷名称 [3/26/2023]
	int _defectLevel = 0;	// 缺陷等级 [3/26/2023]
	float _confVal = 0.0f;	// 置信值 [3/26/2023]

	ImageInfo() {}

	ImageInfo(int idx, const QString& strName, const QString& strPath,
		const QString& defectName, int defectLevel, float confVal)
		: _idx(idx)
		, _name(strName)
		, _absPath(strPath)
		, _defectName(defectName)
		, _defectLevel(defectLevel)
		, _confVal(confVal)
	{}

	ImageInfo(const QString& strName, const QString& strPath, 
		const QString& defectName, int defectLevel, float confVal)
		: _name(strName)
		, _absPath(strPath)
		, _defectName(defectName)
		, _defectLevel(defectLevel)
		, _confVal(confVal)
	{}

	ImageInfo& operator=(const ImageInfo& info)
	{
		this->_idx = info._idx;
		this->_name = info._name;
		this->_absPath = info._absPath;
		this->_defectName = info._defectName;
		this->_defectLevel = info._defectLevel;
		this->_confVal = info._confVal;
		return *this;
	}
};

// 项目数据 [3/13/2023]
class CProjectDB : public CSqlUtils, public CSqlOperation
{
public:
	static CProjectDB* getInstance();
	virtual ~CProjectDB();

	// CRUD [3/13/2023]
	void insertData(const QString& name);	// 插入数据更新映射 [3/17/2023]
	void updateName(const QString& oldName, const QString& name);
	void getAllProjects(QStringList& lstProjects);

	// 基类函数 [3/27/2023]
	virtual bool openDatabase() override;
	virtual void closeDatabase() override;
	virtual bool initialTable() override;
	virtual void deleteData(const QString& name) override;

private:
	CProjectDB();
	/**
	* @brief: 更新名称-ID映射关系
	* @param: 
	* @date: 2023/03/16
	*/
	void updateMap(const QString& proName);
private:
	static CProjectDB* m_pInstance;

	unordered_map<QString, int> m_mapNameIdx;	// 名称-ID映射关系 [3/16/2023]

	friend class SewerClient;
};

// 项目中检测修改完成的图片数据 [3/13/2023]
class CImageDB : public CSqlUtils, public CSqlOperation
{
public:
	static CImageDB* getInstance();
	virtual ~CImageDB();

	// CRUD [3/13/2023]
	void insertData(ImageInfo& info);
	void updateDefectName(const QString& strPath, const QString& defectName);
	void updateDefectLevel(const QString& strPath, int defectLevel);
	ImageInfo searchData(const QString& strPath);
	ImageInfo searchData(const int imgId);
	/**
	* @brief: 获取图片名称-属性映射
	* @param: 
	* @date: 2023/03/17
	*/
	void loadMapNameIdx();

	// 基类函数 [3/27/2023]
	virtual bool openDatabase() override;
	virtual void closeDatabase() override;
	virtual bool initialTable() override;
	virtual void deleteData(const QString& strPath) override;

private:
	CImageDB();
	/**
	* @brief: 获取最后添加图片ID、用于插入图片后更新映射关系
	* @param: 
	* @date: 2023/03/18
	*/
	void getLastImageID();

private:
	static CImageDB* m_pInstance;

	unordered_map<QString, ImageInfo> m_mapNameIdx;	// 名称-ID映射关系 [3/17/2023]
	int m_lastImgIdx;	// 最后插入图片ID [3/18/2023]

	friend class SewerClient;
};

// 映射关系表 [3/13/2023]
class CMapDB : public CSqlUtils, public CSqlOperation
{
public:
	static CMapDB* getInstance();

	virtual ~CMapDB();
	// CRUD [3/15/2023]
	void insertData(int projectIdx, int imageIdx);
	// 项目-图片映射 [3/17/2023]
	void loadAllMapInfo();
	void deleteDataFromImg(int imageIdx);
	void deleteDataFromProject(int projectIdx);
	void updateImageIdx(int projectIdx, int imageIdx);

	// 基类函数 [3/27/2023]
	virtual bool openDatabase() override;
	virtual void closeDatabase() override;
	virtual bool initialTable() override;
	virtual void deleteData(const QString& name) {};
private:
	CMapDB();

private:
	static CMapDB* m_pInstance;
	unordered_map<int, vector<int> > m_mapProImgIdx;		// 项目图片 [3/17/2023]

	friend class SewerClient;
};


#endif // !__PROJECTCFG_H__
