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

// Returns a vector of aminoacids to map abbreviations to hydropathicity
vector<aminoacid_type> get_table(string const& filename);
// Returns the content of a file
string read_from_file(string const& filename);
// Returns the elements of a string separated by the given delimiter
vector<string> split_string(string const& str, char const delimiter);
// Returns input from console or file
string get_seq();
// Returns if a letter is valid (aka if the letter is found in the table)
bool valid_letter(char const letter, vector<aminoacid_type> const& aminoacids);
// Removes invalid characters from the sequence
void preprocess(string& s, vector<aminoacid_type> const& aminoacids);
// Reads an integer from the user and returns it. Checks if it's valid in the context (less than sequence length, above zero, odd)
int get_windowsize(string const& seq);
// Returns the graph_type entered by the user
graph_type get_type();
// Returns a vector with values smoothed out by using an average function on a window
vector<double> smooth(string const& sequence, size_t const& window_width, vector<aminoacid_type> const& aminoacids);
// Normalizes a vector and returns the initial max value
double normalize(vector<double>& input_vec);
// Returns the maximum absolute value in a vector. Used by "normalize"
double max(vector<double> const& vec);
// Prints the graph of a corresponding vector with the desired spacing and type
void draw(vector<double> const& vec, double const max, double const spacing, graph_type type);

void main()
{
	vector<aminoacid_type> aminoacids(get_table("pairs.csv"));

	// Prepare the sequence
	string seq(get_seq());
	preprocess(seq, aminoacids);
	cout << "The entered sequence is: " << seq << endl << endl;

	// Choose window size and display type
	int win_size(get_windowsize(seq));
	graph_type type(get_type());

	// Normalize the values and determine max
	vector<double> values(smooth(seq, win_size, aminoacids));
	double max(normalize(values));

	// Print graph and additional info
	draw(values, max, 0.05, type);
	cout << "\nTo get the absolute values, simply multiply the maximum number (" << max << ") with the Y-values (0.05 per step).\n";
}

