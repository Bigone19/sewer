#pragma once
#ifndef __SQLOPERATION_H__
#define __SQLOPERATION_H__

#include <QtCore>

/************************************************************************/
/* 数据库操作抽象基类                                                   */
/* 2023/03/27                                                           */
/************************************************************************/

class CSqlOperation
{
	/**
	* @brief: 打开数据库
	* @param:
	* @date: 2023/03/14
	*/
	virtual bool openDatabase() = 0;
	/**
	* @brief: 关闭数据库
	* @param:
	* @date: 2023/03/13
	*/
	virtual void closeDatabase() = 0;
	/**
	* @brief: 初始化表
	* @param:
	* @date: 2023/03/13
	*/
	virtual bool initialTable() = 0;
	/**
	* @brief: 删除操作
	* @param: 
	* @date: 2023/03/28
	*/
	virtual void deleteData(const QString& name) = 0;
};

#endif // !__SQLOPERATION_H__
