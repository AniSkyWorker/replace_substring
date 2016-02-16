#include "stdafx.h"
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <string.h>
#include <fstream>

const std::streampos c_maxPos = 2147483648;

bool IsFileSizeIncorrect(const std::string& fileName)
{
	std::fstream file(fileName, std::ios::in);
	file.seekg(0, std::ios::end);

	if (file.tellg() > c_maxPos)
	{
		std::cout << "Error: Invalid size of input file (> 2Gb)";
		return true;
	}

	return false;
}

bool ReplaceSubstringInFile(const std::string& inputFileName,const std::string& outputFileName,
	const std::string& oldSubstring, const std::string& newSubstring)
{

	std::ifstream inputFile(inputFileName);

	if (!inputFile.is_open())
	{
		std::cout << "Error: Invalid name of input file!";
		return false;
	}

	if (IsFileSizeIncorrect(inputFileName))
		return false;

	std::ofstream outputFile(outputFileName);
	std::string workString;

	while (std::getline(inputFile, workString))
	{
		if (workString.size() != 0)
			boost::replace_all(workString, oldSubstring, newSubstring);

		if (inputFile.peek() != EOF)
			workString += "\n";

		outputFile << workString;
	}

	if (!outputFile.flush())
		std::cout << "Error: Failed writing to output file!";

	return true;
}

int main (int argc, char *argv[])
{
	if (argc != 5)
	{
		std::cout << "Error: Invalid number of arguments!" << std::endl
			<< "Usage: replace.exe <inputFile> <outputFile> <searchString> <replacmentString>";
		return 1;
	}

	if(!ReplaceSubstringInFile(argv[1], argv[2], argv[3], argv[4]))
		return 1;

    return 0;
}