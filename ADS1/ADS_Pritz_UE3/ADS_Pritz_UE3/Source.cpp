#include<iostream>
#include<string>
using std::string;
using std::cin;
using std::cout;

string translate(string s, string to_be_translated);

void main()
{
	string s("");
	cout << "Bitte geben Sie einen deutschen Satz ein: ";
	cout << std::endl;
	std::getline(cin, s);
	cout << std::endl << "Dieser Satz lautet auf tirolerisch: " << std::endl;

	s = translate(s, "st");
	s = translate(s, "sT");
	s = translate(s, "St");
	s = translate(s, "ST");

	cout << s;
}

string translate(string s, string to_be_translated)
{
	int pos(-1);

	while (s.find(to_be_translated, pos + 1) != string::npos)
	{
		pos = s.find(to_be_translated, pos + 1);
		if (s.length() <= pos + 2 || s[pos + 2] == '.' || s[pos + 2] == '?' || s[pos + 2] == '!' || s[pos + 2] == ' ')
		{
			if (to_be_translated == "st")
			{
				s.replace(pos, 2, "sch");
			}
			else if (to_be_translated == "sT")
			{
				s.replace(pos, 2, "sch");
			}
			else if (to_be_translated == "St")
			{
				s.replace(pos, 2, "SCH");
			}
			else if (to_be_translated == "ST")
			{
				s.replace(pos, 2, "SCH");
			}
		}
		else
		{
			if (to_be_translated == "st")
			{
				s.replace(pos, 2, "scht");
			}
			else if (to_be_translated == "sT")
			{
				s.replace(pos, 2, "schT");
			}
			else if (to_be_translated == "St")
			{
				s.replace(pos, 2, "SCHt");
			}
			else if (to_be_translated == "ST")
			{
				s.replace(pos, 2, "SCHT");
			}
		}
	}

	return s;
}