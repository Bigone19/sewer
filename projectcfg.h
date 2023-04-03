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
#include "sqlOperation.h"

using std::vector;
using std::unordered_map;

// ���ͼƬ���� [3/13/2023]
struct ImageInfo
{
	int _idx = -1;
	QString _name;			// �ļ����� [3/17/2023]
	QString _absPath;		// ͼƬ·�� [3/26/2023]
	QString _defectName;	// ȱ������ [3/26/2023]
	int _defectLevel = 0;	// ȱ�ݵȼ� [3/26/2023]
	float _confVal = 0.0f;	// ����ֵ [3/26/2023]

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

// ��Ŀ���� [3/13/2023]
class CProjectDB : public CSqlUtils, public CSqlOperation
{
public:
	static CProjectDB* getInstance();
	virtual ~CProjectDB();

	// CRUD [3/13/2023]
	void insertData(const QString& name);	// �������ݸ���ӳ�� [3/17/2023]
	void updateName(const QString& oldName, const QString& name);
	void getAllProjects(QStringList& lstProjects);

	// ���ຯ�� [3/27/2023]
	virtual bool openDatabase() override;
	virtual void closeDatabase() override;
	virtual bool initialTable() override;
	virtual void deleteData(const QString& name) override;

private:
	CProjectDB();
	/**
	* @brief: ��������-IDӳ���ϵ
	* @param: 
	* @date: 2023/03/16
	*/
	void updateMap(const QString& proName);
private:
	static CProjectDB* m_pInstance;

	unordered_map<QString, int> m_mapNameIdx;	// ����-IDӳ���ϵ [3/16/2023]

	friend class SewerClient;
};

// ��Ŀ�м���޸���ɵ�ͼƬ���� [3/13/2023]
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
	* @brief: ��ȡͼƬ����-����ӳ��
	* @param: 
	* @date: 2023/03/17
	*/
	void loadMapNameIdx();

	// ���ຯ�� [3/27/2023]
	virtual bool openDatabase() override;
	virtual void closeDatabase() override;
	virtual bool initialTable() override;
	virtual void deleteData(const QString& strPath) override;

private:
	CImageDB();
	/**
	* @brief: ��ȡ������ͼƬID�����ڲ���ͼƬ�����ӳ���ϵ
	* @param: 
	* @date: 2023/03/18
	*/
	void getLastImageID();

private:
	static CImageDB* m_pInstance;

	unordered_map<QString, ImageInfo> m_mapNameIdx;	// ����-IDӳ���ϵ [3/17/2023]
	int m_lastImgIdx;	// ������ͼƬID [3/18/2023]

	friend class SewerClient;
};

// ӳ���ϵ�� [3/13/2023]
class CMapDB : public CSqlUtils, public CSqlOperation
{
public:
	static CMapDB* getInstance();

	virtual ~CMapDB();
	// CRUD [3/15/2023]
	void insertData(int projectIdx, int imageIdx);
	// ��Ŀ-ͼƬӳ�� [3/17/2023]
	void loadAllMapInfo();
	void deleteDataFromImg(int imageIdx);
	void deleteDataFromProject(int projectIdx);
	void updateImageIdx(int projectIdx, int imageIdx);

	// ���ຯ�� [3/27/2023]
	virtual bool openDatabase() override;
	virtual void closeDatabase() override;
	virtual bool initialTable() override;
	virtual void deleteData(const QString& name) {};
private:
	CMapDB();

private:
	static CMapDB* m_pInstance;
	unordered_map<int, vector<int> > m_mapProImgIdx;		// ��ĿͼƬ [3/17/2023]

	friend class SewerClient;
};


#endif // !__PROJECTCFG_H__
