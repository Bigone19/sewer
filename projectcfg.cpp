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
            project_id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
            project_name CHAR (50) UNIQUE NOT NULL
        )
    )";
	QSqlQuery query;
	if (query.exec(sql))
	{
		qDebug() << "initial projects table success";
		return true;
	}
	else
	{
		qWarning() << "failed to create projects table: " << query.lastError().text();
		return false;
	}
}


void CProjectDB::updateMap()
{

}

void CProjectDB::insertData(const QString& name)
{
	QSqlQuery query;
	bool ret = query.exec(QString(
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

// 仅启动初始化时加载一次 [3/16/2023]
void CProjectDB::getAllProjects(QStringList& lstProjects)
{
	// 获取全部项目列表 [3/14/2023]
	QSqlQuery query;
	query.exec(QString(
		R"(SELECT * FROM projects_table;)"
	));
	while (query.next())
	{
		int proIdx = query.value(0).toInt();
		QString proName = query.value(1).toString();
		lstProjects.append(proName);
		// 初始化当前名称-ID映射关系 [3/16/2023]
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
	QString strSql = R"(UPDATE images_table SET defect_name=:defectName WHERE image_path=:imagePath)";
	query.prepare(strSql);

	query.bindValue(":imagePath", strPath);
	query.bindValue(":defectName", defectName);
	if (!query.exec()) 
	{
		qDebug() << "Failed to execute updateDefectName query: " << query.lastError().text();
		return;
	}
}

void CImageDB::updateDefectLevel(const QString& strPath, int defectLevel)
{
	QSqlQuery query;
	query.prepare("UPDATE images_table SET defect_level= :defectLevel WHERE image_path=:path");
	query.bindValue(":defectLevel", defectLevel);
	query.bindValue(":path", strPath);
	query.exec();
}

ImageInfo CImageDB::searchData(const QString& strPath)
{
	ImageInfo info;
	info.s_path = strPath;
	QSqlQuery query;
	query.prepare("SELECT defect_name, defect_level FROM images_table WHERE image_path=:path");
	query.bindValue(":path", strPath);
	if (query.exec() && query.next()) 
	{
		info.s_defectName = query.value(0).toString();
		info.s_defectLevel = query.value(1).toInt();
	}
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
		qDebug() << "initial image table success";
	}
	else
	{
		qDebug() << "create image table failed" << query.lastError();
	}
	return ret;
}

CMapDB::CMapDB()
{
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

void CMapDB::insertData(int projectIdx, int imageIdx)
{
	QSqlQuery query;
	query.exec(QString(
		R"(INSERT INTO mapProjectImage_table(project_id, image_id) VALUES(%1,%2))"
	).arg(projectIdx).arg(imageIdx));
}

void CMapDB::getAllMapInfo(unordered_map<int, vector<int>>& mapProjectImage)
{
	QSqlQuery query;
	query.exec(QString(
		R"(SELECT * FROM mapProjectImage_table;)"
	));
	while (query.next())
	{
		int projectIdx = query.value(1).toInt();
		int imageIdx = query.value(2).toInt();
		if (mapProjectImage.find(projectIdx) != mapProjectImage.end())
		{
			mapProjectImage[projectIdx].emplace_back(imageIdx);
		}
		else
		{
			// 未插入项目id补充 [3/16/2023]
			mapProjectImage.emplace(projectIdx, imageIdx);
		}
	}
}

void CMapDB::deleteDataFromImg(int imageIdx)
{
	QSqlQuery query;
	query.exec(QString(
		R"(DELETE FROM mapProjectImage_table WHERE image_id=%1)"
	).arg(imageIdx));
}

void CMapDB::deleteDataFromProject(int projectIdx)
{
	QSqlQuery query;
	query.exec(QString(
		R"(DELETE FROM mapProjectImage_table WHERE project_id=%1)"
	).arg(projectIdx));
}

void CMapDB::updateImageIdx(int projectIdx, int imageIdx)
{
	QSqlQuery query;
	query.exec(QString(
		R"(UPDATE mapProjectImage_table SET project_id=%1 WHERE image_id=%2)"
	).arg(projectIdx).arg(imageIdx));
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
			image_id	INTEGER		UNIQUE NOT NULL
		);
	)";
	QSqlQuery query;
	bool ret = query.exec(sql);
	if (ret)
	{
		qDebug() << "initial map table success";
	}
	else
	{
		qDebug() << "create map table failed" << query.lastError();
	}
	return ret;
}
