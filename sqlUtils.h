#pragma once
#ifndef __SQLUTILS_H__
#define __SQLUTILS_H__

/************************************************************************/
/* sql»ùÀà                                                              */
/* 2023/03/14                                                           */
/************************************************************************/

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class CSqlUtils
{
public:
	CSqlUtils();
	virtual ~CSqlUtils();
protected:
	QSqlDatabase m_db;
};

#endif // !__SQLUTILS_H__
