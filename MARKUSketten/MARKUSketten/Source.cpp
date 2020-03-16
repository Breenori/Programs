#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<time.h>
#include<iomanip>
using namespace std;

vector<char> TEXT;
vector<int> WORD;
int TEXTLENGTH(0);
int WORDCOUNT(0);
int ORDER(3);

void read_file(string const& name);
void read_text(vector<string> const& filenames);
void split_text_in_words();

int strcmp(int index1, int index2, int order);
/*
void sort();
void rotate(int const b, int const e);
*/
void print_nonsense();
int choose_phrase(int start, int phrase);
int skip_words(int index, int  n);
int word_length(int index);
int binary_search(int phrase);
void print_word(int index);
void print_x_words(int index, int n, ostream& out = cout);
void print_phrase(int index, ostream& out = cout);
void quicksort(int low, int high);
int partition(int low, int high);
void print_summary();

void main()
{
	srand((int)time(0));
	vector<string> filenames = { "hp_short.txt"};
	read_text(filenames);
	split_text_in_words();
	quicksort(0, WORDCOUNT-1);

	print_summary();
	
	print_nonsense();
}

void print_summary()
{
	cout << WORDCOUNT << std::endl;
	for (int i(0); i < WORDCOUNT; i++)
	{
		cout << fixed << setw(5) << i << ": ";
		print_phrase(WORD[i]);
		cout << endl;
	}
	cout << endl;
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
			if (c == '\n')
			{
				c = ' ';
			}

			if (c == ' ' && last_char != ' ')
			{
				TEXT.push_back(c);
				TEXTLENGTH++;
				last_char = c;
			}
			else if (c != ' ' && c != '\\')
			{
				TEXT.push_back(c);
				TEXTLENGTH++;
				last_char = c;
			}
		}
		if (last_char != ' ')
		{
			TEXT.push_back(' ');
			TEXTLENGTH++;
		}
	}
}
void read_text(vector<string> const& filenames)
{
	for (int i(0); i < std::size(filenames); i++)
	{
		read_file(filenames[i]);
	}
}
void split_text_in_words()
{
	int offset(0);
	WORD.push_back(0);
	WORDCOUNT++;
	while (WORD[offset] < TEXTLENGTH)
	{
		WORD.push_back(WORD[offset] + word_length(WORD[offset]) + 1);
		WORDCOUNT++;
		offset++;
	}
	TEXT.push_back('\0');
}
int strcmp(int index1, int index2, int order)
{
	bool equal(false);
	
	while (!equal && TEXT[index1] == TEXT[index2])
	{
		if (TEXT[index1] == ' ')
		{
			order--;
			if (order == 0)
			{
				equal = true;
			}
		}
		index1++;
		index2++;
	}

	return TEXT[index1] - TEXT[index2];
}
/*
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
void rotate(int const b, int const e)
{
	int tmp = WORD[e];
	for (int i(e - 1); i >= b; i--)
	{
		WORD[i + 1] = WORD[i];
	}
	WORD[b] = tmp;
}*/
void quicksort(int low, int high)
{
	if (low < high)
	{
		int pi = partition(low, high);
		quicksort(low, pi - 1);
		quicksort(pi + 1, high);
	}
}
int partition(int low, int high)
{
	int pivot(WORD[high]);
	int i(low - 1);

	for (int j(low); j <= high - 1; j++)
	{
		if (strcmp(WORD[j], pivot, ORDER) < 0)
		{
			i++;
			swap(WORD[i], WORD[j]);
		}
	}
	swap(WORD[i + 1], WORD[high]);
	return i + 1;
}
void print_nonsense()
{
	bool end(false);
	int phrase(0);
	
	cout << "Here comes the text:\n";
	print_x_words(0, ORDER);

	while (!end)
	{
		int s = binary_search(phrase);
		int w = choose_phrase(s,phrase);
		int q = skip_words(WORD[w], ORDER);
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
int choose_phrase(int const start, int const phrase)
{
	int occurences(1);
	while (start+occurences < WORDCOUNT && strcmp(WORD[start + occurences], phrase, ORDER) == 0)
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

		if (strcmp(phrase, WORD[m], ORDER) <= 0)
		{
			r = m;
		}
		else
		{
			l = m + 1;
		}
	}

	return (strcmp(phrase, WORD[r], ORDER) == 0) ? r : -1;
}
void print_word(int index)
{
	print_x_words(index, 1);
}
void print_x_words(int index, int n, ostream& out)
{
	while (n > 0 && index < TEXTLENGTH)
	{
		if (TEXT[index] == ' ')
		{
			n--;
		}
		out << TEXT[index];
		index++;
	}
}
void print_phrase(int index, ostream& out)
{
	print_x_words(index, ORDER, out);
}

