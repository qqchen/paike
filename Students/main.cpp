#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include "students.h"
#include "class.h"

using namespace std;

static const int TypeNum = 20;
static const int step = 2;

static Students ABC(PLOITICS, HISTORY, GEOGRAPHY, 0);
static Students ABD(PLOITICS, HISTORY, PHYSICS, 0);
static Students ABE(PLOITICS, HISTORY, CHEMISTRY, 0);
static Students ABF(PLOITICS, HISTORY, BIOLOGY, 0);
static Students ACD(PLOITICS, GEOGRAPHY, PHYSICS, 0);
static Students ACE(PLOITICS, GEOGRAPHY, CHEMISTRY, 0);
static Students ACF(PLOITICS, GEOGRAPHY, BIOLOGY, 0);
static Students ADE(PLOITICS, PHYSICS, CHEMISTRY, 0);
static Students ADF(PLOITICS, PHYSICS, BIOLOGY, 0);
static Students AEF(PLOITICS, CHEMISTRY, BIOLOGY, 0);
static Students BCD(HISTORY, GEOGRAPHY, PHYSICS, 0);
static Students BCE(HISTORY, GEOGRAPHY, CHEMISTRY, 0);
static Students BCF(HISTORY, GEOGRAPHY, BIOLOGY, 0);
static Students BDE(HISTORY, PHYSICS, CHEMISTRY, 0);
static Students BDF(HISTORY, PHYSICS, BIOLOGY, 0);
static Students BEF(HISTORY, CHEMISTRY, BIOLOGY, 0);
static Students CDE(GEOGRAPHY, PHYSICS, CHEMISTRY, 0);
static Students CDF(GEOGRAPHY, PHYSICS, BIOLOGY, 0);
static Students CEF(GEOGRAPHY, CHEMISTRY, BIOLOGY, 0);
static Students DEF(PHYSICS, CHEMISTRY, BIOLOGY, 0);
static Students* pStu[TypeNum] = { &ABC, &ABD, &ABE, &ABF, &ACD, &ACE, &ACF, &ADE, &ADF, &AEF, &BCD, &BCE, &BCF, &BDE, &BDF, &BEF, &CDE, &CDF, &CEF, &DEF };

static int identityMatrix[6][3][3] = {
	{ { 1, 0, 0 }, { 0, 1, 0 }, { 0, 0, 1 } },
	{ { 1, 0, 0 }, { 0, 0, 1 }, { 0, 1, 0 } },
	{ { 0, 1, 0 }, { 1, 0, 0 }, { 0, 0, 1 } },
	{ { 0, 1, 0 }, { 0, 0, 1 }, { 1, 0, 0 } },
	{ { 0, 0, 1 }, { 1, 0, 0 }, { 0, 1, 0 } },
	{ { 0, 0, 1 }, { 0, 1, 0 }, { 1, 0, 0 } } };

// ��ʼ��ÿ�����͵�ѡ������
static int StudentNum[TypeNum] = { 19, 3, 12, 39, 6, 8, 34, 3, 3, 7, 10, 49, 111, 1, 4, 18, 6, 13, 34, 9 };
// �˹����
static int SubjectMatrix[3][6] = { { 54, 78, 148, -1, 37, 120 }, { 54, 78, 74, -1, 37, 80 }, { 30, 120, 74, 58, 74, 80 } };

static int copySubjectMatrix[3][6] = { 0 };
// ���ڱ���ÿ�ſε�ѡ�����
static Class classes[3][6] = { { Class(), Class(), Class(), Class(), Class(), Class() }, { Class(), Class(), Class(), Class(), Class(), Class() }, { Class(), Class(), Class(), Class(), Class(), Class() } };

void Init();
bool CheckStudentNum();
void SortStudents();
void PrintMatrix();
void PrintStudents();
bool SplitStudents();

int main()
{
	Init();
	bool valid = CheckStudentNum();    // ��Ҫ�Ǽ������
	if (!valid)
	{
		cout << "wrong data!" << endl;
		return 1;
	}
	SortStudents();   // ��20���������
	PrintMatrix();
	PrintStudents();
	bool success = SplitStudents();  // ��ѧ��
	if (success)
	{
		cout << "splite student success" << endl;
	}
	else
	{
		cout << "splite student failed" << endl;
	}
	return 1;
}

