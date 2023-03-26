#include "projectcfg.h"

CProjectDB* CProjectDB::m_pInstance = nullptr;

CProjectDB* CProjectDB::getInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new CProjectDB();
	}
	return m_pInstance;
}

CProjectDB::CProjectDB()
{
	if (m_db.open())
	{
		// 创建项目数据表 [3/13/2023]
		initialProjectTable();
	}
}

CProjectDB::~CProjectDB()
{
	m_mapNameIdx.clear();
}

bool CProjectDB::initialProjectTable()
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


void CProjectDB::updateMap(const QString& proName)
{
	QSqlQuery query;
	QString strSql = R"(SELECT project_id FROM projects_table WHERE project_name=:name;)";
	query.prepare(strSql);
	query.bindValue(":name", proName);
	if (query.exec() && query.first())
	{
		int proIdx = query.value(0).toInt();
		m_mapNameIdx[proName] = proIdx;
	}
}

void CProjectDB::insertData(const QString& name)
{
	QSqlQuery query;
	query.prepare("INSERT INTO projects_table(project_name) VALUES (:name)");
	query.bindValue(":name", name);
	if (query.exec())
	{
		// 更新映射关系 [3/17/2023]
		updateMap(name);
	}
}

void CProjectDB::deleteData(const QString& name)
{
	QSqlQuery query;
	QString strSql = R"(DELETE FROM projects_table WHERE project_name=:name;)";
	query.prepare(strSql);
	query.bindValue(":name", name);
	query.exec();
}

void CProjectDB::updateName(const QString& name)
{
	QString sql = R"(UPDATE projects_table SET project_name=:name WHERE project_name!=:name;)";
	QSqlQuery query;

	query.prepare(sql);
	query.bindValue(":name", name);

	if (!query.exec()) 
	{
		qDebug() << "Failed to update project name:" << query.lastError().text();
	}
}


// 仅启动初始化时加载一次 [3/16/2023]
void CProjectDB::getAllProjects(QStringList& lstProjects)
{
	// 获取全部项目列表 [3/14/2023]
	QSqlQuery query;
	query.exec(QString(
		R"(SELECT * FROM projects_table;)"
	));
	unordered_map<QString, int> tmpMap;
	while (query.next())
	{
		int proIdx = query.value(0).toInt();
		QString proName = query.value(1).toString();
		lstProjects.append(proName);
		// 初始化当前名称-ID映射关系 [3/16/2023]
		tmpMap.emplace(proName, proIdx);
	}
	m_mapNameIdx.swap(tmpMap);
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

CImageDB* CImageDB::m_pInstance = nullptr;

CImageDB* CImageDB::getInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new CImageDB();
	}
	return m_pInstance;
}

CImageDB::CImageDB()
{
	if (m_db.open())
	{
		// 创建图片表 [3/14/2023]
		initialImageTable();
	}
}

CImageDB::~CImageDB()
{
	m_mapNameIdx.clear();
}

void CImageDB::insertData(ImageInfo& info)
{
	QSqlQuery query;
	QString strSql = R"(
		INSERT INTO images_table(image_name,image_path,defect_name,defect_level,conf_val) VALUES(:name,:path,:defectName,:defectLevel,:confVal);
	)";
	query.prepare(strSql);
	query.bindValue(":name", info._name);
	query.bindValue(":path", info._absPath);
	query.bindValue(":defectName", info._defectName);
	query.bindValue(":defectLevel", info._defectLevel);
	query.bindValue(":confVal", info._confVal);
	query.exec();
	// 获取插入最后图片ID [3/18/2023]
	getLastImageID();
}

void CImageDB::deleteData(const QString& strPath)
{
	QSqlQuery query;
	QString strSql = R"(DELETE FROM images_table WHERE image_path=:path;)";
	query.prepare(strSql);
	query.bindValue(":path", strSql);
	if (!query.exec())
	{
		qDebug() << query.lastError().text();
	}
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
	info._absPath = strPath;
	QSqlQuery query;
	query.prepare("SELECT image_id, image_name, defect_name, defect_level FROM images_table WHERE image_path=:path;");
	query.bindValue(":path", strPath);
	if (query.exec() && query.first())
	{
		info._idx = query.value(0).toInt();
		info._name = query.value(1).toString();
		info._defectName = query.value(2).toString();
		info._defectLevel = query.value(3).toInt();
	}
	return info;
}

ImageInfo CImageDB::searchData(const int imgId)
{
	ImageInfo info;
	info._idx = imgId;

	// 使用 QSqlQuery::executed() 函数判断查询是否成功执行，并打印出错信息
	QSqlQuery query;
	QString strSql = R"(
        SELECT image_name, image_path, defect_name, defect_level, conf_val FROM images_table WHERE image_id=:idx;
    )";
	query.prepare(strSql);
	query.bindValue(":idx", imgId);
	if (query.exec() && query.first())
	{
		info._name = query.value(0).toString();
		info._absPath = query.value(1).toString();
		info._defectName = query.value(2).toString();
		info._defectLevel = query.value(3).toInt();
		info._confVal = query.value(4).toFloat();
	}
	else
	{
		qDebug() << "Failed to execute query. Error message: " << query.lastError().text();
	}

	return info;
}

