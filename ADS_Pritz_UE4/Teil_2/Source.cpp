#include<iostream>
#include<string>
using std::cout;
using std::cin;
using std::string;

// Finds the longest matching occurence between two strings and returns it.
string find_longest_match(string string1, string string2);

int main() {
	cout << "Please enter first string: ";
	string string1("");
	std::getline(cin, string1);

	cout << "Please enter second string: ";
	string string2("");
	std::getline(cin, string2);

	
	string match(find_longest_match(string1, string2));
	
	if (string1.length() > 0 && string2.length() > 0)
	{
		if (match.length() > 0)
		{
			cout << "The longest matching occurence is: \n";
			cout << match;
		}
		else
		{
			cout << "No matches found.";
		}
	}
	else
	{
		cout << "One or more strings are empty! 0 matches.";
	}
}

string find_longest_match(string string1, string string2)
{
	// if both strings are empty, we don't have to check for similarities
	if (string1.length() == 0 && string2.length() == 0)
	{
		return "";
	}

	// Check if s2 is longer than s1 and if that's the case: swap them to ensure that s1 is always bigger.
	// This way we can reduce the amount of substrings we have to build (the longer word cant fully be part of the shorter word)
	if (string1.length() < string2.length())
	{
		string tmp = string1;
		string1 = string2;
		string2 = tmp;
	}

	string max_string("");
	string current_substring("");

	for (int i(0); i < string2.length(); i++)
	{
		// assign tmp the first char of string2
		current_substring = string2[i];

		// loop as long as a substring beginning at position i can be found and the end of s2 hasn't been reached.
		while (string1.find(current_substring) != string::npos && (i + current_substring.length()) <= string2.length())
		{
			if (current_substring.length() > max_string.length())
			{
				max_string = current_substring;
			}

			// Add the next char of s2 to tmp, to increase substring length
			current_substring += string2[i + current_substring.length()];
		}
	}

	return max_string;
}
