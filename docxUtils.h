#pragma once
#ifndef __DOCXUTILS_H__
#define __DOCXUTILS_H__

/************************************************************************/
/* docx–¥»Î                                                             */
/* 2023/02/06                                                           */
/************************************************************************/

#include <string>

#include "document.h"
#include "table.h"

using namespace DocxUtils;
using std::string;

class CDocx : public Document
{
public:
	CDocx();
	explicit CDocx(const string& fileName);
	virtual ~CDocx();

private:
};

#endif // !__DOCXUTILS_H__
