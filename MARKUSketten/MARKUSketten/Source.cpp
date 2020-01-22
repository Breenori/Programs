#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<time.h>
using namespace std;

vector<char> TEXT;
vector<int> WORD;
int TEXTLENGTH(0);
int WORDCOUNT(0);
int ORDER(3);

void read_file(string const& name);
void populate_text(vector<string> const& filenames);
void populate_word();
void rotate(int const b, int const e);
int strcmp(int index1, int index2, int order);
void sort();
void print_nonsense();
int choose_phrase(int start, int phrase);
int skip_words(int index, int  n);
int word_length(int index);
int binary_search(int phrase);
void print_word(int index);
void print_x_words(int index, int n);
void print_phrase(int index);

void main()
{
	srand((int)time(0));
	vector<string> filenames = { "hp.txt" };
	populate_text(filenames);
	populate_word();
	sort();

	cout << WORDCOUNT << std::endl;
	for (int i(0); i < WORDCOUNT; i++)
	{
		cout << i;
		print_phrase(WORD[i]);
		cout << endl;
	}

	print_nonsense();
}

void read_file(string const& name)
{
	ifstream in(name);

	if (in)
	{
		char last_char(0);
		while (!in.eof())
		{
			char c(tolower(in.get()));

			if (c == ' ' && last_char != ' ')
			{
				TEXT.push_back(c);
				TEXTLENGTH++;
				last_char = c;
			}
			else if (c != ' ' && c != '\\' && c != '\n')
			{
				TEXT.push_back(c);
				TEXTLENGTH++;
				last_char = c;
			}
		}
	}
}
void populate_text(vector<string> const& filenames)
{
	for (int i(0); i < std::size(filenames); i++)
	{
		read_file(filenames[i]);
	}
}
void populate_word()
{
	int offset(0);
	WORD.push_back(0);
	while (WORD[offset] < TEXTLENGTH)
	{
		WORD.push_back(WORD[offset] + word_length(WORD[offset]) + 1);
		WORDCOUNT++;
		offset++;
	}
}
void rotate(int const b, int const e)
{
	int tmp = WORD[e];
	for (int i(e-1); i >= b; i--)
	{
		WORD[i + 1] = WORD[i];
	}
	WORD[b] = tmp;
}
// Returns -1 if the first string is lower
int strcmp(int index1, int index2, int order)
{
	bool equal(false);
	
	while (!equal && TEXT[index1] == TEXT[index2])
	{
		if (TEXT[index1] == ' ')
		{
			order--;
		}
		if (order == 0)
		{
			equal = true;
		}
		index1++;
		index2++;
	}

	return TEXT[index1] - TEXT[index2];
}
void sort()
{
	for (int i(0); i < WORDCOUNT-1; i++)
	{
		int tmp = i;
		for (int j(i + 1); j < WORDCOUNT; j++)
		{
			if (strcmp(WORD[j], WORD[tmp], ORDER) < 0)
			{
				tmp = j;
			}
		}
		rotate(i, tmp);
	}
}

void print_nonsense()
{
	//cout << TEXT << std::endl;
	bool end(false);
	int phrase(0);
	
	print_x_words(0, ORDER - 1);

	while (!end)
	{
		
		int s = binary_search(phrase);
		if (s == 1281)
		{
			cout << "sup";
		}
		int w = choose_phrase(s,phrase);
		int q = skip_words(WORD[w], ORDER-1);
		phrase = skip_words(WORD[w], 1);
		if (word_length(q) == 0)
		{
			end = true;
		}
		else
		{
			print_word(q);
		}
	}
}


// Chooses ONE of the possibilities
int choose_phrase(int const start, int const phrase)
{
	int occurences(1);
	while (start+occurences < WORDCOUNT && strcmp(WORD[start + occurences], phrase, ORDER -1) == 0)
	{
		occurences++;
	}

	int delta(rand() % occurences);

	int val = start + delta;
	return val;
}
int skip_words(int index, int n)
{
	while (n > 0)
	{
		index = index + word_length(index) + 1;
		n--;
	}

	return index;
}
int word_length(int index)
{
	if (index >= TEXTLENGTH)
	{
		return 0;
	}

	int start(index);
	while (TEXT[index] != ' ' && index<TEXTLENGTH-1)
	{
		index++;
	}

	return index-start;
}
int binary_search(int phrase)
{
	int l = 0;
	int r = WORD.size() - 1;

	while (l < r)
	{
		int m = (l + r) / 2;

		if (strcmp(phrase, WORD[m], ORDER - 1) <= 0)
		{
			r = m;
		}
		else
		{
			l = m + 1;
		}
	}

	return (strcmp(phrase, WORD[r], ORDER - 1) == 0) ? r : -1;
}

void print_word(int index)
{
	print_x_words(index, 1);
}
void print_x_words(int index, int n)
{
	while (n > 0 && index < TEXTLENGTH)
	{
		if (TEXT[index] == ' ')
		{
			n--;
		}
		cout << TEXT[index];
		index++;
	}
}

void print_phrase(int index)
{
	print_x_words(index, ORDER);
}

