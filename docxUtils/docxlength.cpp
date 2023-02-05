#include "docxlength.h"

namespace DocxUtils
{
	const int EMUS_PER_INCH = 914400;	// Ó¢´ç [2/5/2023]
	const int EMUS_PER_CM = 360000;		// ÀåÃ× [2/5/2023]
	const int EMUS_PER_MM = 36000;		// ºÁÃ× [2/5/2023]
	const int EMUS_PER_PX = 12700;		// ÏñËØ [2/5/2023]
	const int EMUS_PER_TWIP = 635;

	const int UNITS_PER_POINT = 100;

	CLength::CLength()
		: m_value(0)
		, m_isEmpty(false)
	{}

	CLength::CLength(int val)
		: m_value(val)
		, m_isEmpty(false)
	{}

	CLength::~CLength()
	{}

	int CLength::getValue() const
	{
		return this->m_value;
	}

	float CLength::cm() const
	{
		return (float)m_value / (float)EMUS_PER_CM;
	}

	float CLength::inches() const
	{
		return (float)m_value / (float)EMUS_PER_INCH;
	}

	float CLength::mm() const
	{
		return (float)m_value / (float)EMUS_PER_MM;
	}

	int CLength::px() const
	{
		return (int)(round((float)m_value / (float)EMUS_PER_PX) + 0.1);
	}

}




