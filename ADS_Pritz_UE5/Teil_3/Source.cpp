#include<iostream>
#include<string>
#include<vector>
using namespace std;

enum strictness_type {normal, strict};
typedef vector<vector<int>> matrix;

// Checks if a single char is A,G,C or T.
bool is_valid_DNA_char(char const nucleotid);
// Reads a valid DNA string from the console and returns it.
string read_DNA();
// prints out the matrix with description of colums and rows
void print_matrix(matrix const& matrix, string const& dna1, string const& dna2);
// calculates a dot matrix using two strings and returns the matrix.
// bool "strict" decides strictness. false = normal, true = strict matrix.
matrix calc_dot_matrix(string const& dna1, string const& dna2, strictness_type const type);

void main()
{
	cout << "(1)";
	string dna1(read_DNA());
	cout << "(2)";
	string dna2(read_DNA());

	if (!dna1.empty() && !dna2.empty())
	{
		matrix normal_dot_matrix(calc_dot_matrix(dna1, dna2, normal));

		cout << endl << "Normal dot matrix:" << endl;
		print_matrix(normal_dot_matrix, dna1, dna2);

		matrix strict_dot_matrix(calc_dot_matrix(dna1, dna2, strict));
		cout << endl << "Strict dot matrix:" << endl;
		print_matrix(strict_dot_matrix, dna1, dna2);
	}
	else
	{
		cout << std::endl << "One or more sequences missing. Terminating.";
	}
}

bool is_valid_DNA_char(char const nucleotid)
{
	if (std::toupper(nucleotid) == 'A' || std::toupper(nucleotid) == 'T' || std::toupper(nucleotid) == 'G' || std::toupper(nucleotid) == 'C')
	{
		return true;
	}
	else
	{
		return false;
	}

}
string read_DNA()
{
	bool input_required(true);
	string dna;

	std::cout << "Please enter a DNA-Sequence: \n";

	// Read user input and check for validity of the string (only C,G,A,T as chars).
	while (input_required)
	{
		std::getline(cin, dna);

		// Counts the amount of valid chars. If an invalid char is found, step out of the loop and repeat input.
		int counter(0);
		while (is_valid_DNA_char(dna[counter]) && counter < dna.length())
		{
			counter++;
		}

		// If the the amount of valid chars is equal to the strings length, all chars are valid and the program can continue.
		if (counter == dna.length())
		{
			input_required = false;
		}
		else
		{
			cout << "Invalid DNA-Sequence. Please re-enter: ";
		}
	}

	// Convert string to uppercase
	for (int i(0); i < dna.length(); i++)
	{
		dna[i] = std::toupper(dna[i]);
	}

	return dna;
}
void print_matrix(matrix const& matrix, string const& dna1, string const& dna2)
{
	// First lines serve as column descriptions and formatting
	cout << "  | ";
	for (int i(0); i < dna1.length(); i++)
	{
		cout << dna1[i];
		cout << " | ";
	}
	cout << std::endl;
	cout << "---";
	for (int i(0); i < dna1.length(); i++)
	{
		cout << "----";
	}
	cout << std::endl;

	// Loop to check matrix for values of "1" and print an X
	// If "0" found, print blank.
	// New line after every row and blanks between columns
	for (int i(0); i < dna2.length(); i++)
	{
		cout << dna2[i] << " | ";
		for (int j(0); j < dna1.length(); j++)
		{
			if (matrix[i][j])
			{
				cout << "X";
			}
			else
			{
				cout << " ";
			}

			cout << " | ";
		}
		cout << std::endl;
	}
	cout << std::endl;
}
matrix calc_dot_matrix(string const& dna1, string const& dna2, strictness_type const type = normal)
{
	// Create a two-dimensional vector of type int and give it enough rows to compare every letter
	matrix matrix;
	matrix.resize(dna2.length());
	
	if (type == normal)
	{
		for (int i(0); i < dna2.length(); i++)
		{
			for (int j(0); j < dna1.length(); j++)
			{
				// check if current letter is the same
				if (dna2[i] == dna1[j])
				{
					matrix[i].push_back(1);
				}
				else
				{
					matrix[i].push_back(0);
				}
			}
		}
	}
	// if strict is set to true, use different algorithm
	else
	{
		for (int i(0); i < dna2.length()-1; i++)
		{
			for (int j(0); j < dna1.length()-1; j++)
			{
				//check if current letter AND next letter are the same.
				if (dna2[i] == dna1[j] && dna2[i+1] == dna1[j+1])
				{
					matrix[i].push_back(1);
				}
				else
				{
					matrix[i].push_back(0);
				}
			}
			// The elements at the right of the matrix are always 0 (accessing dna1 with j+1 on last element would crash)
			matrix[i].push_back(0);
		}

		// last row is also filled with 0s, because accessing dna2 i+1 would crash
		for (int j(0); j < dna1.length(); j++)
		{
			matrix[dna2.length() - 1].push_back(0);
		}
	}

	return matrix;
}