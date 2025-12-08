#include "CsvReader.h"
#include <fstream>
#include <assert.h>

CsvReader::CsvReader()
{
}

CsvReader::~CsvReader()
{
	for (auto itr = records.begin(); itr != records.end(); itr++) {
		(*itr).clear();
	}
	records.clear();
}

void CsvReader::Load(std::string filename)
{
	// ファイルを開く
	std::ifstream ifs(filename);
	if (ifs) {
		// ファイルを開くことに成功
		std::string s;
		while (std::getline(ifs, s)) {
			// １行目のCSVがsに文字列として入っている
			std::vector<std::string> strs;
			int top = 0;
			for (int i = 0; i < s.length(); i++) {
				if (s[i] == ',') {
					std::string s2 = s.substr(top, i - top);
					strs.push_back(s2);
					top = i + 1;
				}
			}
			std::string s2 = s.substr(top);
			strs.push_back(s2);
			records.push_back(strs);
		}
		// ファイルを閉じる
		ifs.close();
	}
	else {
		assert(false);
	}
}

std::string CsvReader::Get(int line, int column)
{
	assert(line >= 0 && line < records.size());
	assert(column >= 0 && column < records[line].size());
	return records[line][column];
}

float CsvReader::GetFloat(int line, int column)
{
	return stof(Get(line, column));
}

int CsvReader::GetInt(int line, int column)
{
	return stoi(Get(line, column));
}
