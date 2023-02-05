#pragma once
#ifndef __DOCXLENGTH_H__
#define __DOCXLENGTH_H__

/************************************************************************/
/* docx长度格式模块                                                     */
/* 2023/02/05                                                           */
/************************************************************************/

#include "docxUtils_global.h"

namespace DocxUtils
{
	class DOCXUTILS_EXPORT CLength
	{
	public:
		CLength();
		CLength(int val);
		virtual ~CLength();
		// get方法 [2/5/2023]
		int getValue() const;

		// 转换单位 [2/5/2023]
		float cm() const;
		float inches() const;
		float mm() const;
		int px() const;
		int twips() const;
		bool isEmpty() const;

	private:
		int m_value;		// 长度单位值 [2/5/2023]
		bool m_isEmpty;
	};
}

#endif // !__DOCXLENGTH_H__

