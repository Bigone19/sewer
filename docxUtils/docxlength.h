#pragma once
#ifndef __DOCXLENGTH_H__
#define __DOCXLENGTH_H__

/************************************************************************/
/* docx���ȸ�ʽģ��                                                     */
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
		// get���� [2/5/2023]
		int getValue() const;
		bool isEmpty() const;

		// ת����λ [2/5/2023]
		float cm() const;
		float inches() const;
		float mm() const;
		int px() const;
		int twips() const;

	private:
		int m_value;		// ���ȵ�λֵ [2/5/2023]
		bool m_isEmpty;
	};

	class DOCXUTILS_EXPORT Inches
	{
	public:
		static CLength value(float inches);
	};
	class DOCXUTILS_EXPORT Cm
	{
	public:
		static CLength value(float cm);
	};

	class DOCXUTILS_EXPORT Emu
	{
	public:
		static CLength value(float emu);
	};

	class DOCXUTILS_EXPORT Mm
	{
	public:
		static CLength value(float mm);
	};

	class DOCXUTILS_EXPORT Pt
	{
	public:
		static CLength value(float pts);

	};

	class DOCXUTILS_EXPORT Px
	{
	public:
		static CLength value(float px);
	};

	class DOCXUTILS_EXPORT Twips
	{
	public:
		static CLength value(float twips);
	};
}

#endif // !__DOCXLENGTH_H__

