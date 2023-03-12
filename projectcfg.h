#pragma once
#ifndef __PROJECTCFG_H__
#define __PROJECTCFG_H__

/************************************************************************/
/* 写入检测项目配置写入数据库                                           */
/* 2023/03/11                                                           */
/************************************************************************/

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtCore>

// 项目属性结构体 [3/13/2023]
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
// 项目数据 [3/13/2023]
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
	* @brief: 检查是否表已存在
	* @param: 
	* @date: 2023/03/13
	*/
	bool isTableExists();

private:
	QSqlDatabase m_db;

	friend class CImageDB;
};

// 项目中检测修改完成的图片数据 [3/13/2023]
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

// 映射关系表 [3/13/2023]
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
