#include<iostream>
#include<fstream>
#include<string>
using namespace std;

enum mode_type { mt_encrypt, mt_decrypt };

// Returns a text that can be read from console or a file
// Interactive Dialogue.
string get_text();
// Returns the mode_type (en- or decrypt) based on an interactive dialogue
mode_type get_mode();
// Returns the content of a file as a string using the given filename
string read_from_file(string const& filename);
// Returns true if the user changed the ofstream via reference. If false, cout should be used
bool get_output(ofstream& out);
// Returns a fileoutputstream which is created in an interactive dialogue
ofstream get_output_fstream();
// En- or decrypts a given string using the given key and mode
void crypt(mode_type const& mode, string text, string const& key, ostream& out = cout);
// Return true if a file exists, to check if we overwrite something
bool file_exists(string filename);

int main()
{
	string text(get_text());
	cout << endl;

	cout << "Please enter a key: \n";
	string key;
	getline(cin, key);
	cout << endl;
	
	mode_type mode(get_mode());
	cout << endl;

	// Create an outputfilestream.
	// If the following function returns true, it has been changed.
	// otherwise the user chose to print via cout and the ofstream is unchanged.
	ofstream out;
	bool use_file(get_output(out));

	if (use_file)
	{
		if (out)
		{
			crypt(mode, text, key, out);
			out.close();
		}
	}
	else
	{
		out << "Result:\n";
		crypt(mode, text, key);
	}	
}

string get_text()
{
	string ans("");
	cout << "Where do you want to read from:\n";
	cout << "(1) Textfile\n";
	cout << "(2) Console\n";
	getline(cin, ans);
	// In case the user fails entering 1 or 2, ask again
	while (ans != "1" && ans != "2")
	{
		cout << "Please choose one of the options: ";
		getline(cin, ans);
	}

	string text;
	if (ans == "1")
	{
		bool read(false);
		// Let the user repeat the read process if they made a mistake (for example, empty file)
		while (!read)
		{
			string filename;
			cout << "Please enter the filename:\n";
			getline(cin, filename);
			text = read_from_file(filename);
			read = true;

			// en- or decrypting an empty string is useless. Let the user choose again if he/she wants to.
			if (text.empty())
			{
				cout << "File is either empty or file not found.\n";
				cout << "Do you want to change the filename? (y/n)\n";
				getline(cin, ans);
				if (ans == "y" || ans == "Y")
				{
					read = false;
				}
			}
		}

		cout << "The text is:\n" << text << endl;
	}
	else
	{
		// If 2 is entered, simply read from console
		cout << "Please enter your phrase:\n";
		getline(cin, text);
	}
	return text;
}
mode_type get_mode()
{
	string ans;
	cout << "What do you want to do?\n";
	cout << "(1) Encrypt\n";
	cout << "(2) Decrypt\n";
	getline(cin, ans);
	// Again, repeat until the user enters one option.
	while (ans != "1" && ans != "2")
	{
		cout << "Please choose one of the options: ";
		getline(cin, ans);
	}

	if (ans == "1")
	{
		return mt_encrypt;
	}
	else
	{
		return mt_decrypt;
	}
}
string read_from_file(string const& filename)
{
	string text("");
	ifstream in(filename);

	if (in)
	{
		// If the file could be opened, read line by line and add to text
		string line("");
		while (!in.eof())
		{
			getline(in, line);
			text += line;
		}
	}

	return text;
}
bool get_output(ofstream& out)
{
	string ans;
	cout << "Where do you want to write?\n";
	cout << "(1) Textfile\n";
	cout << "(2) Console\n";
	getline(cin, ans);

	while (ans != "1" && ans != "2")
	{
		cout << "Please choose one of the options: ";
		getline(cin, ans);
	}
	cout << endl;

	if (ans == "1")
	{
		out = get_output_fstream();
		return true;
	}
	else
	{
		return false;
	}
}
ofstream get_output_fstream()
{
	ofstream out;
	string out_name;
	bool file_ok(false);
	// If the user picked a file they dont want to overwrite, let them choose again.
	while (!file_ok)
	{
		cout << "Please enter the output filename:\n";
		getline(cin, out_name);
		file_ok = true;
		if (file_exists(out_name))
		{
			// Print warning and let them choose
			file_ok = false;
			cout << "Caution! This will overwrite an existing file!\n";
			cout << "Do you really want to continue? (y/n)\n";
			string ans("");
			getline(cin, ans);
			if (ans == "y" || ans == "Y")
			{
				file_ok = true;
			}
		}
	}
	out.open(out_name);

	return out;
}
void crypt(mode_type const& mode, string text, string const& key, ostream& out)
{
	for (int i(0); i < text.length(); i++)
	{
		// depending on the mode, we either en- or decrypt
		if (mode == mt_encrypt)
		{
			// I wanted to start encryption offset with A as one, which is why i substract A and add 1.
			// To make it more similiar to other encryption techniques
			text[i] += key[i % key.length()] - 'A' + 1;
		}
		else
		{
			text[i] -= key[i % key.length()] - 'A' + 1;
		}
	}
	out << text;
}
bool file_exists(string filename)
{
	// If the file could be opened, set bool and return it.
	fstream file(filename);
	bool exists(file.good());
	file.close();
	return exists;
}
