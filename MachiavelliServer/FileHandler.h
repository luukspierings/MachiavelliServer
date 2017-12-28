#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using std::fstream;
using std::istringstream;
using std::ios_base;
using std::vector;
using std::string;


class FileHandler
{
public:
	FileHandler(string filePath, bool overwrite = false);

	vector<vector<string>> getValues();
	void writeLine(vector<string> values);
	void writeLine(string value);

	bool remove(string filePath);
	static bool exists(string filePath);

private:
	fstream currentFile;
};

