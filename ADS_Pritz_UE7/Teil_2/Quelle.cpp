#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<iomanip>
#include "slw.h"
using namespace std;

enum graph_type { gt_vertical, gt_horizontal };

struct aminoacid_type {
						char key; 
						double hydropathicity;
};

vector<string> split_string(string const& str, char const delimiter);
vector<aminoacid_type> get_table(string const& filename);
vector<double> smooth(string const& sequence, size_t const& window_width, vector<aminoacid_type> const& aminoacids);
double normalize(vector<double>& input_vec);
double max(vector<double> const& vec); 
void draw(vector<double> const& vec, double const spacing, graph_type type);
bool valid_letter(char const letter, vector<aminoacid_type> const& aminoacids);
string read_from_file(string const& filename);
string get_seq();
int get_windowsize(string const& seq);
void preprocess(string& s, vector<aminoacid_type> const& aminoacids);

void main()
{
	vector<aminoacid_type> aminoacids(get_table("pairs.csv"));
	string seq(get_seq());
	preprocess(seq, aminoacids);
	cout << "The entered sequence is: " << seq << endl << endl;
	int win_size(get_windowsize(seq));
	vector<double> values(smooth(seq, win_size, aminoacids));
	normalize(values);
	draw(values, 0.1, gt_vertical);
}

vector<aminoacid_type> get_table(string const& filename)
{
	vector<aminoacid_type> aminoacids;
	ifstream input(filename);

	if (input.good())
	{
		while (!input.eof())
		{
			string line("");
			getline(input, line);
			vector<string> elements = split_string(line, ',');
			if (elements.size() >= 2)
			{
				aminoacid_type AA = { elements[0][0], stod(elements[1]) };
				aminoacids.push_back(AA);
			}
		}
	}

	return aminoacids;
}
vector<double> smooth(string const& sequence, size_t const& window_width, vector<aminoacid_type> const& aminoacids)
{
	vector<double> values;
	slw_t window;
	clear(window);
	set_max_size(window, window_width);

	for (size_t i(0); i < window.max_size - 1; i++)
	{
		int index(0);
		while (aminoacids[index].key != sequence[i])
		{
			index++;
		}
		add_value(window, aminoacids[index].hydropathicity);
	}

	for (size_t i(0); i <= sequence.length() - window.max_size; i++)
	{
		int index(0);
		while (aminoacids[index].key != sequence[i+window.max_size-1])
		{
			index++;
		}
		add_value(window, aminoacids[index].hydropathicity);
		values.push_back(window.sum / window.values.size());
	}

	return values;
}
double normalize(vector<double>& input_vec)
{
	double max_val(max(input_vec));
	for (int i(0); i < input_vec.size(); i++)
	{
		input_vec[i] = input_vec[i] / max_val;
	}

	return max_val;
}
double max(vector<double> const& vec)
{
	if (!vec.empty())
	{
		double max(vec[0]);
		for (int i(0); i < vec.size(); i++)
		{
			if (vec[i] > max)
			{
				max = vec[i];
			}
		}
		return max;
	}
	else
	{
		return 0.0;
	}
	
}
void draw(vector<double> const& vec, double const spacing, graph_type type)
{
	if (type == gt_vertical)
	{
		for (int i(0); i < vec.size(); i++)
		{

			// We quantize the value, based on how often the spacing is in the number.
					// Thanks to integer division this even rounds up and is therefor more accurate. (e.g. 0.190 is quantized the same as 0.2 = 4)
			int quants = vec[i] / spacing;
			if (quants < 0)
			{
				quants *= -1;
			}
			cout << i + 1 << " ";
			if (vec[i] > 0)
			{
				cout << fixed << setw(1 / spacing + 1 + 6) << "|";
			}
			else
			{
				cout << fixed << setw(1 / spacing - quants + 1 + 6);
			}

			// Based on how many quants we have, we print one line (horizontal only)
			for (int j(0); j < quants; j++)
			{
				cout << "-";
			}

			if (vec[i] < 0)
			{
				cout << "|";
			}
			cout << endl;
		}
	}
	else
	{
		double offset(1);
		while (offset > 0)
		{
			for (int i(0); i < vec.size(); i++)
			{
				int quants = vec[i] / spacing;
				if (quants >= (int)(offset / spacing))
				{
					cout << "|";
				}
				else
				{
					cout << " ";
				}
			}
			offset -= spacing;
			cout << endl;
		}
		for (int i(0); i < vec.size(); i++)
		{
			cout << "-";
		}
		cout << endl;
		while (offset > -1)
		{
			for (int i(0); i < vec.size(); i++)
			{
				int quants = vec[i] / spacing;
				if (quants <= (int)(offset / spacing) && quants < 0)
				{
					cout << "|";
				}
				else
				{
					cout << " ";
				}
			}
			offset -= spacing;
			cout << endl;
		}
	}
}
bool valid_letter(char const letter, vector<aminoacid_type> const& aminoacids)
{
	bool valid(false);
	int counter(0);
	while (!valid && counter < aminoacids.size())
	{
		if (aminoacids[counter].key == letter)
		{
			valid = true;
		}
		counter++;
	}

	return valid;
}
string read_from_file(string const& filename)
{
	string text("");
	ifstream ifs(filename);

	if (ifs)
	{
		string line("");
		while (!ifs.eof())
		{
			getline(ifs, line);
			if (line[0] != '>' && line[0] != ';')
			{
				for (int i(0); i < line.length(); i++)
				{
					text += line[i];
				}
			}
		}
	}

	return text;
}
std::vector<string> split_string(string const& str, char const delimiter)
{
	int offset(0);
	int element_end(0);
	std::vector<string> elements;

	while (str.find(delimiter, offset) != string::npos)
	{
		//calculate where the next delimiter is and get the substring
		int element_end = str.find(delimiter, offset);
		elements.push_back(str.substr(offset, element_end - offset));
		offset = element_end + 1;
	}

	//if there is no more delimiter, but there are still characters after the last delimiter, add the remaining string to the vector
	if (str.length() - 1 >= offset)
	{
		elements.push_back(str.substr(offset, str.length() - offset));
	}

	return elements;
}
string get_seq() {
	string ans("");
	cout << "Where do you want to read from:\n";
	cout << "(1) Textfile\n";
	cout << "(2) Console\n";
	while (ans != "1" && ans != "2")
	{
		getline(cin, ans);
	}
	cout << endl;
	string text;
	if (ans == "1")
	{
		bool read(false);
		while (!read)
		{
			string filename;
			cout << "Please enter the filename:\n";
			getline(cin, filename);
			text = read_from_file(filename);
			read = true;

			if (text.empty())
			{
				cout << "File is either empty or file not found.\n";
				cout << "Do you want to change the filename? (y/n)";
				getline(cin, ans);
				if (ans == "y" || ans == "Y")
				{
					read = false;
				}
			}
		}
	}
	else
	{
		cout << "Please enter your sequence:\n";
		getline(cin, text);
	}
	return text;
}
int get_windowsize(string const& seq)
{
	int size(-1);
	cout << "Please enter a window size: (must be odd and less than " << seq.length() << ")\n";
	cin >> size;
	while (cin.fail() || size <= 0 || size > seq.length() || size%2==0)
	{
		cout << "Please enter a valid number: ";
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cin >> size;
	}

	return size;
}
void preprocess(string& s, vector<aminoacid_type> const& aminoacids)
{
	for (int i(0); i < s.length(); i++)
	{
		if (!valid_letter(s[i], aminoacids))
		{
			s.erase(s.begin() + i);
		}
	}
}
