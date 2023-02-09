#include "docxUtils.h"
#include "parts/documentpart.h"
#include "table.h"

namespace DocxUtils
{
	CDox::CDox() : Document()
	{
	}
	CDox::CDox(const string& docxPath)
		: Document(QString::fromStdString(docxPath))
	{
	}
	CDox::~CDox()
	{
	}

	Table* CDox::addTemplateTable(const string& imgPath, const string& defectName)
	{
		Table* pTable = this->addTable(11, 6);
		Cell* pCell = pTable->getCell(9, 0);
		pCell->addImage(imgPath);
		return pTable;
	}

}