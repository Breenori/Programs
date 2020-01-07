#include<iostream>
#include<fstream>
#include<string>
#include<time.h>
#include<vector>
using std::string;
using std::cout;
using std::cin;
using std::getline;
using std::vector;

typedef vector<double> points_type;
typedef vector<student_type> students_type;

struct name_type {
	string first_name;
	string last_name;
};
struct person_type {
	name_type name;
	int age;
};
struct student_type {
	person_type data;
	int reg_nr;
	points_type points;
};

void matrix_test();
void print_vector(std::vector<int> const& v);
void init(std::vector<int>& v, int const n, bool fill_rand, bool fill_inc, bool fill_dec);

void file_writing();
void read_file(string const& name);
void read_from_stream(std::istream& in);

void data_types_test()
{
	name_type my_name;
	my_name.first_name = "Uvuvwuevwuevwue";
	my_name.last_name = "Onyetwenyenye-Ugwemugwe-Ossas";

	student_type puccini;
	puccini.reg_nr = 17;
	puccini.data.age = 16;
	puccini.data.name.first_name = "Giacomo";
	puccini.data.name.last_name = "Puccini";
	vector<double> points = { 100, 120, 100, 0 };
	puccini.points = points;
}

void main()
{
	//matrix_test();

	/*read_file("pairs.txt");
	read_from_stream(cin);
	std::ifstream in("pairs.txt");
	read_from_stream(in);
	in.close();*/

	

	
}

void init(std::vector<int>& v, int const n, bool fill_rand, bool fill_inc, bool fill_dec)
{
	v.clear();
	v.resize(n);

	srand((int)time(0));

	for (int i(0); i < n; i++)
	{
		if (fill_rand)
		{
			v[i] = rand() % n;
		}
		else if (fill_inc)
		{
			v[i] = i;
		}
		else if (fill_dec)
		{
			v[i] = n - i - 1;
		}
	}
}
void matrix_test()
{
	//read dimensions from console
	//& build matrix randomly

	int cols(0);
	int rows(0);

	cout << "Please enter number of rows:";
	cin >> rows;
	cout << "Please enter number of cols:";
	cin >> cols;

	vector<vector<int>> matrix(rows);

	srand((int)time(0));
	for (size_t i(0); i < rows; i++)
	{
		vector<int> v;
		init(v, cols, true, false, false);
		print_vector(v);
		cout << std::endl;
		matrix[i] = v;
	}
}
void print_vector(std::vector<int> const& v)
{
	for (int i(0); i < std::size(v); i++)
	{
		if (i != 0)
		{
			std::cout << ", ";
		}
		std::cout << v[i];
	}
}

void file_writing()
{
	// read int and string and save them in a file called "out.txt"
	string str("");
	getline(cin, str);
	int x(0);
	cin >> x;

	std::ofstream o("out.txt");
	o << x;
	o << str;
	o.close();
}
void read_file(string const& name)
{
	std::ifstream in(name);
	cout << "Reading the contents of file " << name << std::endl;

	while (!in.eof())
	{
		std::string s;
		getline(in, s);
		cout << s << std::endl;
	}

	in.close();
}
void read_from_stream(std::istream& in)
{
	string s;
	in >> s;
	cout << s << std::endl;
}