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
// Returns a fileoutputstream which is created in an interactive dialogue
ofstream get_output();
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

	string ans;
	cout << "Where do you want to write?\n";
	cout << "(1) Textfile\n";
	cout << "(2) Console\n";
	getline(cin, ans);

	while (ans != "1" && ans != "2")
	{
		getline(cin, ans);
	}

	if (ans == "1")
	{
		ofstream out(get_output());
		crypt(mode, text, key, out);
		out.close();
	}
	else
	{
		crypt(mode, text, key);
	}
}

string get_text()
{
	string ans("");
	cout << "Where do you want to read from:\n";
	cout << "(1) Textfile\n";
	cout << "(2) Console\n";
	while (ans != "1" && ans != "2")
	{
		getline(cin, ans);
	}

	string text;
	if (ans == "1")
	{
		bool read(false);
		while (!read)
		{
			string filename;
			cout << "Please enter the filename:";
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

		cout << "The text is:\n" << text << endl << endl;
	}
	else
	{
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
	while (ans != "1" && ans != "2")
	{
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
	ifstream ifs(filename);

	if (ifs)
	{
		string line("");
		while (!ifs.eof())
		{
			getline(ifs, line);
			text += line;
		}
	}

	return text;
}
ofstream get_output()
{
	string out_name;
	cout << "Please enter the output filename:\n";
	getline(cin, out_name);
	if (file_exists(out_name))
	{
		cout << "Caution! This will overwrite an existing file!\n";
	}
	ofstream out(out_name);

	return out;
}
void crypt(mode_type const& mode, string text, string const& key, ostream& out)
{
	for (int i(0); i < text.length(); i++)
	{
		if (mode == mt_encrypt)
		{
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
	fstream file(filename);
	bool exists(file.good());
	file.close();
	return exists;
}