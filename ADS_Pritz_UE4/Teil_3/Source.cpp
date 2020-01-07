#include<iostream>
#include<string>
using std::cout;
using std::cin;
using std::string;

// Reads a valid DNA string from the console and returns it.
string read_DNA();
// Checks if a single char is A,G,C or T.
bool is_valid_DNA_char(char const nucleotid);
// Returns if two chars are complementary (e.g. G and C = true)
bool is_complementary(char const nucleotid1, char const nucleotid2);
// Returns the length of the palindrome (palindrome = dna sequence in the beginning has a complementary DNA-sequence at the end.) 
int palindrome_length(string const& dna);

int main() {
	cout << "Please enter a DNA-Sequence: ";
	string dna_string(read_DNA());

	int pali_length = palindrome_length(dna_string);
	if (pali_length == 0)
	{
		cout << "No palindrome found.";
	}
	else
	{
		cout << "Palindrome with a length of " << pali_length << " has been found.";
	}
}

bool is_complementary(char const nucleotid1, char const nucleotid2)
{
		if (std::toupper(nucleotid1) == 'A' && std::toupper(nucleotid2) == 'T')
		{
			return true;
		}
		else if (std::toupper(nucleotid1) == 'T' && std::toupper(nucleotid2) == 'A')
		{
			return true;
		}
		else if (std::toupper(nucleotid1) == 'G' && std::toupper(nucleotid2) == 'C')
		{
			return true;
		}
		else if (std::toupper(nucleotid1) == 'C' && std::toupper(nucleotid2) == 'G')
		{
			return true;
		}
		else 
		{
			return false;
		}
}
int palindrome_length(string const& dna)
{
	if (dna.length() == 0)
	{
		return 0;
	}

	// loop and check if char at 'counter' and char at the mirrored position are complementary. (first and last, 2nd and 2nd-last, ...)
	// stop when half of the string has been searched or chars aren't complementary
	int counter(0);
	while (is_complementary(dna[counter], dna[dna.length() - 1 - counter]) && counter < dna.length()/2)
	{
		counter++;
	}

	return counter;
}
string read_DNA()
{
	bool input_required(true);
	string dna;

	// Read user input and check for validity of the string (only C,G,A,T as chars).
	while (input_required)
	{
		std::getline(cin, dna);

		// Counts the amount of valid chars. If an invalid char is found, step out of the loop and repeat.
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