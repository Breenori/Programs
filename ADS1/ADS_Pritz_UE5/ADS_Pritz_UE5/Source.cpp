#include<iostream>
#include<string>
#include<vector>
#include<fstream>
using std::string;
using std::cout;
using std::cin;

// create a new datatype to store related rna_triplets and abbreviations of aminoacids
struct aminoacid_type {
	string rna_triplet;
	char letter;
};

// Checks if a single char is A,G,C or T.
bool is_valid_DNA_char(char const nucleotid);
// Reads a valid DNA string from the console and returns it.
string read_DNA();
// takes a dna string and returns the transcribed string by replacing T with U
string transcribe(string const& dna);
// takes a rna string and returns a string of aminoacid abbreviations
string translate(string const& rna);
// combinations of rna_triplets and their correspondent aminoacids is stored in a csv file.
// -> reads the file and fills a vector of aminoacid_types which is needed later
// returns true if the file could be read and false if there was an error reading the file
bool prepare_translation(string const& filename, std::vector<aminoacid_type> &aminoacids);
// returns an array of elements of a string that are separated by the delmiter
std::vector<string> split_string(string const& str, char const delimiter);

void main()
{
	string dna(read_DNA());

	if (!dna.empty())
	{
		string rna(transcribe(dna));

		cout << std::endl << "RNA:" << std::endl;
		cout << rna << std::endl << std::endl;

		if (rna.length() >= 3)
		{
			string aminoacid_chain(translate(rna));

			if (!aminoacid_chain.empty())
			{
				cout << "Aminoacid-String:" << std::endl;
				cout << aminoacid_chain;
			}
			else {
				cout << "No start codon has been found.";
			}
		}
		else
		{
			cout << "RNA has less than 3 characters. Terminating.";
		}
	}
	else
	{
		cout << "Empty string detected. Terminating.";
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
string transcribe(string const& dna)
{
	string tmp = dna;

	for (int i(0); i < tmp.length(); i++)
	{
		if (tmp[i] == 'T')
		{
			tmp[i] = 'U';
		}
	}

	return tmp;
}
string translate(string const& rna)
{
	if (rna.find("AUG", 0) != string::npos)
	{
		std::vector<aminoacid_type> aminoacids;
		prepare_translation("pairs.csv", aminoacids);

		//Search for the start codon and save its starting position
		int offset(rna.find("AUG", 0));
		string translated_rna = "";
		bool stop_found = false;


		int i(offset);
		// Loop as long as the string still has 3 characters left 
		// AND no stop codon has been found
		while (i < rna.length() - 2 && !stop_found)
		{
			// loop through the aminoacid_type vector, search for triplet and add the corresponding letter to the translation string
			for (int j(0); j < std::size(aminoacids); j++)
			{
				if (aminoacids[j].rna_triplet == rna.substr(i, 3))
				{
					// X is not used by any aminoacid and has therefor been used to mark a stop codon in the CSV-File
					if (aminoacids[j].letter != 'X')
					{
						translated_rna += aminoacids[j].letter;
					}
					else
					{
						stop_found = true;
					}
				}
			}
			i = i + 3;
		}

		return translated_rna;
	}
	else
	{
		return "";
	}
}
bool prepare_translation(string const& filename, std::vector<aminoacid_type> &aminoacids)
{
	std::ifstream in(filename);

	//check if file could be opened with the ifstream
	if (in)
	{
		//read all lines and build aminoacid_types from them
		while (!in.eof())
		{
			std::string s;
			getline(in, s);
			std::vector<string> pair = split_string(s, ',');
			aminoacid_type aminoacid;
			aminoacid.rna_triplet = pair[0];
			aminoacid.letter = pair[1][0];
			aminoacids.push_back(aminoacid);
		}

		in.close();

		//file could be read, so we return true
		return true;
	}
	else
	{
		//file couldn't be read, so we return false
		return false;
	}
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