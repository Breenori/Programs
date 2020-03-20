#include<iostream>
#include<vector>
#include<string>
#include<fstream>
using std::cout;
using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::stoi;
using std::endl;
using std::ostream;

struct entry_t {
	char* const p_in;
	int index;
};

char* sub_structure(char const* p_in, int const i);
char* c_substr(char const* p, int const begin, int const end);
void read_from_file(vector<entry_t> & entries, string const& filename = "entries.txt");
void write_to_file(vector<entry_t>& entries, ostream& out = cout);
vector<string> split_string(string const& str, char const delimiter);

void main()
{
	vector<entry_t> file_entries;
	read_from_file(file_entries);
	write_to_file(file_entries);
}

char* sub_structure(char const* p_in, int const i)
{
	if (p_in != nullptr)
	{
		int counter(1);
		int offset(i);
		int left(-1);
		int right(-1);

		if (left < 0)
		{
			while (counter > 0 && offset >= 0)
			{
				if (p_in[offset] == '(')
				{
					counter--;
				}
				if (p_in[offset] == ')')
				{
					if (offset != i)
					{
						counter++;
					}
				}
				offset--;
			}
		}

		left = offset+1;

		counter = 1;
		offset = i;
		if (right < 0)
		{
			while (counter > 0 && p_in[offset] != 0)
			{
				if (p_in[offset] == ')')
				{
					counter--;
				}
				if (p_in[offset] == '(')
				{
					if (offset != i)
					{
						counter++;
					}
				}
				offset++;
			}
		}

		right = offset-1;

		return c_substr(p_in, left, right);
	}
	else
	{
		return nullptr;
	}
}
char* c_substr(char const* p, int const begin, int const end)
{
	if (p != nullptr)
	{
		char* dst = new char[(end - begin) + 2];
		int cur_index(0);
		for (int i(begin); i <= end; i++)
		{
			dst[cur_index] = p[i];
			cur_index++;
		}
		dst[cur_index] = '\0';
		return dst;
	}
	else
	{
		return nullptr;
	}
}
void read_from_file(vector<entry_t>& entries, string const& filename)
{
	ifstream in(filename);

	string line;
	if (in)
	{
		while (getline(in, line))
		{
			vector<string> data = split_string(line, ' ');

			char* carray = new char[data[0].length()+1];
			for (int i(0); i < data[0].length(); i++)
			{
				carray[i] = line[i];
			}
			carray[line.length()] = '\0';

			entry_t entry = { carray, stoi(data[1]) };
			entries.push_back(entry);
		}
	}

	in.close();

}
void write_to_file(vector<entry_t>& entries, ostream & out)
{
	if (out)
	{
		for (int i(0); i < entries.size(); i++)
		{
			out << sub_structure(entries[i].p_in, entries[i].index) << endl;
		}
	}
}
vector<string> split_string(string const& str, char const delimiter)
{
	int offset(0);
	int element_end(0);
	vector<string> elements;

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