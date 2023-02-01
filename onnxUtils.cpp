#include "onnxUtils.h"

vector<QString> fileUtils::loadInitFile()
{
	vector<QString> res;
	res.clear();
	ifstream ifs(g_initFilePath);
	if (ifs.is_open())
	{
		string line;
		while (getline(ifs, line))
		{
			if (line.back() == '\r')
			{
				line.pop_back();
			}
			res.emplace_back(g_projectPath + QString::fromStdString(line));
		}
	}
	return res;
}

