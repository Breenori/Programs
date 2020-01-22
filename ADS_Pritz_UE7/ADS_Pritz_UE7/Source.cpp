#include<iostream>
#include<string>
#include<fstream>
using namespace std;


string encrypt(string phrase, string const& key);
string decrypt(string phrase, string const& key);

void main()
{

	string ans("");
	cout << "What do you want to do?\n";
	cout << "(1) Encrypt\n";
	cout << "(2) Decrypt\n";
	getline(cin, ans);

	cout << "Please enter the filename: ";
	string phrase("");
	getline(cin, phrase);

	cout << "Please enter a key: ";
	string key("");
	getline(cin, key);

	if (ans == "1" || ans == "(1)" || ans == "Encrypt" || ans == "encrypt")
	{
		string encrypted(encrypt(phrase, key));
		cout << encrypted << endl;
	}
	
	if (ans == "2" || ans == "(2)" || ans == "Decrypt" || ans == "decrypt")
	{
		string decrypted(decrypt(phrase, key));
		cout << decrypted << endl;
	}
}

string encrypt(string phrase, string const& key)
{
	for (int i(0); i < phrase.length(); i++)
	{
		phrase[i] += key[i % key.length()] - 'A' + 1;
	}
	return phrase;
}
string decrypt(string phrase, string const& key)
{
	for (int i(0); i < phrase.length(); i++)
	{
		phrase[i] -= key[i % key.length()] - 'A' + 1;
	}
	return phrase;
}