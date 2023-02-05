#include "docxlength.h"

#include <math.h>

namespace DocxUtils
{
	const int EMUS_PER_INCH = 914400;	// 英寸 [2/5/2023]
	const int EMUS_PER_CM = 360000;		// 厘米 [2/5/2023]
	const int EMUS_PER_MM = 36000;		// 毫米 [2/5/2023]
	const int EMUS_PER_PX = 12700;		// 像素 [2/5/2023]
	const int EMUS_PER_TWIP = 635;		// 1/20点 [2/5/2023]

	const int UNITS_PER_POINT = 100;	// 点 [2/5/2023]

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

	bool CLength::isEmpty() const
	{
		return this->m_isEmpty;
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

	int CLength::twips() const
	{
		return (int)(round((float)m_value / (float)EMUS_PER_TWIP));
	}
	/**
	* @brief: Inches长度 eg width = Inches(0.5)
	* @param: 
	* @date: 2023/02/05
	*/
	CLength Inches::value(float inches)
	{
		int val = int(inches * EMUS_PER_INCH);
		return CLength(val);
	}
	/**
	* @brief: centimetres 长度 eg height = Cm(12)
	* @param: 
	* @date: 2023/02/05
	*/
	CLength Cm::value(float cm)
	{
		int val = int(cm * EMUS_PER_CM);
		return CLength(val);
	}
	/**
	* @brief: English Metric Units eg width = Emu(457200)
	* @param: 
	* @date: 2023/02/05
	*/
	CLength Emu::value(float emu)
	{
		return CLength(emu);
	}
	/**
	* @brief: millimeters 长度
	* @param: 
	* @date: 2023/02/05
	*/
	CLength Mm::value(float mm)
	{
		int val = int(mm * EMUS_PER_MM);
		return CLength(val);
	}
	/**
	* @brief: setting font sizes in points
	* @param: 
	* @date: 2023/02/05
	*/
	CLength Pt::value(float pts)
	{
		int units = int(pts * UNITS_PER_POINT);
		return CLength(units);
	}
	/**
	* @brief: pixels
	* @param: 
	* @date: 2023/02/05
	*/
	CLength Px::value(float px)
	{
		int val = int(px * EMUS_PER_PX);
		return CLength(val);
	}
	/**
	* @brief: Twips eg width = Twips(42)
	* @param: 
	* @date: 2023/02/05
	*/
	CLength Twips::value(float twips)
	{
		int val = int(twips * EMUS_PER_TWIP);
		return CLength(val);
	}

}




