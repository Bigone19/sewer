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
using std::vector;
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
		explicit CDox(const QString& docxPath);
		~CDox();
		/**
		* @brief: ÃÌº”ƒ£∞Â
		* @param: 
		* @date: 2023/02/10
		*/
		Table* addTemplate(const string& imgPath, const string& defectName, int defectLevel);
	};
}



#endif // !__DOCXUTILS_H__
