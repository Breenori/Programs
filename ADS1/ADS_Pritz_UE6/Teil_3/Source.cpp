#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<time.h>
using std::vector;
using std::string;
using std::ifstream;
using std::cin;
using std::cout;


// Since letter and threshold belong together, we store them in a struct.
struct letter_info {
	char letter;
	int threshold;
};

// Returns a vector of letters and their corresponding probabilities, read from a file.
vector<letter_info> get_probabilities(string const& filename);
// Returns an array of all the elements of a string which were split with the given delimiter.
vector<string> split_string(string const& str, char const delimiter);
// Returns the sum of thresholds for all elements in l_info up to index n.
// essentially returns the maximum threshold for a given character at index n that the random number has to be beneath to become that letter.
int sum_of_thresholds(vector<letter_info> const& l_info, int const n);
// Returns a random char based on the probabilities stored in the vector
char get_char(vector<letter_info> const& l_info);
// Returns whether a char is a special character or not
bool is_special(char const c);
// Returns the last non-blank letter in the string
char get_last_letter(string s);
// Returns a number that has been entered by the user and has been checked for errors
int read_number();
// Returns a random text.
string generate_text(vector<letter_info> const& l_info, int const length);

void main()
{
	int length_input(read_number());

	if (length_input > 0)
	{
		srand((int)time(0));
		vector<letter_info> info(get_probabilities("input.csv"));

		string text(generate_text(info, length_input));

		cout << text;
	}
}

vector<letter_info> get_probabilities(string const& filename)
{
	vector<letter_info> l_info(0);

	ifstream in(filename);

	if (in)
	{
		while (!in.eof())
		{
			string line("");
			getline(in, line);

			// Every line consists of the letter followed by the probability.
			char letter(split_string(line,';')[0][0]);
			int threshold(stoi(split_string(line,';')[1]) - 1);
			l_info.push_back({ letter,threshold });
		}
	}

	return l_info;
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
int sum_of_thresholds(vector<letter_info> const& l_info, int const n)
{
	int sum(0);
	for (int i(0); i < n; i++)
	{
		sum += l_info[i].threshold;
	}
	return sum;
}
char get_char(vector<letter_info> const& l_info)
{
	// First we calculate the sum of all the probabilities aka the highest possible outcome of the random number.
	int max_threshold(sum_of_thresholds(l_info, size(l_info)));

	// Based on the threshold, we get a random number in the specified range.
	int letter_num(rand() % (max_threshold + 1));

	// Now we match this to the right letter
	// Each letter has a threshold that is calculated by the sum of the probabilities of the preceding characters PLUS its own probability.
	// Therefor the right letter is determined by comparing the aforementioned threshold for every letter with the random number. 
	int counter(1);
	while (sum_of_thresholds(l_info, counter) < letter_num)
	{
		counter++;
	}
	
	return l_info[counter - 1].letter;
}
bool is_special(char const c)
{
	return c == ' ' || c == ',' || c == '.' || c == '(' || c == '"' || c == '?' || c == '!';
}
char get_last_letter(string s)
{
	if (!s.empty())
	{
		char c(' ');

		int offset(s.length() - 1);
		
		// Decrease the offset as long as the value at the offset is a blank.
		// -> We get the first non-blank character at the end of the string.
		while (s[offset] == ' ' && offset > 0)
		{
			offset--;
		}

		return s[offset];
	}
	else
	{
		return ' ';
	}
}
int read_number()
{
	int num(0);
	cout << "How many characters should the text contain?\n";
	cin >> num;

	// make sure the user enters a valid number
	while (cin.fail())
	{
		num = 0;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "The value must be numeric (MAX:" << INT_MAX << "): ";
		cin >> num;
	}
	// If there's something after the number, clear it.
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	return num;
}
string generate_text(vector<letter_info> const& l_info, int const length)
{
	string text("");

	bool upper_case(true);
	bool open_quotes(false);
	bool open_brackets(false);
	while (text.length() < length)
	{
		char rand_char(get_char(l_info));
		if (text.length() > 1)
		{
			// Double special characters have to be avoided. 
			while (is_special(rand_char) && is_special(get_last_letter(text)))
			{
				rand_char = get_char(l_info);
			}
		}

		// We need to pay attention to special characters dot, exclamation mark, question mark, comma, quotes and brackets.
		if (is_special(rand_char))
		{
			// dots, commas, exclamation marks and ! all share something: They are followed by a blank. 
			// Dots, exclamation marks and question marks also end a sentence ( -> next letter is uppercase)
			if (rand_char == '.' || rand_char == ',' || rand_char == '?' || rand_char == '!')
			{
				if (!text.empty())
				{
					if (text[text.length() - 1] != ' ')
					{
						text += rand_char;
					}
					// If the previous character was a blank, replace the blank with the character and put a blank afterwards.
					else
					{
						text[text.length() - 1] = rand_char;
					}
					text += ' ';

					if (rand_char == '.' || rand_char == '?' || rand_char == '!')
					{
						upper_case = true;
					}
				}
			}
			else if (rand_char == '"')
			{
				// If no quotes are open (without a 2nd quote afterwards) we can just put a quote preceded by a blank.
				if (!open_quotes)
				{
					if (!text.empty() && text[text.length() - 1] != ' ')
					{
						text += ' ';
					}
					text += rand_char;
					open_quotes = true;
					upper_case = true;
				}
				else
				{
					// If quotes are open we have to check if brackets are open, because we have to close them in the right order.
					// End quotes are always followed by a blank.
					if (open_brackets)
					{
						if (text.rfind('(') > text.rfind('"'))
						{
							text += ')';
							open_brackets = false;
						}
					}
					text += rand_char;
					text += ' ';
					open_quotes = false;
				}
			}
			else if (rand_char == '(')
			{
				// Same workflow as the quotes:
				// If no brackets are open, just put a blank followed by the first bracket.
				if (!open_brackets)
				{
					if (!text.empty() && text[text.length() - 1] != ' ')
					{
						text += ' ';
					}
					text += rand_char;
					open_brackets = true;
					upper_case = true;
				}
				// If quotes are open as well, close them in the right order.
				else
				{
					if (open_quotes)
					{
						if (text.rfind('"') > text.rfind('('))
						{
							text += '"';
							open_quotes = false;
						}
					}
					text += ')';
					text += ' ';
					open_brackets = false;
				}
			}
			else if (rand_char == ' ')
			{
				if (!text.empty() && !is_special(text[text.length() - 1]))
				{
					text += rand_char;
				}
			}
		}
		else
		{
			if (upper_case)
			{
				rand_char = toupper(rand_char);
				upper_case = false;
			}
			text += rand_char;
		}
	}

	if (text[text.length()-1] != '.' && text[text.length() - 1] != ',')
	{
		text += '.';
	}
	else if (text[text.length() - 1] == ',')
	{
		text[text.length() - 1] = '.';
	}

	// If there are still open quotes or brackets, we close them.
	// This will however cause the string to be slightly larger than wanted.
	if (open_quotes && open_brackets)
	{
			if (text.rfind('"') > text.rfind('('))
			{
				text += '"';
				text += ')';
				open_quotes = false;
				open_brackets = false;
			}
			else
			{
				text += ')';
				text += '"';
				open_quotes = false;
				open_brackets = false;
			}
	}
	else if (open_quotes)
	{
		text += '"';
		open_quotes = false;
	}
	else if (open_brackets)
	{
		text += ')';
		open_brackets = false;
	}


	return text;
}
