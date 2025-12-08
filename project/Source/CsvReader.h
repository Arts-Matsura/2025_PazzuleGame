#pragma once
#include <string>
#include <vector>

class CsvReader {
public:
	CsvReader();
	~CsvReader();
	void Load(std::string filename);
	std::string Get(int line, int column);
	float GetFloat(int line, int column);
	int GetInt(int line, int column);
	int Lines() { return records.size(); }
	int Columns(int line) { return records[line].size(); }
private:
	std::vector<std::vector<std::string>> records;
};