void Init()
{
	for (int i = 0; i < TypeNum; ++i)
	{
		pStu[i]->m_stuNum = StudentNum[i];
	}

	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 6; j++)
		{
			copySubjectMatrix[i][j] = SubjectMatrix[i][j];
		}
	}
}


bool CheckStudentNum()
{
	int stuNum = 0;
	for (int i = 0; i < TypeNum; ++i)
	{
		stuNum += StudentNum[i];
	}
	cout << "student num : " << stuNum << endl;
	int sum = 0;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 6; ++j)
		{
			sum += SubjectMatrix[i][j];
		}
	}
	return stuNum <= sum;
}

void SortStudents()
{
	for (int i = 0; i < TypeNum; ++i)
	{
		for (int j = i + 1; j < TypeNum; ++j)
		{
			if (pStu[j]->m_stuNum > pStu[i]->m_stuNum)
			{
				Students* tmp = pStu[i];
				pStu[i] = pStu[j];
				pStu[j] = tmp;
			}
		}
	}
}

void PrintMatrix()
{
	cout << endl << "matrix : " << endl;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 6; ++j)
		{
			cout << SubjectMatrix[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void PrintStudents()
{

	for (int i = 0; i < TypeNum; ++i)
	{
		cout << pStu[i]->GetName() << " : " << pStu[i]->m_stuNum << endl;
	}
}

bool HaveStudent(int ** src, int ** identity)
{
	bool hasStudent = true;
	for (size_t ri = 0; ri < 3; ri++)
	{
		hasStudent = true;
		for (size_t ci = 0; ci < 3; ci++)
		{
			if (identity[ri][ci] == 1)
				hasStudent = src[ri][ci] > 0;
		}
		if (!hasStudent)
			break;
	}
	return hasStudent;
}

bool SplitStudents()
{
	ofstream ofs;
	ofs.open("log.txt");
	static int tmpMatrix[3][3] = { 0 };

	for (size_t i = 0; i < TypeNum; i++)
	{
		Students* pp = pStu[i];
		cout << "processing " << pp->GetName() << "..." << endl;

		for (size_t mi = 0; mi < 3; mi++)
		{
			tmpMatrix[mi][0] = copySubjectMatrix[mi][pp->m_s1];
			tmpMatrix[mi][1] = copySubjectMatrix[mi][pp->m_s2];
			tmpMatrix[mi][2] = copySubjectMatrix[mi][pp->m_s3];
		}

		//if (ofs.is_open())
		//{
		//	ofs << "processing " << pp->GetName() << "..." << endl;
		//	ofs << "original:" << endl;
		//	for (size_t mi = 0; mi < 3; mi++)
		//	{
		//		ofs << tmpMatrix[mi][0] << " " << tmpMatrix[mi][1] << " " << tmpMatrix[mi][2] << endl;
		//	}
		//	ofs << endl;
		//}

		int num = pp->m_stuNum;
		int index = 0;
		while (num > 0)
		{
			index = (rand() % 6);
			bool minusSuccess = false;
			for (size_t identityIndex = 0; identityIndex < 6; identityIndex++)
			{
				int ii = (index + identityIndex) % 6; // ���ϱ任��λ����

				// �����ݵ�ǰ��λ�����Ƿ���ѧ�����Է�
				bool hasStudent = true;
				for (size_t ri = 0; ri < 3; ri++)
				{
					hasStudent = true;
					for (size_t ci = 0; ci < 3; ci++)
					{
						if (identityMatrix[ii][ri][ci] == 1)
							hasStudent = tmpMatrix[ri][ci] > 0;
					}
					if (!hasStudent)
						break;
				}

				if (!hasStudent)
					continue;
				else
				{
					// ��ѧ��
					for (size_t ri = 0; ri < 3; ri++)
					{
						for (size_t ci = 0; ci < 3; ci++)
						{
							if (identityMatrix[ii][ri][ci] == 1)
							{
								tmpMatrix[ri][ci]--;
								classes[ri][pp->GetSubject(ci)].Push(pp->GetName(), pp->m_stuNum - num); // ��ѧ��
							}
						}
					}
					num--;
					minusSuccess = true;
					break;
				}
			}
			// ����ĳ���༶���������˵��·ֲ��ˣ���ʱ��Ҫ�����༶�����������µ�ѧ��
			// �������ͨ����Ӱ༶����������������������
			if (!minusSuccess)
			{
				vector<pair<int, int>> tmpIndex; // ��Щ��ʱ���ſΣ���-1��ʾ�����ҳ���
				for (size_t ii = 0; ii < 3; ii++)
				{
					for (size_t jj = 0; jj < 3; jj++)
					{
						if (tmpMatrix[ii][jj] == -1)
							tmpIndex.push_back(pair<int, int>(ii, jj));
					}
				}

				int iii = 0;
				for (iii = 0; iii < 6; ++iii)
				{
					int sum = 0;
					for (int jjj = 0; jjj < tmpIndex.size(); ++jjj)
					{
						sum += identityMatrix[iii][tmpIndex[jjj].first][tmpIndex[jjj].second];
					}
					if (sum == 0)
						break;
				}

				for (size_t ri = 0; ri < 3; ri++)
				{
					for (size_t ci = 0; ci < 3; ci++)
					{
						if (identityMatrix[iii][ri][ci] == 1)
						{
							if (tmpMatrix[ri][ci] == 0)
							{
								bool update = false;
								for (size_t ti = 0; ti < 3; ti++)
								{
									if (tmpMatrix[ti][ci] > 2)
									{
										// �����༶�����������µ�ѧ�����˴�Ӧ���������
										tmpMatrix[ti][ci] -= step;
										tmpMatrix[ri][ci] += (step - 1);
										classes[ri][pp->GetSubject(ci)].Push(pp->GetName(), pp->m_stuNum - num); // ��ѧ��
										// ���°༶����
										SubjectMatrix[ti][ci] -= step;
										SubjectMatrix[ri][ci] += step;
									}
								}
							}
							else
							{
								tmpMatrix[ri][ci]--;
								classes[ri][pp->GetSubject(ci)].Push(pp->GetName(), pp->m_stuNum - num);  // ��ѧ��
							}
						}
					}
				}
				num--;
			}

			//if (ofs.is_open())
			//{
			//	for (size_t mi = 0; mi < 3; mi++)
			//	{
			//		ofs << tmpMatrix[mi][0] << " " << tmpMatrix[mi][1] << " " << tmpMatrix[mi][2] << endl;
			//		//cout << tmpMatrix[mi][0] << " " << tmpMatrix[mi][1] << " " << tmpMatrix[mi][2] << endl;
			//	}
			//	ofs << endl << endl;
			//}
		}

		// ��������
		for (size_t mi = 0; mi < 3; mi++)
		{
			copySubjectMatrix[mi][pp->m_s1] = tmpMatrix[mi][0];
			copySubjectMatrix[mi][pp->m_s2] = tmpMatrix[mi][1];
			copySubjectMatrix[mi][pp->m_s3] = tmpMatrix[mi][2];
		}
	}

	// ��������
	if (ofs.is_open())
	{
		// �ְ����
		ofs << "splite students : " << endl << endl;
		for (size_t i = 0; i < 3; i++)
		{
			for (size_t j = 0; j < 6; j++)
			{
				ofs << "i, j : " << i << ", " << j << endl << endl;
				for (size_t k = 0; k < classes[i][j].m_students.size(); k++)
				{
					ofs << classes[i][j].m_students[k] << endl;
				}
			}
			ofs << endl << endl;
		}

		ofs << endl;
		// ���º�İ༶����
		for (size_t i = 0; i < 3; i++)
		{
			for (size_t j = 0; j < 6; j++)
			{
				ofs << SubjectMatrix[i][j] << " ";
			}
			ofs << endl << endl;
		}

		ofs << endl;
		// ÿ��ÿ����Ŀ�ֶ�����
		for (size_t i = 0; i < 3; i++)
		{
			for (size_t j = 0; j < 6; j++)
			{
				ofs << classes[i][j].m_students.size() << " ";
			}
			ofs << endl << endl;
		}

	}
	ofs.close();
	return true;
}




