#include "onnxUtils.h"


vector<QString> fileUtils::loadInitFile(const string& initialFilePath)
{
	vector<QString> res;
	res.clear();
	ifstream ifs(initialFilePath);
	if (ifs.is_open())
	{
		string line;
		while (getline(ifs, line))
		{
			if (line.back() == '\r')
			{
				line.pop_back();
			}
			res.emplace_back(QDir::currentPath() + QString::fromStdString(line));
		}
	}
	return res;
}

vector<string> onnxUtils::loadClsNames(const string& path)
{
	vector<string> vecClsName;
	ifstream inFile(path);
	if (inFile.is_open())
	{
		string line;
		while (getline(inFile, line))
		{
			if (line.back() == '\r')
			{
				line.pop_back();
			}
			vecClsName.emplace_back(line);
		}
	}
	else
	{
		qDebug() << "ERROR: Failed to access class name path: " << QString::fromLocal8Bit(path) << Qt::endl;
	}
	return vecClsName;
}
