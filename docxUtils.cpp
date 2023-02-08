#include "docxUtils.h"

namespace DocxUtils
{
	Table* addTemplateTable(Document* pDoc, 
		const string& imgPath, const string& defectName)
	{
		Table* pTable = pDoc->addTable(11, 6);
		Cell* pCell = pTable->getCell(9, 0);
		pCell->addImage(imgPath);
		return pTable;
	}
}