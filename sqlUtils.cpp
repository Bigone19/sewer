#include "sqlUtils.h"

CSqlUtils::CSqlUtils()
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
}

CSqlUtils::~CSqlUtils()
{
	m_db.close();
	m_db.removeDatabase("QSQLITE");
}
