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

// ���ͼƬ���� [3/13/2023]
struct ImageInfo
{
	int _idx = -1;
	QString _name;	// �ļ����� [3/17/2023]
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

// ��Ŀ���� [3/13/2023]
class CProjectDB : public CSqlUtils
{
public:
	CProjectDB();
	virtual ~CProjectDB();

	// CRUD [3/13/2023]
	void insertData(const QString& name);	// �������ݸ���ӳ�� [3/17/2023]
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
	* @brief: ��ʼ����
	* @param: 
	* @date: 2023/03/13
	*/
	bool initialProjectTable();
	/**
	* @brief: ��������-IDӳ���ϵ
	* @param: 
	* @date: 2023/03/16
	*/
	void updateMap(const QString& proName);
private:
	unordered_map<QString, int> m_mapNameIdx;	// ����-IDӳ���ϵ [3/16/2023]

	friend class SewerClient;
};

// ��Ŀ�м���޸���ɵ�ͼƬ���� [3/13/2023]
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
	* @brief: ��ȡͼƬ����-����ӳ��
	* @param: 
	* @date: 2023/03/17
	*/
	void loadMapNameIdx();

	bool openDatabase();
	void closeDatabase();
private:
	/**
	* @brief: ��ȡ������ͼƬID
	* @param: 
	* @date: 2023/03/18
	*/
	void getLastImageID();
	// ��ʼ�� [3/18/2023]
	bool initialImageTable();
private:
	unordered_map<QString, ImageInfo> m_mapNameIdx;	// ����-IDӳ���ϵ [3/17/2023]
	int m_lastImgIdx;	// ������ͼƬID [3/18/2023]

	friend class SewerClient;
};

// ӳ���ϵ�� [3/13/2023]
class CMapDB : public CSqlUtils
{
public:
	CMapDB();
	virtual ~CMapDB();

	// CRUD [3/15/2023]
	void insertData(int projectIdx, int imageIdx);
	// ��Ŀ-ͼƬӳ�� [3/17/2023]
	void loadAllMapInfo();
	void deleteDataFromImg(int imageIdx);
	void deleteDataFromProject(int projectIdx);
	void updateImageIdx(int projectIdx, int imageIdx);

	bool openDatabase();
	void closeDatabase();
private:
	bool initialMapTable();
private:
	unordered_map<int, vector<int> > m_mapProImgIdx;		// ��ĿͼƬ [3/17/2023]
};

#endif // !__PROJECTCFG_H__
