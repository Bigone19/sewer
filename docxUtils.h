#pragma once
#ifndef __DOCXUTILS_H__
#define __DOCXUTILS_H__

/************************************************************************/
/* docxд��                                                             */
/* 2023/02/06                                                           */
/************************************************************************/

#include <string>

#include "document.h"
#include "table.h"
#include "parts/documentpart.h"

using std::string;

namespace DocxUtils
{
	/**
	* @brief: docx���ģ����
	* @param: 
	* @date: 2023/02/09
	*/
	Table* addTemplateTable(Document* pDoc,
		const string& imgPath, const string& defectName);
}



#endif // !__DOCXUTILS_H__
