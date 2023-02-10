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

	Table* CDox::addTemplate(const string& imgPath, const string& defectName)
	{
		
		Table* pTable = this->addTable(11, 6);
		// 添加表格表头 [2/10/2023]
		pTable->getCell(0, 0)->addText(QString::fromUtf8("图像文件"));
		pTable->getCell(1, 0)->addText(QString::fromUtf8("敷设年代"));
		pTable->getCell(2, 0)->addText(QString::fromUtf8("管段类型"));
		pTable->getCell(3, 0)->addText(QString::fromUtf8("检测方向"));
		pTable->getCell(4, 0)->addText(QString::fromUtf8("修复指数"));
		pTable->getCell(5, 0)->addText(QString::fromUtf8("检测地点"));

		// 表格内添加缺陷图片 [2/10/2023]
		Cell* pCell = pTable->getCell(9, 0);
		vector<Cell*> vecCell = { pTable->getCell(9, 1), pTable->getCell(9, 2) };
		pCell->addImage(imgPath);
		pCell->mergeMutliCell(vecCell);
		return pTable;
	}

}