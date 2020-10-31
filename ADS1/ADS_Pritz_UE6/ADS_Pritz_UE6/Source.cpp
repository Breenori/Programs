#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<time.h>
using std::string;
using std::vector;
using std::ofstream;
using std::cout;


struct name_type {
	string surname;
	string lastname;
};
struct person_type {
	name_type name;
	int age;
};
typedef vector<int> points_type;
struct student_type {
	person_type data;
	__int64 reg_nr;
	points_type points;
};
typedef vector<student_type> students_type;

int MIN_AGE = 17;
int MAX_AGE = 60;

int get_rand_age();
int get_rand_point();
points_type get_rand_points(int const n);
__int64 get_rand_regnr();
student_type get_rand_student(string const& surname, string const& lastname, int const n_points);
double median(points_type const& points);
bool odd(int const& n);
void print_person(person_type const& person);
void print_points(points_type const& points);
void print_student(student_type const& student);
void print_students(students_type const& students);
void rearrange(students_type& students, int const i, int const j, bool const stable);
void rotate(students_type& students, int const i, int const j);
void sort_surnames(students_type& students, bool const stable);
void sort_lastnames(students_type& students, bool const stable);
void sort_points(points_type& points);
void sort_points_of_students(students_type& students);
void swap(students_type& students, int const i, int const j);
int compare_strings(string const& str1, string const& string2);

void main()
{
	srand((int)time(0));
	students_type students = { get_rand_student("Giacomo", "Puccini", 5), get_rand_student("Tom", "Turbo", 4), get_rand_student("Tony", "Stark", 3), get_rand_student("Ramsey", "Cook", 3), get_rand_student("Tom", "Cook", 3), get_rand_student("John", "Cortana", 4), get_rand_student("Andreas", "Bourani", 6) };
	sort_points_of_students(students);
	sort_lastnames(students, true);

	print_students(students);
}

int get_rand_age()
{
	return (rand()%(MAX_AGE - MIN_AGE + 1)) + MIN_AGE;
}
int get_rand_point()
{
	return rand() % 101;
}
points_type get_rand_points(int const n)
{
	points_type points(0);
	for (int i(0); i < n; i++)
	{
		points.push_back(get_rand_point());
	}
	return points;
}
__int64 get_rand_regnr()
{
	return 1910458000 + rand() % 1000;
}
student_type get_rand_student(string const& surname, string const& lastname, int const n_points)
{
	student_type student;
	student.data.name.surname = surname;
	student.data.name.lastname = lastname;
	student.data.age = get_rand_age();
	student.points = get_rand_points(rand()%10);
	student.reg_nr = get_rand_regnr();

	return student;
}
double median(points_type const& points)
{
	if (points.empty())
	{
		return 0.00;
	}

	points_type tmp = points;
	sort_points(tmp);
	
	if (odd(size(tmp)))
	{
		return (tmp[size(tmp) / 2] * 1.00);
	}
	else
	{
		return (tmp[size(tmp) / 2] + tmp[size(tmp) / 2 - 1]) * 1.00 / 2;
	}
}
bool odd(int const& n)
{
	return !(n%2==0);
}
void print_person(person_type const& person)
{
	cout << "Name: " << person.name.surname << " " << person.name.lastname << std::endl;
	cout << "Age: " << person.age << std::endl;
}
void print_points(points_type const& points)
{
	cout << "Points: " << std::endl;
	for (int i(0); i < size(points); i++)
	{
		cout << points[i];
		if (i < size(points) - 1)
		{
			cout << ", ";
		}
	}
	cout << std::endl << "Median: " << median(points) << std::endl;
}
void print_student(student_type const& student)
{
	cout << "Reg. Number: " << student.reg_nr << std::endl;
	print_person(student.data);
	print_points(student.points);
}
void print_students(students_type const& students)
{
	if (students.empty())
	{
		cout << "No students found.";
	}
	for (int i(0); i < size(students); i++)
	{
		print_student(students[i]);
		cout << std::endl;
	}
}
void rearrange(students_type& students, int const i, int const j, bool const stable)
{
	if (stable)
	{
		rotate(students, i, j);
	}
	else
	{
		swap(students, i, j);
	}
}
void rotate(students_type& students, int const i, int const j)
{
	student_type tmp = students[j];
	
	for (int k(j - 1); k >= i; k--)
	{
		students[k + 1] = students[k];
	}
	students[i] = tmp;
}
void sort_surnames(students_type& students, bool const stable)
{
	if (!students.empty())
	{
		for (int i(0); i < size(students) - 1; i++)
		{
			int j(i);
			for (int k(i + 1); k < size(students); k++)
			{
				string name1 = students[k].data.name.surname;
				string name2 = students[j].data.name.surname;
				if (compare_strings(name1, name2) < 0)
				{
					j = k;
				}
			}
			rearrange(students, i, j, stable);
		}
	}
}
void sort_lastnames(students_type& students, bool const stable)
{
	if (!students.empty())
	{
		for (int i(0); i < size(students) - 1; i++)
		{
			int j(i);
			for (int k(i + 1); k < size(students); k++)
			{
				string name1 = students[k].data.name.lastname;
				string name2 = students[j].data.name.lastname;
				if (compare_strings(name1, name2) < 0)
				{
					j = k;
				}
			}
			rearrange(students, i, j, stable);
		}
	}
}
void sort_points(points_type& points)
{
	if (points.empty())
	{
		return;
	}
	for (int i(0); i < size(points) - 1; i++)
	{
		int j = i;
		for (int k(i + 1); k < size(points); k++)
		{
			if (points[k] < points[j])
			{
				j = k;
			}
		}
		
		// Swapping two variables without additional variable.
		int tmp = points[i];
		points[i] = points[j];
		points[j] = tmp;
	}
}
void sort_points_of_students(students_type& students)
{
	for (int i(0); i < size(students); i++)
	{
		sort_points(students[i].points);
	}
}
void swap(students_type& students, int const i, int const j)
{
	student_type tmp = students[i];
	students[i] = students[j];
	students[j] = tmp;
}
int compare_strings(string const& str1, string const& str2)
{
	int state(0);
	int counter(0);

	while (counter < str1.length() && counter < str2.length() && state == 0)
	{
		if (toupper(str1[counter]) < toupper(str2[counter]))
		{
			state = -1;
		}
		else if (toupper(str1[counter]) > toupper(str2[counter]))
		{
			state = 1;
		}
		counter++;
	}

	if (state == 0 && str1.length() < str2.length())
	{
		state = -1;
	}
	else if(state == 0 && str1.length() > str2.length())
	{
		state = 1;
	}

	return state;
}

