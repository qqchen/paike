#ifndef CLASS_H
#define CLASS_H

#include <iostream>
#include <sstream>
#include <vector>

class Class
{
public:
	Class(){};
	void Push(std::string stu)
	{
		m_students.push_back(stu);
	}
	void Push(std::string stu, int index)
	{
		std::stringstream ss(std::stringstream::in | std::stringstream::out);
		ss << stu << "_" << index;
		Push(ss.str());
	}
	std::vector<std::string> m_students;
};

#endif