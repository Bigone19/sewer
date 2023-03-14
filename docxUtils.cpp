#include "docxUtils.h"
#include "parts/documentpart.h"
#include "table.h"

#include <unordered_map>
#include <QFile>

using std::unordered_map;

const unordered_map<int, string> g_mapLevel =
{
	{1, "1级"}, {2, "2级"},
	{3, "3级"}, {4, "4级"}
};

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

	DocxUtils::Table* CDox::addTemplate(const string& imgPath, const string& defectName, int defectLevel)
	{
		// 获取图片文件名称 [2/16/2023]
		size_t pos = imgPath.find_last_of('/');
		string strImgName = imgPath.substr(pos + 1);

		Table* pTable = this->addTable(11, 6);
		// 添加表格表头 [2/10/2023]
		pTable->getCell(0, 0)->addText(QString::fromUtf8("图像文件"));
		pTable->getCell(0, 1)->addText(QString::fromStdString(strImgName));
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
		pCell->merge(pTable->getCell(5, 5));

		pTable->getCell(6, 0)->addText(QString::fromUtf8("距离(m)"));
		pTable->getCell(6, 1)->addText(QString::fromUtf8("缺陷名称代码"));
		pTable->getCell(6, 2)->addText(QString::fromUtf8("分值"));
		pTable->getCell(6, 3)->addText(QString::fromUtf8("等级"));
		pTable->getCell(6, 4)->addText(QString::fromUtf8("管段内部状况描述"));
		pTable->getCell(6, 5)->addText(QString::fromUtf8("照片序号或说明"));
		
		pTable->getCell(7, 1)->addText(QString::fromStdString(defectName));
		pTable->getCell(7, 3)->addText(QString::fromStdString(g_mapLevel.at(defectLevel)));
		pTable->getCell(7, 5)->addText(QString::fromUtf8("照片1"));

		pTable->getCell(8, 0)->addText(QString::fromUtf8("备注"));
		pCell = pTable->getCell(8, 1);
		pCell->merge(pTable->getCell(8, 5));

		// 表格内添加缺陷图片 [2/10/2023]
		pCell = pTable->getCell(9, 0);
		pCell->addImage(imgPath);
		pCell->merge(pTable->getCell(9, 2));

		pCell = pTable->getCell(9, 3);
		pCell->merge(pTable->getCell(9, 5));

		pCell = pTable->getCell(10, 0);
		pTable->getCell(10, 0)->addText(QString::fromUtf8("照片1"));
		pCell->merge(pTable->getCell(10, 2));
		pCell = pTable->getCell(10, 3);
		pCell->merge(pTable->getCell(10, 5));

		return pTable;
	}

}