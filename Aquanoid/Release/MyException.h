#pragma once

#include <iostream>
#include <string>

//-----------------------------------------------MyException---------------------------------------//
class MyException
{
public:
	MyException(std::string description , int line = 0) : _description(description),_lineNum(line){}

	//print the exception.
	void show()
	{
		if(_lineNum > 0 )
			std::cout << _description << " at line " << _lineNum << std::endl;
		else
			std::cout << _description << std::endl;
	}

private:
	
	std::string _description;
	int _lineNum;
};