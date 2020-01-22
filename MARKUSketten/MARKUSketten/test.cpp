/*#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <random>
#include <time.h>


char read_letter(std::string const& file_name, int const& char_amount, std::ifstream& input);
void print_vector(std::vector<char> const& vector);
void empty_text();
void insert_letter(char const& symbol, int& selected_field);
int check_text_length(std::string const& file_name);
int wort_laenge(int const begin);
void zerteile_text_in_woerter();
int anzahl_woerter();
int vergleiche_phrasen(int b0, int b1, int n);
void sortiere_phrasen();
void drucke_x_woerter(int start, int amount);
void drucke_phrase(int begin);
void drucke_wort(int begin);
void drucke_nonsense();
int suche_erste_phrase(int left_side, int right_side, int const phrase);
void rotate(int i, int j);
void drucke_tabelle();
int waehle_phrase(int start);
int ueberspringe_woerter(int const start, int const amount);

// global variables
std::string FILE_NAME("hp_short2.txt");
int ORDNUNG(3);
size_t TEXTLAENGE(10000);
std::vector<char> TEXT(check_text_length(FILE_NAME) + ORDNUNG);
std::vector<int> WORT(1);
size_t WORTANZAHL;


void main() {
	srand(time(0));
	std::ifstream input;
	std::string file_name(FILE_NAME);
	input.open(file_name);
	//empty_text();
	int selected_field(0);
	char symbol;
	for (int i(0); i < TEXTLAENGE; ++i) {
		symbol = read_letter(file_name, TEXTLAENGE, input);
		insert_letter(symbol, selected_field);
	}
	zerteile_text_in_woerter();
	sortiere_phrasen();
	input.close();
	std::cout << std::endl;
	drucke_tabelle();
	std::cout << std::endl << "Wortanzahl: " << WORTANZAHL << std::endl;
	std::cout << "\nHier beginnt der Text: \n";
	drucke_nonsense();
	std::cout << "\nProgramm beendet.";
}

char read_letter(std::string const& file_name, int const& char_amount, std::ifstream& input) {
	int text_length(0);
	char next_symbol;
	if (input.good() && text_length < char_amount) {
		next_symbol = input.get();
		text_length += 1;
	}
	if (input.eof()) {
		return '\0';
	}
	/*else if (std::isspace(next_symbol)) { // function returns 'true' if TAB etc. is detected
		return ' ';
	}
	else {
		return next_symbol;
	}
}
void print_vector(std::vector<char> const& vector) {
	std::cout << "<";
	for (size_t i(0); i < vector.size(); ++i) {
		std::cout << vector[i];
		if (i < vector.size() - 1) {
			std::cout << ",";
		}
	}
	std::cout << ">";
}
void empty_text() {
	WORTANZAHL = 0;
}
void insert_letter(char const& symbol, int& selected_field) {
	if (symbol != '\0' && selected_field < TEXT.size()) {
		TEXT[selected_field] = symbol;
		selected_field += 1;
	}
}
int check_text_length(std::string const& file_name) {
	std::ifstream check_input;
	check_input.open(file_name);
	int characters_in_file(0);
	bool found_end(false);
	while (found_end == false) {
		check_input.get();
		if (check_input.eof()) {
			found_end = true;
		}
		else {
			characters_in_file += 1;
		}
	}
	check_input.close();
	if (TEXTLAENGE > characters_in_file) {
		TEXTLAENGE = characters_in_file;
	}
	return TEXTLAENGE;
}
int wort_laenge(int const begin) {
	int end(begin);
	if (TEXT.size() <= end) {
		return 0;
	}
	while (TEXT[end] != ' ') {
		end += 1;
	}
	return end - begin;
}
void zerteile_text_in_woerter() {
	int i(0);
	WORT[i] = 0;
	TEXT.push_back(' ');
	while (WORT[i] < TEXTLAENGE) {
		WORT.push_back(WORT[i] + wort_laenge(WORT[i]) + 1); // push_back is used; already discussed
		i += 1;
	}
	WORTANZAHL = i;
}
int anzahl_woerter() {
	int woerter(0);
	std::ifstream input_woerter;
	input_woerter.open(FILE_NAME);
	for (size_t i(0); i < TEXT.size(); ++i) {
		if (TEXT[i] == ' ' && TEXT[i - 1] != ' ' && i != 0) {
			woerter += 1;
		}
	}
	std::cout << woerter;
	input_woerter.close();
	return woerter;
}
int vergleiche_phrasen(int b0, int b1, int n) {
	bool gleich(false);
	while (!gleich && TEXT[b0] == TEXT[b1]) {
		if (TEXT[b0] == ' ' || TEXT[b0] == '\0') {
			n = n - 1;
			if (n == 0) {
				gleich = true;
				return 0;
				b0 -= 1;
				b1 -= 1;
			}
		}
		b0 += 1;
		b1 += 1;
	}
	return TEXT[b0] - TEXT[b1];
}
void sortiere_phrasen() {
	for (int i(0); i < WORTANZAHL - 2; ++i) {
		int j(i);
		for (int k(i + 1); k < WORTANZAHL - 1; ++k) {
			if (vergleiche_phrasen(WORT[k], WORT[j], ORDNUNG) < 0) {
				j = k;
			}
		}
		rotate(i, j);
	}
}
void drucke_x_woerter(int start, int amount) {
	while (amount != 0) {
		std::cout << TEXT[start];
		if (TEXT[start] == ' ' || TEXT[start] == '\0') {
			amount -= 1;
		}
		start += 1;
	}
}
void drucke_phrase(int begin) {
	drucke_x_woerter(begin, ORDNUNG);
}
void drucke_wort(int begin) {
	drucke_x_woerter(begin, 1);
}
void drucke_nonsense() {
	bool ende(false);
	int phrase(0);
	int start;
	int wahl;
	int folgewort;
	drucke_phrase(phrase);
	while (!ende) {
		start = suche_erste_phrase(0, WORTANZAHL, phrase); // start somehow returns -1 sometimes (I guess when entry is in the last half of text)
		wahl = waehle_phrase(start);
		folgewort = ueberspringe_woerter(WORT[wahl], ORDNUNG-1);
		phrase = ueberspringe_woerter(WORT[wahl], 1);
		if (wort_laenge(folgewort) == 0) {
			ende = true;
		}
		else {
			drucke_wort(folgewort);
		}

	}
}

int suche_erste_phrase(int left_side, int right_side, int const phrase) {
	int left(left_side);
	int right(right_side);
	while (left < right) {
		int mid((left + right) / 2);
		if (vergleiche_phrasen(phrase, WORT[mid], ORDNUNG-1) <= 0) {
			right = mid;
		}
		else {
			left = mid + 1;
		}
	}
	//return WORT[right] == phrase ? right : -1;
	return vergleiche_phrasen(WORT[right], phrase, ORDNUNG-1) == 0 ? right : -1;
}


void drucke_tabelle() {
	for (int i(0); i < WORT.size() - 1; ++i) {
		std::cout << i << " ";
		int start(WORT[i]);
		drucke_x_woerter(start, ORDNUNG);
		std::cout << std::endl;
	}
}

int waehle_phrase(int start) {
	bool equal(true);
	int last_equal(start);
	while (equal) {
		if (vergleiche_phrasen(WORT[start], WORT[last_equal], ORDNUNG-1) == 0) {
			last_equal += 1;
		}
		else {
			equal = false;
		}
	}
	int amount_equal(last_equal - start); // should never be 0 because last_equal is always at least 1 higher than start
	return (rand() % amount_equal) + start;
}

int ueberspringe_woerter(int const start, int const amount) {
	int new_position(start);
	for (int i(0); i < amount; ++i) {
		new_position += wort_laenge(new_position) + 1;
	}
	return new_position;
}

void rotate(int i, int j) {
	if (i > j) { // limits are passed wrong
		std::swap(i, j); // swaps limits to prevent an error
	}
	int temp(WORT[j]);
	for (int start(j - 1); start >= i; --start) {
		WORT[start + 1] = WORT[start];
	}
	WORT[i] = temp;
}*/