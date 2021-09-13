/*
HW3 Andrew Boyce
SU Net ID: 209721818 (amboyce)
HW3
Due: 11:59PM, March 23 (Tuesday)
*/
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <tuple>
#include <vector>
#include <iomanip>

using namespace std;

class course
{
public:
	string name;
	int section;
	int credits;
	string grade;
	course() {}
	course(string n, int s, int c, string g)
	{
		name = n;
		section = s;
		credits = c;
		grade = g;
	}

	//OP overloaded for course.
	friend ostream &operator<<(ostream &os, const course &c)
	{
		os << "(" << c.name << " " << to_string(c.section) << " " << to_string(c.credits) << " " << c.grade << ") ";
		return os;
	}

	//OP overloaded for courses.
	friend ostream &operator<<(ostream &os, const vector<course *> &v)
	{
		for (auto itr2 : v)
			os << (*itr2);
		os << "\n";
		return os;
	}

	//OP overloaded for semester.
	friend ostream &operator<<(ostream &os, const tuple<int, float, vector<course *> *> &t)
	{
		os << "GPA : " << get<1>(t) << "\n";
		os << "Credits : " << get<0>(t) << "\n";
		for (auto itr2 : (*get<2>(t)))
			os << (*itr2);
		os << "\n";
		return os;
	}

	//OP overloaded for semesters map.
	friend ostream &operator<<(ostream &os, const map<int, tuple<int, float, vector<course *> *>> &map)
	{
		for (auto &itr2 : map)
		{
			os << "Semester : " << itr2.first << "\n";
			os << itr2.second;
		}
		return os;
	}

	//OP overloaded for student information (gpa, credits, map of semsters).
	friend ostream &operator<<(ostream &os, const tuple<int, float, map<int, tuple<int, float, vector<course *> *>> *> &t)
	{
		os << "Overall GPA: " << get<1>(t) << "\n";
		os << "Overall Credits: " << get<0>(t) << "\n";
		os << *(get<2>(t));
		return os;
	}

	//OP overloaded for student information with the key as the student id.
	friend ostream &operator<<(ostream &os, const pair<int, tuple<int, float, map<int, tuple<int, float, vector<course *> *>> *>> &t)
	{
		os << "Student ID: " << t.first << "\n";
		os << t.second;
		return os;
	}

	//Op overloaded for list.
	friend ostream &operator<<(ostream &os, const list<pair<int, tuple<int, float, map<int, tuple<int, float, vector<course *> *>> *>> *> &t)
	{
		for (auto itr2 : t)
			os << (*itr2);
		return os;
	}

	//You might need to implement some overloaded operators here.
};
//Implement the following functions.
//When adding a student, if the student is already in DB, then ignore the operation.
//When adding a course, if the course is already in DB, then ignore the operation.
//When dropping a course, if the course does not exist, then ignore the operation.
//When removing a student, if the student does not exist, then ignore the operation.
//All courses in a semester need to be sorted.
//When dropping or adding a course, overall GPA, semester GPA, overall credits and semester credits all need to be updated.

//Semeser numbers:  Spring 2019: 20191; Fall 2019: 20192, etc.

void add_student(list<pair<int, tuple<int, float, map<int, tuple<int, float, vector<course *> *>> *>> *> &DB, int id);
void remove_student(list<pair<int, tuple<int, float, map<int, tuple<int, float, vector<course *> *>> *>> *> &DB, int id);
void add_course(list<pair<int, tuple<int, float, map<int, tuple<int, float, vector<course *> *>> *>> *> &DB, int semester, int id, course c); //20171 Spring semester of 2017; 20172: Fall semester of 2017
																																			  //All courses in the list should be sorted according to name (increasing order)
void drop_course(list<pair<int, tuple<int, float, map<int, tuple<int, float, vector<course *> *>> *>> *> &DB, int semester, int id, course c);
void print_student_semester_courses(list<pair<int, tuple<int, float, map<int, tuple<int, float, vector<course *> *>> *>> *> &DB, int semester, int id);
void print_student_all_courses(list<pair<int, tuple<int, float, map<int, tuple<int, float, vector<course *> *>> *>> *> &DB, int id);

//Implement additional functions such that you can do
//cout << DB << endl;

//You might need to implement some overloaded operators in the course class.

