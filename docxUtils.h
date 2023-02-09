#pragma once
#ifndef __DOCXUTILS_H__
#define __DOCXUTILS_H__

/************************************************************************/
/* docx–¥»Î                                                             */
/* 2023/02/06                                                           */
/************************************************************************/

#include <string>

#include "document.h"

using std::string;

namespace DocxUtils
{
	class DocumentPart;
	class Paragraph;
	class Table;
	class Cell;

	class CDox : public Document
	{
	public:
		CDox();
		explicit CDox(const string& docxPath);
		~CDox();
		/**
		* @brief: 
		* @param: 
		* @date: 2023/02/10
		*/
		Table* addTemplateTable(const string& imgPath, const string& defectName);
	};
}



#endif // !__DOCXUTILS_H__