vector<aminoacid_type> get_table(string const& filename)
{
	vector<aminoacid_type> aminoacids;
	ifstream input(filename);

	// If the file has been found, do something.
	if (input.good())
	{
		// Read every line
		while (!input.eof())
		{
			string line("");
			getline(input, line);
			vector<string> elements = split_string(line, ',');
			// for every line check if the 2 values are present
			// if thats the case, save the abbreviation and the corresponding hydropathicity and add it to the vector
			if (elements.size() >= 2)
			{
				aminoacid_type AA = { toupper(elements[0][0]), stod(elements[1]) };
				aminoacids.push_back(AA);
			}
		}
	}

	return aminoacids;
}
string read_from_file(string const& filename)
{
	string text("");
	ifstream ifs(filename);

	// Reads the text line by line and adds lines that are NOT definitions or comments in fasta files (that dont start with > or ;)
	if (ifs)
	{
		string line("");
		while (!ifs.eof())
		{
			getline(ifs, line);
			if (line[0] != '>' && line[0] != ';')
			{
				text += line;
			}
		}
	}

	return text;
}
vector<string> split_string(string const& str, char const delimiter)
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

	// Ask the user where to read from interactively
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

			// Notify the user if the file could be invalid
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
bool valid_letter(char const letter, vector<aminoacid_type> const& aminoacids)
{
	bool valid(false);
	int counter(0);
	// Search every element in the aminoacid vector
	while (!valid && counter < aminoacids.size())
	{
		if (aminoacids[counter].key == toupper(letter))
		{
			valid = true;
		}
		counter++;
	}

	return valid;
}
void preprocess(string& s, vector<aminoacid_type> const& aminoacids)
{
	// Remove all escape characters
	while (s.find("\\", 0) != string::npos)
	{
		s.replace(s.find("\\", 0), 1, "");
	}
	// Remove all other chars that aren't in the aminoacid table
	for (int i(0); i < s.length(); i++)
	{
		if (!valid_letter(s[i], aminoacids))
		{
			s.replace(i, 1, "");
		}
	}
}
int get_windowsize(string const& seq)
{
	int size(-1);
	cout << "Please enter a window size: (must be odd and less than " << seq.length() << ")\n";
	cin >> size;
	// Read in a valid number until it meets the needed criteria
	while (cin.fail() || size <= 0 || size > seq.length() || size % 2 == 0)
	{
		cout << "Please enter a valid number: ";
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cin >> size;
	}

	return size;
}
graph_type get_type()
{
	string ans;
	cout << "How would you like to display the values?\n";
	cout << "(1) Horizontally\n";
	cout << "(2) Vertically\n";
	while (ans != "1" && ans != "2")
	{
		getline(cin, ans);
	}

	if (ans == "1")
	{
		return gt_horizontal;
	}
	else
	{
		return gt_vertical;
	}
}
vector<double> smooth(string const& sequence, size_t const& window_width, vector<aminoacid_type> const& aminoacids)
{
	vector<double> values;
	// Prepare sliding window.
	// My version of the sliding window also holds the current sum which improves performance for large windowsizes. This needs to be set to 0 at first (init).
	slw_t window;
	init(window);
	set_max_size(window, window_width);

	// Fill up the window to max_size - 1 (because 1 is being added for every iteration later, filling it up at the beginning)
	for (size_t i(0); i < window.max_size - 1; i++)
	{
		int index(0);
		while (aminoacids[index].key != sequence[i])
		{
			index++;
		}
		add_value(window, aminoacids[index].hydropathicity);
	}

	// Search the corresponding amino-acid hydropathicity, calculate the average and add it to the vector.
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
	// Searches the maximum value in the vector and divides all elements of the vector with it.
	// this results in values between 0 and 1.
	double max_val(max(input_vec));
	for (int i(0); i < input_vec.size(); i++)
	{
		input_vec[i] = input_vec[i] / max_val;
	}

	return max_val;
}
double max(vector<double> const& vec)
{
	// If vector is empty, return 0.0 as max
	// Otherwise search for the largest element in linear fashion.
	if (!vec.empty())
	{
		double max(abs(vec[0]));
		for (int i(1); i < vec.size(); i++)
		{
			if (abs(vec[i]) > max)
			{
				max = abs(vec[i]);
			}
		}
		return max;
	}
	else
	{
		return 0.0;
	}
	
}
void draw(vector<double> const& vec, double const max, double const spacing, graph_type type)
{
	cout << endl;

	if (type == gt_vertical)
	{
		cout << fixed << setw(9) << "-1.0" << fixed << setw(1 / spacing) << "0.0" << fixed << setw(1 / spacing) << "1.0" << endl;
		cout << fixed << setw(9) << "  v " << fixed << setw(1 / spacing) << " v " << fixed << setw(1 / spacing) << " v " << endl;

		for (int i(0); i < vec.size(); i++)
		{

			// We quantize the value, based on how often the spacing fits in the number.
			// This shouldn't be negative in this case, which is why we use the abs function
			int quants = abs(vec[i] / spacing);

			// We the index and a fixed amount of whitespaces for the '|' to always be central
			cout << fixed << setw(6) << i + 1 << "#";
			if (vec[i] > 0)
			{
				cout << fixed << setw(1 / spacing + 1) << "|";
			}
			else
			{
				cout << fixed << setw(1 / spacing - quants + 1);
			}

			// Based on how many quants we have, we print one line 
			for (int j(0); j < quants; j++)
			{
				cout << '-';
			}

			// If the hydrophacity is negative, the line ends with '|'
			if (vec[i] < 0)
			{
				cout << "|";
				cout << fixed << setw(1 / spacing + 1) << "#";
			}
			else
			{
				cout << fixed << setw( 1 / spacing -quants + 1) << "#";
			}
			cout << endl;
		}
	}
	else
	{
		// A common value for the width of console windows is 80.
		// If the length of the vector is larger than it, we cut it.
		int len(vec.size());
		if (len > 75)
		{
			len = 75;
			cout << "Cutting the length due to console limitations.\n\n";
		}

		for (int i(0); i < 80; i++)
		{
			cout << "#";
		}
		cout << endl;

		// We start by searching for the maximum (e.g. 1) and decrease it based on the spacing.
		// We then compare if the current value is above our threshold which is slowly decreased.
		double threshold(1);
		while (threshold > 0)
		{
			// Print orientation marks.
			// NOTE: We can't check for straight values (e.g. threshold <= 0.5) because comma values in c++ aren't exact.
			// E.g. 0.05 = 0.05000000000000000278 and that little difference makes it more complicated 
			if (threshold == 1)
			{
				cout << " 1.0 ";
			}
			else if (threshold <= 0.5 && threshold > 0.49)
			{
				cout << " 0.5 ";
			}
			else
			{
				cout << "     ";
			}
			for (int i(0); i < len; i++)
			{
				if (vec[i] >= threshold)
				{
					cout << "|";
				}
				else
				{
					cout << " ";
				}
			}
			threshold -= spacing;
			cout << endl;
		}

		// Print the zero line
		cout << " 0.0 ";
		for (int i(0); i <= len-1; i++)
		{
			cout << "-";
		}
		cout << endl;

		
		threshold = 0;
		double minimum(0 - (int)(1 / spacing) * spacing);
		while (threshold >= -1.01)
		{
			// Print orientation marks
			if ((int)threshold == -1)
			{
				cout << "-1.0 ";
			}
			else if (threshold <= -0.5 && threshold > -0.59)
			{
				cout << "-0.5 ";
			}
			else
			{
				cout << "     ";
			}

			// Print values below 0 row by row
			for (int i(0); i < len; i++)
			{
				if (vec[i] <= threshold && vec[i] < 0)
				{
					cout << "|";
				}
				else
				{
					cout << " ";
				}
			}
			threshold -= spacing;
			cout << endl;
		}
		for (int i(0); i < 80; i++)
		{
			cout << "#";
		}
		cout << endl;
	}
}