int main()
{

	list<pair<int, tuple<int, float, map<int, tuple<int, float, vector<course* >*> >*> >*>  DB;

	add_student(DB, 11111);
	course C1("CIS554", 1, 3, "A-"), C2("CSE674", 1, 3, "B+"), C3("MAT296", 8, 4, "A"), C4("WRT205", 5, 3, "A");

	add_course(DB, 20171, 11111, C1);
	add_course(DB, 20171, 11111, C4);
	add_course(DB, 20171, 11111, C3);
	add_course(DB, 20171, 11111, C2);
	print_student_semester_courses(DB, 20171, 11111);

	drop_course(DB, 20171, 11111, C1);
	print_student_semester_courses(DB, 20171, 11111); //sorted according to course name

	course C5("CIS351", 2, 3, "A-"), C6("PSY205", 5, 3, "B+"), C7("MAT331", 2, 3, "A"), C8("ECN203", 4, 3, "A");
	add_course(DB, 20172, 11111, C5);
	add_course(DB, 20172, 11111, C6);
	add_course(DB, 20172, 11111, C7);
	add_course(DB, 20172, 11111, C8);
	add_course(DB, 20172, 11111, C3);
	print_student_all_courses(DB, 11111);//ID GPA

	add_student(DB, 11112);
	add_course(DB, 20171, 11112, C2);
	add_course(DB, 20171, 11112, C5);
	add_course(DB, 20171, 11112, C7);
	add_course(DB, 20171, 11112, C4);
	print_student_semester_courses(DB, 20171, 11112);

	add_course(DB, 20172, 11112, C8);
	add_course(DB, 20172, 11112, C3);
	add_course(DB, 20172, 11112, C5);
	add_course(DB, 20172, 11112, C1);
	print_student_semester_courses(DB, 20172, 11112);

	print_student_all_courses(DB, 11112);

	cout << DB << endl;
	remove_student(DB, 11111);
	cout << DB << endl;
	getchar();
	getchar();
	return 0;
}

void add_student(list<pair<int, tuple<int, float, map<int, tuple<int, float, vector<course *> *>> *>> *> &DB, int id)
{
	auto it1{DB.begin()};
	bool found{false};
	while (it1 != DB.end())
	{
		if ((*it1)->first == id)
			found = true;
		it1++;
	}
	if (found)
		return;
	auto p = new pair<int, tuple<int, float, map<int, tuple<int, float, vector<course *> *>> *>>{id, {0, 0.00, new map<int, tuple<int, float, vector<course *> *>>}};
	DB.push_back(p);
}

void remove_student(list<pair<int, tuple<int, float, map<int, tuple<int, float, vector<course *> *>> *>> *> &DB, int id)
{
	auto it1{DB.begin()};
	bool found{false};
	while (it1 != DB.end())
	{
		if ((*it1)->first == id)
		{
			DB.remove(*it1);
			return;
		}
		it1++;
	}
}

