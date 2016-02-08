#include "stdafx.h"
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <string.h>
#include <fstream>

struct ReplaceInterface
{
	std::ifstream inputFile;
	std::ofstream outputFile;
	std::string workString;

	bool IsFileSizeIncorrect(std::string fileName)
	{
		std::fstream file(fileName, std::ios::in);
		file.seekg(0, std::ios::end);
		int sizeInBytes = static_cast<int>(file.tellg());
		if (sizeInBytes > 2147483648)
		{
			perror("Size of file > 2Gb!");
			return true;
		}
		return false;
	}

	bool IsNameIncorrect()
	{
		if (!inputFile.is_open())
		{
			perror("Incorret name of file!");
			return true;
		}

		return false;
	}

	bool replace(std::string inputFileName, std::string outputFileName, 
		std::string oldSubstring, std::string newSubstring)
	{
		if (!IsFileSizeIncorrect(inputFileName))
			inputFile.open(inputFileName);
		else
			return false;

		if (!IsNameIncorrect())
			outputFile.open(outputFileName);
		else
			return false;

		while (!inputFile.eof())
		{
			std::getline(inputFile, workString);
			if (workString.size() != 0)
				boost::replace_all(workString, oldSubstring, newSubstring);
			if (inputFile.peek() != EOF)
				workString += "\n";
			outputFile << workString;
		}
		return true;
	}

	void close()
	{
		inputFile.close();
		outputFile.close();
	}

};

int main (int argc, char *argv[])
{
	if (argc != 5)
	{
		perror("Incorrect number of arguments!");
		return 1;
	}

	ReplaceInterface fInterface;
	if(fInterface.replace(argv[1], argv [2], argv[3], argv[4]))
		fInterface.close();
	else 
	{
		fInterface.close();
		return 1;
	}

    return 0;
}

