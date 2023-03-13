#include "projectcfg.h"

CProjectDB::CProjectDB()
{
	if (m_db.open())
	{
		// 创建项目数据表 [3/13/2023]
		createProjectTable();
	}
}

CProjectDB::~CProjectDB()
{
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
		qDebug() << "initial projects table success";
	}
	else
	{
		qDebug() << query.lastError();
	}
	return ret;
}

void CProjectDB::insertData(const QString& name)
{
	QSqlQuery query;
	bool ret = query.exec(QString(
		R"(INSERT INTO projects_table(project_name) VALUES('%1');)"
	).arg(name));
	qDebug() << "create table failed" << query.lastError();
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

void CProjectDB::getAllProjects(QStringList& lstProjects)
{
	// 获取全部项目列表 [3/14/2023]
	QSqlQuery query;
	query.exec(QString(
		R"(SELECT * FROM projects_table;)"
	));
	while (query.next())
	{
		lstProjects.append(query.value(1).toString());
	}
}

bool CProjectDB::openDatabase()
{
	if (!m_db.isOpen())
	{
		return m_db.open();
	}
	return true;
}

void CProjectDB::closeDatabase()
{
	m_db.close();
}

CImageDB::CImageDB()
{
	if (QSqlDatabase::contains("qt_sql_default_connection"))
	{
		m_db = QSqlDatabase::database("qt_sql_default_connection");
	}
	else
	{
		m_db = QSqlDatabase::addDatabase("QSQLITE");
	}
	m_db.setDatabaseName("imageInfo.db");
	if (m_db.open())
	{
		// 创建图片表 [3/14/2023]
		createImageTable();
	}
}

CImageDB::~CImageDB()
{
	m_db.close();
}

void CImageDB::insertData(const QString& strPath, const QString& defectName, int defectLevel)
{
	QSqlQuery query;
	query.exec(QString(
		R"(INSERT INTO images_table(image_path,defect_name,defect_level) VALUES('%1','%2',%3);)"
	).arg(strPath).arg(defectName).arg(defectLevel));
}

void CImageDB::deleteData(const QString& strPath)
{
	QSqlQuery query;
	query.exec(QString(
		R"(DELETE FROM images_table WHERE image_path='%1';)"
	).arg(strPath));
}

void CImageDB::updateDefectName(const QString& strPath, const QString& defectName)
{
	QSqlQuery query;
	query.exec(QString(
		R"(UPDATE images_table SET defect_name='%2' WHERE image_path='%1';)"
	).arg(strPath).arg(defectName));
}

void CImageDB::updateDefectLevel(const QString& strPath, int defectLevel)
{
	QSqlQuery query;
	query.exec(QString(
		R"(UPDATE images_table SET defect_level=%2 WHERE image_path='%1';)"
	).arg(strPath).arg(defectLevel));
}

ImageInfo CImageDB::searchData(const QString& strPath)
{
	ImageInfo info;
	info.s_path = strPath;
	QSqlQuery query;
	query.exec(QString(
		R"(SELECT defect_name,defect_level FROM images_table
			WHERE image_path='%1';)"
	));
	info.s_defectName = query.value(0).toString();
	info.s_defectLevel = query.value(1).toInt();
	return info;
}

bool CImageDB::openDatabase()
{
	if (!m_db.isOpen())
	{
		return m_db.open();
	}
	return true;
}

void CImageDB::closeDatabase()
{
	m_db.close();
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

CMapDB::CMapDB()
{
	if (QSqlDatabase::contains("qt_sql_default_connection"))
	{
		m_db = QSqlDatabase::database("qt_sql_default_connection");
	}
	else
	{
		m_db = QSqlDatabase::addDatabase("QSQLITE");
	}
	m_db.setDatabaseName("mapInfo.db");
	if (m_db.open())
	{
		// 创建映射表 [3/14/2023]
		createMapTable();
	}
}

CMapDB::~CMapDB()
{
	m_db.close();
}

bool CMapDB::openDatabase()
{
	if (!m_db.isOpen())
	{
		return m_db.open();
	}
	return true;
}

void CMapDB::closeDatabase()
{
	m_db.close();
}

bool CMapDB::createMapTable()
{
	const QString sql = R"(
		CREATE TABLE IF NOT EXISTS mapProjectImage_table (
			map_id		INTEGER		PRIMARY KEY AUTOINCREMENT NOT NULL,
			project_id	INTEGER		UNIQUE NOT NULL,
			image_id	INTEGER		NOT NULL
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
