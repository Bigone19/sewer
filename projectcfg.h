#pragma once
#ifndef __PROJECTCFG_H__
#define __PROJECTCFG_H__

/************************************************************************/
/* д������Ŀ����д�����ݿ�                                           */
/* 2023/03/11                                                           */
/************************************************************************/

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtCore>

// ��Ŀ���Խṹ�� [3/13/2023]
struct ProjectInfo
{
	QString s_name;
	QString s_defectName;
	int s_defectLevel;

	ProjectInfo& operator=(const ProjectInfo& info)
	{
		this->s_name = info.s_name;
		this->s_defectName = info.s_defectName;
		this->s_defectLevel = info.s_defectLevel;
		return *this;
	}
};

class CMapDB;
class CImageDB;
// ��Ŀ���� [3/13/2023]
class CProjectDB
{
public:
	CProjectDB();
	virtual ~CProjectDB();

	// CRUD [3/13/2023]
	void insertData(const QString& name);
	void deleteData(const QString& name);
	void updateName(const QString& name);
	ProjectInfo searchData(const QString& name);
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
	/**
	* @brief: ����Ƿ���Ѵ���
	* @param: 
	* @date: 2023/03/13
	*/
	bool isTableExists();

private:
	QSqlDatabase m_db;

	friend class CImageDB;
};

// ��Ŀ�м���޸���ɵ�ͼƬ���� [3/13/2023]
class CImageDB
{
public:
	CImageDB();
	virtual ~CImageDB();

	// CRUD [3/13/2023]
	void insertData(const QString& strPath);
	void deleteData(const QString& strPath);
	void updateName(const QString& strPath);
	ProjectInfo searchData(const QString& strPath);

private:
	bool createImageTable();
	bool isTableExists();
private:
	QSqlDatabase m_db;
};

// ӳ���ϵ�� [3/13/2023]
class CMapDB
{
public:
	CMapDB();
	virtual ~CMapDB();
private:
	bool createMapTable();
	bool isTableExists();
private:
	QSqlDatabase m_db;
};

#endif // !__PROJECTCFG_H__
