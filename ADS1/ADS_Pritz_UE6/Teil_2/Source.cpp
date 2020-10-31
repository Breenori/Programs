#include<vector>
#include<string>
#include<iostream>
#include<fstream>
#include<regex>
using std::vector;
using std::ifstream;
using std::string;
using std::cout;

typedef std::vector<vector<double>> matrix;

vector<string> split_string(string const& str, char const delimiter);
matrix read(string const& filename);
matrix multiply(matrix const& matrix1, matrix const& matrix2);
bool is_numeric(string const& str);
void print(matrix const& input_m);

void main()
{
	cout << "First Matrix:\n";
	matrix matrix1(read("matrix2.csv"));
	print(matrix1);
	cout << "Second Matrix:\n";
	matrix matrix2(read("matrix1.csv"));
	print(matrix2);
	
	cout << "Multiplied Matrix:\n";
	matrix multiplied(multiply(matrix1, matrix2));
	print(multiplied);
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
matrix read(string const& filename)
{
	matrix output(0);
	ifstream in(filename);

	if (in)
	{
		int rows(0);
		int cols(0);
		bool firstline(true);
		bool valid_matrix(true);

		if (!in.eof())
		{
			string line("");
			getline(in, line);

			rows = stoi(split_string(line, ' ')[0]);
			cols = stoi(split_string(line, ' ')[1]);
			firstline = false;
		}

		while(!in.eof() && output.size() < rows && valid_matrix)
		{
			string line("");
			getline(in, line);
		
			vector<string> elements = split_string(line, ' ');

			vector<double> row(0);
			if (elements.size() >= cols)
			{
				for (int col(0); col < cols; col++)
				{
					if (is_numeric(elements[col]))
					{
						row.push_back(stod(elements[col]));
					}
				}
			}
			
			
			if(row.size() == cols)
			{
				output.push_back(row);
			}
			else
			{
				valid_matrix = false;
			}
		}

		if (output.size() < rows)
		{
			valid_matrix = false;
		}

		if (!valid_matrix)
		{
			cout << "Ambiguous matrix format found. Terminating read process. \n";
			return matrix();
		}
		else
		{
			return output;
		}
	}
	else
	{
		return matrix();
	}
}
matrix multiply(matrix const& matrix1, matrix const& matrix2)
{
	matrix output(0);

	if (matrix1.empty() || matrix2.empty())
	{
		return output;
	}

	if (matrix1[0].size() == matrix2.size())
	{
		for (int m1_row(0); m1_row < matrix1.size(); m1_row++)
		{
			vector<double> prepared_row(0);
			for (int m2_col(0); m2_col < matrix2[0].size(); m2_col++)
			{
				double sum(0);
				for (int m2_row(0); m2_row < matrix2.size(); m2_row++)
				{
					int m1_col(m2_row);
					double m1_cell = matrix1[m1_row][m1_col];
					double m2_cell = matrix2[m2_row][m2_col];
					sum += m1_cell * m2_cell;
				}
				prepared_row.push_back(sum);
			}
			output.push_back(prepared_row);
		}
	}
	else if (matrix1.size() == matrix2[0].size())
	{
		cout << "Swapped matrices order to allow multiplication.\n";
		output = multiply(matrix2, matrix1);
	}
	else
	{
		cout << "Number of rows and columns doesn't allow for multiplication.\n";
	}

	return output;
}
bool is_numeric(string const& str)
{
	std::regex number_regex("^\\d+\\.?\\d+$");

	return std::regex_match(str, number_regex);
}
void print(matrix const& input_m)
{
	if (input_m.size() > 0)
	{
		for (int row(0); row < input_m.size(); row++)
		{
			for (int col(0); col < input_m[row].size(); col++)
			{
				if (col > 0)
				{
					cout << '\t';
				}
				cout << input_m[row][col];
			}
			cout << std::endl;
		}
	}
	else
	{
		cout << "This matrix is empty.\n";
	}
	cout << std::endl;
}
