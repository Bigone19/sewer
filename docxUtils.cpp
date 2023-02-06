#include "docxUtils.h"


CDocx::CDocx() : Document()
{
}

CDocx::CDocx(const string& fileName)
	: Document(QString::fromStdString(fileName))
{
}

CDocx::~CDocx()
{
}
