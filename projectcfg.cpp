#include "projectcfg.h"

CProjectDB::CProjectDB()
{
	if (QSqlDatabase::contains("qt_sql_default_connection"))
	{
		m_db = QSqlDatabase::database("qt_sql_default_connection");
	}
	else
	{
		m_db = QSqlDatabase::addDatabase("QSQLITE");
	}
	m_db.setDatabaseName("projectInfo.db");
	if (m_db.open())
	{
		qDebug() << "sqlite open success! ";
		// 创建项目数据表 [3/13/2023]
		if (!isTableExists())
		{
			createProjectTable();
		}
	}
}

CProjectDB::~CProjectDB()
{
	m_db.close();
}

bool CProjectDB::createProjectTable()
{
	const QString sql = R"(
		CREATE TABLE IF NOT EXISTS projects_table (
			project_id			INTEGER   PRIMARY KEY AUTOINCREMENT NOT NULL,
			project_name		CHAR (50) UNIQUE NOT NULL
		);
	)";
	QSqlQuery query;
	bool ret = query.exec(sql);
	if (ret)
	{
		qDebug() << "create table success";
	}
	else
	{
		qDebug() << "create table failed" << query.lastError();
	}
	return ret;
}

bool CProjectDB::isTableExists()
{
	const QString sql = R"(
		SELECT name From sqlite_master
		WHERE type='table'
		AND name='projects_table';
	)";
	QSqlQuery query;
	return query.exec(sql);
}

void CProjectDB::insertData(const QString& name)
{
	QSqlQuery query;
	query.exec(QString(
		R"(INSERT INTO projects_table(project_name) VALUES('%1');)"
	).arg(name));
}

void CProjectDB::deleteData(const QString& name)
{
	QSqlQuery query;
	query.exec(QString(
		R"(DELETE FROM projects_table WHERE project_name='%1';)"
	).arg(name));
}

void CProjectDB::updateName(const QString& name)
{
	QSqlQuery query;
	query.exec(QString(
		R"(UPDATE projects_table SET project_name='%1' WHERE project_name='%1';)"
	).arg(name));
}

ProjectInfo CProjectDB::searchData(const QString& name)
{
	ProjectInfo info;
	return info;
}

void CProjectDB::closeDatabase()
{
	m_db.close();
}

CImageDB::CImageDB()
{
}

CImageDB::~CImageDB()
{
	m_db.close();
}

void CImageDB::insertData(const QString& strPath)
{
	QSqlQuery query;
	query.exec(QString(
		R"(INSERT INTO images_table(image_path) VALUES('%1');)"
	).arg(strPath));
}

void CImageDB::deleteData(const QString& strPath)
{

}

void CImageDB::updateName(const QString& strPath)
{

}

ProjectInfo CImageDB::searchData(const QString& strPath)
{

}

bool CImageDB::createImageTable()
{
	const QString sql = R"(
		CREATE TABLE IF NOT EXISTS images_table (
			image_id		INTEGER   PRIMARY KEY AUTOINCREMENT NOT NULL,
			image_path		CHAR (50),
			defect_name		CHAR (50),
			defect_level	INTEGER
		);
	)";
	QSqlQuery query;
	bool ret = query.exec(sql);
	if (ret)
	{
		qDebug() << "create table success";
	}
	else
	{
		qDebug() << "create table failed" << query.lastError();
	}
	return ret;
}

bool CImageDB::isTableExists()
{
	const QString sql = R"(
		SELECT name From sqlite_master
		WHERE type='table'
		AND name='images_table';
	)";
	QSqlQuery query;
	return query.exec(sql);
}

CMapDB::CMapDB()
{

}

CMapDB::~CMapDB()
{
	m_db.close();
}

bool CMapDB::createMapTable()
{

}

bool CMapDB::isTableExists()
{

}
