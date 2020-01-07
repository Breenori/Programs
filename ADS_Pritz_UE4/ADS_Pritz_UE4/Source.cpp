#include<iostream>
#include<string>
using std::cout;
using std::cin;
using std::string;

// Reads a valid DNA string from the console and returns it.
string read_DNA();
// Checks if a single char is A,G,C or T.
bool is_valid_DNA_char(char const nucleotid);
// This function checks every letter of the DNA-String and replaces it with its complementary counterpart and returns the whole string afterwards.
string complementary_dna(string str);

int main() {
	cout << "Please enter a DNA-Sequence: ";
	string dna(read_DNA());

	// Note: ' has been used instead of ´ because console isn't properly displaying the latter.
	if (dna.length() > 0)
	{
		cout << "5' " << dna << " 3'\n";
		cout << "3' " << complementary_dna(dna) << " 5'";
	}
	else
	{
		cout << "No data has been entered. Terminating.";
	}
}

string read_DNA()
{
	bool input_required(true);
	string dna;

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
string complementary_dna(string dna)
{
	for (int i(0); i < dna.length(); i++)
	{
		if (std::toupper(dna[i]) == 'A')
		{
			dna[i] = 'T';
		}
		else if (std::toupper(dna[i]) == 'T')
		{
			dna[i] = 'A';
		}
		else if (std::toupper(dna[i]) == 'G')
		{
			dna[i] = 'C';
		}
		else if (std::toupper(dna[i]) == 'C')
		{
			dna[i] = 'G';
		}
	}

	return dna;
}