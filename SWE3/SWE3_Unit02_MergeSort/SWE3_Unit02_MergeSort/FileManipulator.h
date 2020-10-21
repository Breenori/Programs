#ifndef FILEMANIPULATOR_H
#define FILEMANIPULATOR_H
#include<iostream>
#include<vector>
#include<string>
#include<fstream>

class FileManipulator {

	typedef std::string value_type;

public:
	static size_t partition(std::string const& src, std::vector<std::string> const& dst);

private:

};

#endif