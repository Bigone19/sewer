#include "docxUtils.h"
#include "parts/documentpart.h"
#include "table.h"

#include <QFile>

namespace DocxUtils
{
	CDox::CDox() : Document()
	{
	}
	CDox::CDox(const QString& docxPath)
		: Document(docxPath)
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
		pTable->getCell(0, 2)->addText(QString::fromUtf8("起始井号"));
		pTable->getCell(0, 4)->addText(QString::fromUtf8("终止井号"));
		pTable->getCell(1, 0)->addText(QString::fromUtf8("敷设年代"));
		pTable->getCell(1, 2)->addText(QString::fromUtf8("起点埋深"));
		pTable->getCell(1, 4)->addText(QString::fromUtf8("终点埋深"));
		pTable->getCell(2, 0)->addText(QString::fromUtf8("管段类型"));
		pTable->getCell(2, 2)->addText(QString::fromUtf8("管段材质"));
		pTable->getCell(2, 4)->addText(QString::fromUtf8("管段直径"));
		pTable->getCell(3, 0)->addText(QString::fromUtf8("检测方向"));
		pTable->getCell(3, 2)->addText(QString::fromUtf8("管道长度"));
		pTable->getCell(3, 4)->addText(QString::fromUtf8("检测长度"));
		pTable->getCell(4, 0)->addText(QString::fromUtf8("修复指数"));
		pTable->getCell(4, 2)->addText(QString::fromUtf8("养护指数"));
		pTable->getCell(4, 4)->addText(QString::fromUtf8("检测日期"));

		pTable->getCell(5, 0)->addText(QString::fromUtf8("检测地点"));
		Cell* pCell = pTable->getCell(5, 1);
		vector<Cell*> vecCell = { pTable->getCell(5, 2), pTable->getCell(5, 3), 
			pTable->getCell(5, 4), pTable->getCell(5, 5)};
		pCell->mergeMutliCell(vecCell);

		pTable->getCell(6, 0)->addText(QString::fromUtf8("距离(m)"));
		pTable->getCell(6, 1)->addText(QString::fromUtf8("缺陷名称代码"));
		pTable->getCell(6, 2)->addText(QString::fromUtf8("分值"));
		pTable->getCell(6, 3)->addText(QString::fromUtf8("等级"));
		pTable->getCell(6, 4)->addText(QString::fromUtf8("管段内部状况描述"));
		pTable->getCell(6, 5)->addText(QString::fromUtf8("照片序号或说明"));
		
		pTable->getCell(8, 0)->addText(QString::fromUtf8("备注"));
		pCell = pTable->getCell(8, 1);
		vecCell = { pTable->getCell(8, 2), pTable->getCell(8, 3)
			, pTable->getCell(8, 4), pTable->getCell(8, 5) };
		pCell->mergeMutliCell(vecCell);

		// 表格内添加缺陷图片 [2/10/2023]
		pCell = pTable->getCell(9, 0);
		vecCell = { pTable->getCell(9, 1), pTable->getCell(9, 2) };
		pCell->addImage(imgPath);
		pCell->mergeMutliCell(vecCell);

		pCell = pTable->getCell(9, 3);
		vecCell = { pTable->getCell(9, 4), pTable->getCell(9, 5) };
		pCell->mergeMutliCell(vecCell);

		pTable->getCell(10, 0)->addText(QString::fromUtf8("图片1"));
		pCell = pTable->getCell(10, 0);
		vecCell = { pTable->getCell(10, 1), pTable->getCell(10, 2) };
		pCell->mergeMutliCell(vecCell);
		pCell = pTable->getCell(10, 3);
		vecCell = { pTable->getCell(10, 4), pTable->getCell(10, 5) };
		pCell->mergeMutliCell(vecCell);

		return pTable;
	}

}