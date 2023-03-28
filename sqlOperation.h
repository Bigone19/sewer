#pragma once
#ifndef __SQLOPERATION_H__
#define __SQLOPERATION_H__

#include <QtCore>

/************************************************************************/
/* ���ݿ�����������                                                   */
/* 2023/03/27                                                           */
/************************************************************************/

class CSqlOperation
{
	/**
	* @brief: �����ݿ�
	* @param:
	* @date: 2023/03/14
	*/
	virtual bool openDatabase() = 0;
	/**
	* @brief: �ر����ݿ�
	* @param:
	* @date: 2023/03/13
	*/
	virtual void closeDatabase() = 0;
	/**
	* @brief: ��ʼ����
	* @param:
	* @date: 2023/03/13
	*/
	virtual bool initialTable() = 0;
	/**
	* @brief: ɾ������
	* @param: 
	* @date: 2023/03/28
	*/
	virtual void deleteData(const QString& name) = 0;
};

#endif // !__SQLOPERATION_H__