void add_course(list<pair<int, tuple<int, float, map<int, tuple<int, float, vector<course *> *>> *>> *> &DB, int semester, int id, course c)
{
	auto it1{DB.begin()};
	bool found{false};
	while (it1 != DB.end())
	{
		if ((*it1)->first == id)
		{
			found = true;
			break;
		}
		it1++;
	}
	if (found)
	{
		map<int, tuple<int, float, vector<course *> *>> *map = get<2>((*it1)->second);
		if ((*map).find(semester) == (*map).end())
		{
			vector<course *> *classes = new vector<course *>();
			course *class1 = new course{(&c)->name, (&c)->section, (&c)->credits, (&c)->grade};
			(*classes).push_back(class1);
			float gpa = 0.00;
			string grade = (&c)->grade;
			if (grade == "A")
			{
				gpa = 4.0;
			}
			else if (grade == "A-")
			{
				gpa = 3.6666;
			}
			else if (grade == "B+")
			{
				gpa = 3.3333;
			}
			else if (grade == "B")
			{
				gpa = 3.00;
			}
			else if (grade == "B-")
			{
				gpa = 2.6666;
			}
			else if (grade == "C+")
			{
				gpa = 2.3333;
			}
			else if (grade == "C")
			{
				gpa = 2.00;
			}
			else if (grade == "C-")
			{
				gpa = 1.6666;
			}
			else if (grade == "D")
			{
				gpa = 1.00;
			}
			else if (grade == "D-")
			{
				gpa = 0.666;
			}
			else
				gpa = 0.00;
			tuple<int, float, vector<course *> *> semesterInfo{(&c)->credits, gpa, (vector<course *> *)classes};
			(*map).insert({semester, semesterInfo});
			auto overallStats = (*it1)->second;
			int overallCredits = 0;
			float overallGradePoints = 0.00;
			for (auto itr2{(*map).begin()}; itr2 != (*map).end(); itr2++)
			{
				auto semInfo = itr2->second;
				overallCredits += get<0>(semInfo);
				overallGradePoints += get<0>(semInfo) * get<1>(semInfo);
			}
			get<0>((*it1)->second) = overallCredits;
			get<1>((*it1)->second) = overallGradePoints / overallCredits;
			return;
		}
		for (auto itr2{(*map).begin()}; itr2 != (*map).end(); itr2++)
		{
			if (itr2->first == semester)
			{
				tuple<int, float, vector<course *> *> semesterInfo = itr2->second;
				auto courses = get<2>(semesterInfo);
				for (auto itr3{(*courses).begin()}; itr3 != (*courses).end(); itr3++)
					if ((*itr3)->name == (&c)->name)
						return;
				bool found{false};
				for (auto itr3{(*courses).begin()}; itr3 != (*courses).end(); itr3++)
				{
					if ((&c)->name > (*itr3)->name)
					{
						course *class1 = new course{(&c)->name, (&c)->section, (&c)->credits, (&c)->grade};
						(*courses).insert(itr3 + 1, class1);
						found = true;
						break;
					}
				}
				if (!found)
				{
					course *class1 = new course{(&c)->name, (&c)->section, (&c)->credits, (&c)->grade};
					(*courses).push_back(class1);
				}
				bool swapable = true;
				while (swapable)
				{
					swapable = false;
					for (size_t i = 0; i < (*courses).size() - 1; i++)
					{
						if ((*courses)[i]->name > (*courses)[i + 1]->name)
						{
							swap((*courses)[i], (*courses)[i + 1]);
							swapable = true;
						}
					}
				}
				float overallGradePoints = 0;
				float cred = 0;
				for (auto itr3{(*courses).begin()}; itr3 != (*courses).end(); itr3++)
				{
					cred += (*itr3)->credits;
					float gpa = 0.00;
					string grade = (*itr3)->grade;
					if (grade == "A")
					{
						gpa = 4.0;
					}
					else if (grade == "A-")
					{
						gpa = 3.6666;
					}
					else if (grade == "B+")
					{
						gpa = 3.3333;
					}
					else if (grade == "B")
					{
						gpa = 3.00;
					}
					else if (grade == "B-")
					{
						gpa = 2.6666;
					}
					else if (grade == "C+")
					{
						gpa = 2.3333;
					}
					else if (grade == "C")
					{
						gpa = 2.00;
					}
					else if (grade == "C-")
					{
						gpa = 1.6666;
					}
					else if (grade == "D")
					{
						gpa = 1.00;
					}
					else if (grade == "D-")
					{
						gpa = 0.666;
					}
					else
						gpa = 0.00;
					overallGradePoints += (*itr3)->credits * gpa;
				}
				itr2->second = make_tuple(cred, (overallGradePoints / cred), courses);
				auto overallStats = (*it1)->second;
				int overallCredits = 0;
				float totalGradePoints = 0.00;
				for (auto itr2{(*map).begin()}; itr2 != (*map).end(); itr2++)
				{
					auto semInfo = itr2->second;
					overallCredits += get<0>(semInfo);
					totalGradePoints += (get<0>(semInfo) * get<1>(semInfo));
				}
				get<0>((*it1)->second) = overallCredits;
				get<1>((*it1)->second) = totalGradePoints / overallCredits;
				return;
			}
		}
	}
	return;
}