void CImageDB::loadMapNameIdx()
{
	QSqlQuery query;
	QString strSql = R"(
		SELECT * FROM images_table;
	)";
	query.exec(strSql);
	unordered_map<QString, ImageInfo> tmpMap;
	while (query.next())
	{
		int imgIdx = query.value(0).toInt();
		QString imgName = query.value(1).toString();
		QString imgPath = query.value(2).toString();
		QString defectName = query.value(3).toString();
		int defectLevel = query.value(4).toInt();
		float confVal = query.value(5).toFloat();
		ImageInfo tmpInfo = 
		{
			imgIdx, imgName, imgPath, defectName, defectLevel, confVal
		};
		tmpMap.emplace(imgName, tmpInfo);
	}
	m_mapNameIdx.swap(tmpMap);
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
	m_mapNameIdx.clear();
}

void CImageDB::getLastImageID()
{
	QString strSql = R"(SELECT last_insert_rowid() FROM images_table)";
	QSqlQuery query;
	query.prepare(strSql);
	if (query.exec() && query.first())
	{
		m_lastImgIdx = query.value(0).toInt();
	}
}

bool CImageDB::initialImageTable()
{
	const QString sql = R"(
		CREATE TABLE IF NOT EXISTS images_table (
			image_id		INTEGER   PRIMARY KEY AUTOINCREMENT NOT NULL,
			image_name		CHAR(50)  NOT NULL,
			image_path		CHAR (50) NOT NULL,
			defect_name		CHAR (50),
			defect_level	INTEGER,
			conf_val		REAL
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

CMapDB* CMapDB::m_pInstance = nullptr;

CMapDB* CMapDB::getInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new CMapDB();
	}
	return m_pInstance;
}

CMapDB::CMapDB()
{
	if (m_db.open())
	{
		// 创建映射表 [3/14/2023]
		initialMapTable();
	}
}

CMapDB::~CMapDB()
{
}

void CMapDB::insertData(int projectIdx, int imageIdx)
{
	QSqlQuery query;
	QString strSql = R"(INSERT INTO mapProjectImage_table(project_id, image_id) VALUES(:projectIdx,:imageIdx))";
	query.prepare(strSql);
	query.bindValue(":projectIdx", projectIdx);
	query.bindValue(":imageIdx", imageIdx);
	if (query.exec())
	{
		// 插入成功后更新映射 [3/25/2023]
		m_mapProImgIdx[projectIdx].emplace_back(imageIdx);
	}
}

void CMapDB::loadAllMapInfo()
{
	QSqlQuery query;
	query.exec(QString(
		R"(SELECT * FROM mapProjectImage_table;)"
	));
	unordered_map<int, vector<int> > tmpMap;
	while (query.next())
	{
		int projectIdx = query.value(1).toInt();
		int imageIdx = query.value(2).toInt();
		if (tmpMap.find(projectIdx) != tmpMap.end())
		{
			tmpMap[projectIdx].emplace_back(imageIdx);
		}
		else
		{
			// 未插入项目id补充 [3/16/2023]
			tmpMap.emplace(projectIdx, vector<int>{imageIdx});
		}
	}
	m_mapProImgIdx.swap(tmpMap);
}

void CMapDB::deleteDataFromImg(int imageIdx)
{
	QSqlQuery query;
	QString strSql = R"(DELETE FROM mapProjectImage_table WHERE image_id=:idx)";
	query.prepare(strSql);
	query.bindValue(":idx", imageIdx);
	query.exec();
}

void CMapDB::deleteDataFromProject(int projectIdx)
{
	QSqlQuery query;
	QString strSql = R"(DELETE FROM mapProjectImage_table WHERE project_id=:idx)";
	query.prepare(strSql);
	query.bindValue(":idx", projectIdx);
	query.exec();
}

void CMapDB::updateImageIdx(int projectIdx, int imageIdx)
{
	QSqlQuery query;
	QString strSql = R"(UPDATE mapProjectImage_table SET project_id=:pid WHERE image_id=:imgId)";
	query.prepare(strSql);
	query.bindValue("pid", projectIdx);
	query.bindValue(":imgId", imageIdx);
	query.exec();
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

bool CMapDB::initialMapTable()
{
	// 判断是否已经存在表 [3/17/2023]
	const QString sql = R"(
		CREATE TABLE IF NOT EXISTS mapProjectImage_table (
			map_id		INTEGER		PRIMARY KEY AUTOINCREMENT NOT NULL,
			project_id	INTEGER		NOT NULL,
			image_id	INTEGER		NOT NULL
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
