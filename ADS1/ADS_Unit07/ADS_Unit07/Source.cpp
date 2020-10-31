#include<iostream>
#include<string>

void print_substring(std::string const& s, int a, int b);
void print_all_substrings(std::string const& s);

bool is_palindrom(std::string const& s);

int main()
{
	std::string str("hagenberg");
	print_all_substrings(str);

	std::string p;
	std::cout << "Please enter a word: ";
	std::cin >> p;
	std::string sub = p;
	for (int i(0); i < p.length(); i++)
	{
		sub[i] = std::tolower(p[i]);
	}
	std::cout << std::endl << is_palindrom(sub);
}

void print_all_substrings(std::string const&s)
{
	int wordlength = 0;

	for (int wordlength(0); wordlength <= s.length(); wordlength++)
	{
		for (int i(0); i < s.length() - wordlength; i++)
		{
			print_substring(s, i, i + wordlength);
			std::cout << " ";
		}
		std::cout << std::endl;
	}
}
void print_substring(std::string const& s,int a, int b)
{
	if (a > b)
	{
		a = a + b;
		b = a - b;
		a = a - b;
	}
	if (a < 0)
	{
		a = 0;
	}
	if (b >= s.size())
	{
		b = s.size() - 1;
	}

	for (int i(a); i <= b; i++)
	{
		std::cout << s[i];
	}
}

bool is_palindrom(std::string const &s)
{
	for (int i(0); i < s.length() / 2; i++)
	{
		if (s[i] != s[s.length() - 1 - i])
			return false;
	}
	return true;
}