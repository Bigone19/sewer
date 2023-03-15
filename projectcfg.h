#pragma once
#ifndef __PROJECTCFG_H__
#define __PROJECTCFG_H__

/************************************************************************/
/* д������Ŀ����д�����ݿ�                                           */
/* 2023/03/11                                                           */
/************************************************************************/

#include <QtCore>
#include <unordered_map>

#include "sqlUtils.h"

using std::vector;
using std::unordered_map;

// ��Ŀ���Խṹ�� [3/13/2023]
struct ImageInfo
{
	QString s_path;
	QString s_defectName;
	int s_defectLevel;

	ImageInfo& operator=(const ImageInfo& info)
	{
		this->s_path = info.s_path;
		this->s_defectName = info.s_defectName;
		this->s_defectLevel = info.s_defectLevel;
		return *this;
	}
};

class CMapDB;
class CImageDB;
// ��Ŀ���� [3/13/2023]
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
	* @brief: �����ݿ�
	* @param: 
	* @date: 2023/03/14
	*/
	bool openDatabase();
	/**
	* @brief: �ر����ݿ�
	* @param: 
	* @date: 2023/03/13
	*/
	void closeDatabase();
private:
	/**
	* @brief: ������
	* @param: 
	* @date: 2023/03/13
	*/
	bool createProjectTable();
};

// ��Ŀ�м���޸���ɵ�ͼƬ���� [3/13/2023]
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

// ӳ���ϵ�� [3/13/2023]
class CMapDB : public CSqlUtils
{
public:
	CMapDB();
	virtual ~CMapDB();

	// CRUD [3/15/2023]
	void insertData(int projectIdx, int imageIdx);
	void getAllMapInfo(unordered_map<int, vector<int> >& mapProjectImage);

	bool openDatabase();
	void closeDatabase();
private:
	bool createMapTable();
};

#endif // !__PROJECTCFG_H__
