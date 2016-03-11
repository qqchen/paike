#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>

enum SUBJECT
{
	PLOITICS = 0,
	HISTORY,
	GEOGRAPHY,
	PHYSICS,
	CHEMISTRY,
	BIOLOGY,
	SUB_NUM,
};

std::string sbj[SUB_NUM] = { "A", "B", "C", "D", "E", "F" };

class Students
{
public:
	Students(SUBJECT s1, SUBJECT s2, SUBJECT s3, int stuNum) :m_s1(s1), m_s2(s2), m_s3(s3), m_stuNum(stuNum){}
	std::string GetName()
	{
		return sbj[m_s1] + sbj[m_s2] + sbj[m_s3];
	}
	SUBJECT GetSubject(int i)
	{
		SUBJECT ss = m_s1;
		switch (i)
		{
		case 0:
			ss = m_s1;
			break;
		case 1:
			ss = m_s2;
			break;
		case 2:
			ss = m_s3;
			break;
		default:
			break;
		}
		return ss;
	}

	SUBJECT m_s1;     // 选科1 
	SUBJECT m_s2;     // 选科2
	SUBJECT m_s3;     // 选科3
	int     m_stuNum; // 选了这3科的学生数
};

#endif