void drop_course(list<pair<int, tuple<int, float, map<int, tuple<int, float, vector<course *> *>> *>> *> &DB, int semester, int id, course c)
{
	auto it1{DB.begin()};
	bool found{false};
	while (it1 != DB.end())
	{
		if ((*it1)->first == id)
		{
			found = true;
			break;
		}
		it1++;
	}
	if (found)
	{
		map<int, tuple<int, float, vector<course *> *>> *map = get<2>((*it1)->second);
		if ((*map).empty())
			return;
		for (auto itr2{(*map).begin()}; itr2 != (*map).end(); itr2++)
		{
			if (itr2->first == semester)
			{
				auto semesterInfo = itr2->second;
				auto courses = get<2>(semesterInfo);
				auto it = (*courses).begin();
				bool found{false};
				while (it != (*courses).end())
				{
					if ((*it)->name == (&c)->name)
					{
						(*courses).erase(it);
						found = true;
						break;
					}
				}
				if (!found)
					return;
				float overallGradePoints = 0;
				float cred = 0;
				for (auto itr3{(*courses).begin()}; itr3 != (*courses).end(); itr3++)
				{
					cred += (*itr3)->credits;
					float gpa = 0.00;
					string grade = (*itr3)->grade;
					if (grade == "A")
					{
						gpa = 4.0;
					}
					else if (grade == "A-")
					{
						gpa = 3.6666;
					}
					else if (grade == "B+")
					{
						gpa = 3.3333;
					}
					else if (grade == "B")
					{
						gpa = 3.00;
					}
					else if (grade == "B-")
					{
						gpa = 2.6666;
					}
					else if (grade == "C+")
					{
						gpa = 2.3333;
					}
					else if (grade == "C")
					{
						gpa = 2.00;
					}
					else if (grade == "C-")
					{
						gpa = 1.6666;
					}
					else if (grade == "D")
					{
						gpa = 1.00;
					}
					else if (grade == "D-")
					{
						gpa = 0.666;
					}
					else
						gpa = 0.00;
					overallGradePoints += (*itr3)->credits * gpa;
				}
				itr2->second = make_tuple(cred, (overallGradePoints / cred), courses);
				auto &overallStats = (*it1)->second;
				int overallCredits = 0;
				float totalGradePoints = 0.00;
				for (auto itr2{(*map).begin()}; itr2 != (*map).end(); itr2++)
				{
					auto semInfo = itr2->second;
					overallCredits += get<0>(semInfo);
					totalGradePoints += get<0>(semInfo) * get<1>(semInfo);
				}
				get<0>((*it1)->second) = overallCredits;
				get<1>((*it1)->second) = totalGradePoints / overallCredits;
				return;
			}
		}
	}
	return;
}

void print_student_semester_courses(list<pair<int, tuple<int, float, map<int, tuple<int, float, vector<course *> *>> *>> *> &DB, int semester, int id)
{
	auto it1{DB.begin()};
	bool found{false};
	while (it1 != DB.end())
	{
		if ((*it1)->first == id)
		{
			found = true;
			break;
		}
		it1++;
	}
	if (found)
	{
		map<int, tuple<int, float, vector<course *> *>> *map = get<2>((*it1)->second);
		if ((*map).empty())
			return;
		for (auto itr2{(*map).begin()}; itr2 != (*map).end(); itr2++)
		{
			if (itr2->first == semester)
			{
				auto &semesterInfo = itr2->second;
				auto courses = get<2>(semesterInfo);
				cout << "Student ID: " << id << endl;
				cout << "Semester: " << semester << endl;
				cout << "GPA : ";
				cout << fixed;
				cout << setprecision(2);
				cout << (float)get<1>(semesterInfo) << endl;
				cout << "Credits : " << get<0>(semesterInfo) << endl;
				for (auto itr3{(*courses).begin()}; itr3 != (*courses).end(); itr3++)
				{
					cout << "(" << (*itr3)->name << " " << to_string((*itr3)->section) << " " << to_string((*itr3)->credits)
						 << " " << (*itr3)->grade << ") ";
				}
				cout << endl;
				cout << endl;
			}
		}
	}
	return;
}
void print_student_all_courses(list<pair<int, tuple<int, float, map<int, tuple<int, float, vector<course *> *>> *>> *> &DB, int id)
{
	auto it1{DB.begin()};
	bool found{false};
	while (it1 != DB.end())
	{
		if ((*it1)->first == id)
		{
			found = true;
			break;
		}
		it1++;
	}
	if (found)
	{
		map<int, tuple<int, float, vector<course *> *>> *map = get<2>((*it1)->second);
		if ((*map).empty())
			return;
		cout << "Student ID: " << id << endl;
		auto &overallStats = (*it1)->second;
		cout << "Overall GPA : ";
		cout << fixed;
		cout << setprecision(2);
		cout << (float)get<1>(overallStats) << endl;
		cout << "Overall Credits : " << get<0>(overallStats) << endl;
		for (auto itr2{(*map).begin()}; itr2 != (*map).end(); itr2++)
		{
			auto &semesterInfo = itr2->second;
			auto &courses = get<2>(semesterInfo);
			cout << "Semester: " << itr2->first << endl;
			cout << "GPA : ";
			cout << fixed;
			cout << setprecision(2);
			cout << (float)get<1>(semesterInfo) << endl;
			cout << "Credits : " << get<0>(semesterInfo) << endl;
			for (auto itr3{(*courses).begin()}; itr3 != (*courses).end(); itr3++)
			{
				cout << "(" << (*itr3)->name << " " << to_string((*itr3)->section) << " " << to_string((*itr3)->credits)
					 << " " << (*itr3)->grade << ") ";
			}
			cout << endl;
		}
		cout << endl;
	}
	return;
}
