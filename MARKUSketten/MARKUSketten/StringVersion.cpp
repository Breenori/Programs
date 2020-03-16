/*#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<time.h>
using namespace std;

string TEXT("");
vector<int> WORD;
int TEXTLENGTH(0);
int WORDCOUNT(0);
int ORDER(3);

void read_file(string const& name);
void preprocess();
void populate_text(vector<string> const& filenames);
void populate_word();
void rotate(int const b, int const e);
int strcmp(string const& str1, string const& str2);
void sort();
void print_nonsense();
int search_first_phrase(int const phrase);
int choose_phrase(int const start, int const phrase);
int skip_words(int const index, int const n);
int word_length(int index);
int binary_search(int phrase);

string get_phrase(int const index, int const& n)
{
	int found(0);
	int offset(index);

	while ((TEXT.find(" ", offset) != string::npos) && (found < n))
	{
		found++;
		offset = TEXT.find(" ", offset) + 1;
	}

	if (found == n)
	{
		return TEXT.substr(index, offset - index);
	}
	else
	{
		return TEXT.substr(index, TEXT.length() - index);
	}
}

void main()
{
	srand((int)time(0));
	vector<string> filenames = { "hp_short.txt" };
	populate_text(filenames);
	preprocess();
	populate_word();
	sort();

	cout << WORD.size() << std::endl;
	for (int i(0); i < std::size(WORD); i++)
	{
		cout << i + 1;
		cout << get_phrase(WORD[i], ORDER) << std::endl;
	}

	print_nonsense();
}

void read_file(string const& name)
{
	ifstream in(name);

	if (in)
	{
		while (!in.eof())
		{
			string line("");
			getline(in, line);
			if (!line.empty())
			{
				TEXT += line;
				TEXT += " ";
			}
		}
	}
}
void preprocess()
{
	for (int i(0); i < TEXT.length(); i++)
	{
		if (TEXT[i] >= 'A' && TEXT[i] <= 'Z')
		{
			TEXT[i] = tolower(TEXT[i]);
		}
		if (i + 1 < TEXT.length())
		{
			while (TEXT[i] == ' ' && TEXT[i + 1] == ' ')
			{
				TEXT.erase(i + 1, 1);
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
	if (TEXT[0] >= 'a' && TEXT[0] <= 'z')
	{
		WORD.push_back(0);
		WORDCOUNT++;
		offset++;
	}
	while (TEXT.find(" ", offset) != string::npos)
	{
		if (TEXT[TEXT.find(" ", offset) + 1] != ' ')
		{
			WORD.push_back(TEXT.find(" ", offset) + 1);
			WORDCOUNT++;
		}

		offset = TEXT.find(" ", offset) + 1;
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
}
// Returns -1 if the first string is lower
int strcmp(string const& str1, string const& str2)
{
	int state = 0;
	int count(0);

	while (state == 0 && count < str1.length())
	{
		if (str1[count] > str2[count])
		{
			state = 1;
		}
		else if (str1[count] < str2[count])
		{
			state = -1;
		}
		count++;
	}

	return state;
}
void sort()
{
	for (int i(0); i < std::size(WORD) - 1; i++)
	{
		int tmp = i;
		for (int j(i + 1); j < std::size(WORD); j++)
		{
			string word1(get_phrase(WORD[j], ORDER));
			string word2(get_phrase(WORD[tmp], ORDER));

			if (strcmp(word1, word2) == -1)
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
	string text("");
	text += get_phrase(0, ORDER - 1);

	while (!end)
	{
		//int s = search_first_phrase(phrase);
		int s = binary_search(phrase);
		//int test = binary_search(phrase);
		if (s < 0)
		{
			cout << get_phrase(WORD[phrase], ORDER);
		}
		string asd = get_phrase(WORD[s], ORDER);
		int w = choose_phrase(s, phrase);
		asd = get_phrase(WORD[w], ORDER);
		int q = skip_words(WORD[w], ORDER - 1);
		asd = get_phrase(q, 1);
		phrase = skip_words(WORD[w], 1);
		if (word_length(q) == 0)
		{
			end = true;
		}
		else
		{
			text += get_phrase(q, 1);
		}
	}

	cout << text;

}

// Searches the first occurence
int search_first_phrase(int const phrase)
{
	bool found(false);

	int counter(0);
	while (counter < WORDCOUNT && !found)
	{
		if (get_phrase(WORD[counter], ORDER - 1) == get_phrase(phrase, ORDER - 1))
		{
			found = true;
		}
		counter++;
	}

	return counter - 1;
}
// Chooses ONE of the possibilities
int choose_phrase(int const start, int const phrase)
{
	int occurences(1);
	while (get_phrase(WORD[start + occurences], ORDER - 1) == get_phrase(phrase, ORDER - 1))
	{
		string asd(get_phrase(WORD[start + occurences], ORDER));
		occurences++;
	}

	int delta(rand() % occurences);

	int val = start + delta;
	return val;
}
int skip_words(int const index, int const n)
{
	int offset(index);
	string asd = get_phrase(index, 1);
	int found(0);
	while (TEXT.find(" ", offset) != string::npos && offset < TEXT.length() && found < n)
	{
		offset = TEXT.find(" ", offset) + 1;
		asd = get_phrase(offset, 1);
		found++;
	}

	if (found == n)
	{
		return offset;
	}
	else
	{
		return TEXT.length() - 1;
	}
}

int word_length(int index)
{
	if (index >= TEXT.length())
	{
		return 0;
	}

	int length(1);
	int start(index);

	while (TEXT[start + length] != ' ')
	{
		length++;
	}

	return length;
}

int binary_search(int phrase)
{
	int l = 0;
	int r = WORD.size() - 1;

	while (l < r)
	{
		int m = (l + r) / 2;

		if (strcmp(get_phrase(phrase, ORDER - 1), get_phrase(WORD[m], ORDER - 1)) <= 0)
		{
			r = m;
		}
		else
		{
			l = m + 1;
		}
	}

	return (strcmp(get_phrase(phrase, ORDER - 1), get_phrase(WORD[r], ORDER - 1)) == 0) ? r : -1;
}
*/
