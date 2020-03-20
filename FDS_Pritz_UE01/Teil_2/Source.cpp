#include<iostream>
#include<string>
#include<fstream>
#include<stdlib.h>
#include<cassert>
using std::cout;
using std::cin;
using std::string;
using std::endl;
using std::ifstream;
using std::getline;

struct row_node_t {
	size_t data;
	row_node_t* next;
};

struct move_t {
	size_t row;
	size_t amount;
};


// Returns a number entered by the user. Displays the given message for input information.
int get_number();
// Creates a linked list based on an input file
void initialize(row_node_t* & head, string const& filename = "game.txt");
// Appends a value to the end of the linked list
void append(row_node_t* & head, size_t const value);
// Returns the length of the linked list
size_t get_size(row_node_t* const& head);
// Getter and Setter for an element in the linked list at the specified index.
size_t& element_at(row_node_t* const & head, size_t const index);
// Removes elements with data = 0 (zero stones left) from the linked list.
void remove_empty_rows(row_node_t* & head);
// Prints all the elements in the given linked list
void print_all(row_node_t* const& head);
// Prints the current gamestate
void print_gamestate(row_node_t* const& head, move_t const& last_move);
// Returns the amount of lines
size_t get_min_rows(row_node_t* const& head);
// Let the user decide and make a move
move_t player_move(row_node_t* & head);
// CPU move
move_t make_move(row_node_t*& head);
// Start the game and play
size_t play_game(row_node_t*& rows);

void main()
{
	row_node_t* rows(nullptr);
	initialize(rows);

	play_game(rows);
}

int get_number()
{
	int num(0);
	cin >> num;
	// As long as input for int failed, repeat read
	while (cin.fail())
	{
		cout << "Invalid value. Please enter a number.\n";
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cin >> num;
	}
	// In case something is entered after int. ex "10a". Isn't counted as cin.fail().
	cin.clear();
	cin.ignore(INT_MAX, '\n');

	return num;
}
void initialize(row_node_t* & head, string const& filename)
{
	ifstream in(filename);

	size_t val(0);
	string line("");
	while (getline(in, line))
	{
		val = std::stoi(line);
		append(head, val);
	}

	in.close();
}
void append(row_node_t* & head, size_t const value)
{
	if (value >= 1 && value <= 30)
	{
		row_node_t* new_node = new row_node_t;
		new_node->data = value;
		new_node->next = nullptr;

		if (head == nullptr)
		{
			head = new_node;
		}
		else
		{
			row_node_t* last = head;
			while (last->next != nullptr)
			{
				last = last->next;
			}
			last->next = new_node;
		}
	}
}
size_t get_size(row_node_t* const& head)
{
	row_node_t* head_ref = head;
	size_t counter(0);

	while (head_ref != nullptr)
	{
		head_ref = head_ref->next;
		counter++;
	}

	return counter;
}
size_t& element_at(row_node_t* const & head, size_t const index)
{
	assert(head != nullptr);
	assert(index < get_size(head));

	row_node_t* head_ref = head;

	for (int i(0); i < index; i++)
	{
		head_ref = head_ref->next;
	}

	return head_ref->data;
}
void remove_empty_rows(row_node_t* & head)
{
	// In case the first row is null, dont look into head->next, but head directly. (root node!)
	if (head != nullptr)
	{
		if (head->data == 0)
		{
			if (head->next == nullptr)
			{
				delete head;
				head = nullptr;
			}
			else
			{
				row_node_t* tmp = head->next;
				delete head;
				head = tmp;
			}
		}
	}

	row_node_t* head_ref = head;

	while (head_ref != nullptr)
	{
		if (head_ref->next != nullptr)
		{
			// If the successor is zero
			if (head_ref->next->data == 0)
			{
				row_node_t* tmp = head_ref->next->next;
				delete head_ref->next;
				head_ref->next = tmp;
			}
		}
		head_ref = head_ref->next;
	}
}
void print_all(row_node_t* const& head)
{
	row_node_t* head_ref = head;
	while (head_ref != nullptr)
	{
		cout << head_ref->data << endl;
		head_ref = head_ref->next;
	}
}
void print_gamestate(row_node_t* const& head, move_t const& last_move)
{
	size_t counter(1);
	row_node_t* head_ref = head;
	if (last_move.row != 0)
	{
		if (last_move.amount == 1)
		{
			cout << last_move.amount << " stone has been taken from row " << last_move.row << endl << endl;
		}
		else
		{
			cout << last_move.amount << " stones have been taken from row " << last_move.row << endl << endl;
		}
	}

	while (head_ref != nullptr)
	{
		cout << "Row " << counter << ": ";
		for (size_t block(0); block < head_ref->data; block++)
		{
			if (block > 0)
			{
				cout << " ";
			}
			cout << (char)178;
		}
		cout << endl << endl;

		head_ref = head_ref->next;
		counter++;
	}
	if (get_size(head) == 0)
	{
		cout << "There are no more stones!\n";
	}
}
size_t get_min_rows(row_node_t* const& head)
{
	row_node_t* head_ref = head;
	size_t counter(0);
	while (head_ref != nullptr)
	{
		if (head_ref->data == 1)
		{
			counter++;
		}
		head_ref = head_ref->next;
	}

	return counter;
}
move_t make_move(row_node_t* & head)
{
	move_t move = { 1,0 };
	size_t minrows = get_min_rows(head);
	size_t allrows = get_size(head);

	// if 1 row remains
	if (allrows == 1)
	{
		move.row = 1;
		// Computer wins :)
		if (element_at(head, 0) > 1)
		{
			move.amount = element_at(head, 0) - 1;
		}
		// Computer loses :(
		else
		{
			move.amount = 1;
		}
	}
	else
	{
		row_node_t* head_ref = head;
		size_t counter(1);

		//find a row with more than 1 block
		while (head_ref != nullptr && head_ref->data == 1)
		{
			counter++;
			head_ref = head_ref->next;
		}
		//if none is found and all have 1 block - pick the first row.
		if (head_ref == nullptr)
		{
			head_ref = head;
		}

		// If only one row has more than one block, computer can ensure win based on the number of total remaining rows
		if (allrows - minrows == 1)
		{
			if (head_ref != nullptr)
			{
				if (allrows % 2 == 0)
				{
					move.amount = head_ref->data;
				}
				else
				{
					move.amount = head_ref->data - 1;
				}
			}
		}
		// If theres more than one row with one block, remove it.
		else if (allrows - minrows == 2)
		{
			move.amount = head_ref->data-1;
		}
		else
		{
			move.amount = head_ref->data;
		}
		move.row = counter;
	}

	// remove the specified blocks
	element_at(head, move.row - 1) -= move.amount;
	if (element_at(head, move.row - 1) == 0)
	{
		remove_empty_rows(head);
	}

	return move;
}
move_t player_move(row_node_t* & head)
{
	move_t move;
	cout << "Which row do you want to pick from?\n";
	move.row = get_number();
	while (move.row < 1 || move.row > get_size(head))
	{
		cout << "That row doesn't exist! Please re-enter: ";
		move.row = get_number();
	}
	cout << endl;

	cout << "How many stones do you want to pick?\n";
	move.amount = get_number();
	while (move.amount > element_at(head, move.row - 1) || move.amount < 1)
	{
		cout << "Invalid amount! Please re-enter: ";
		move.amount = get_number();
	}

	element_at(head, move.row - 1) -= move.amount;
	if (element_at(head, move.row - 1) == 0)
	{
		remove_empty_rows(head);
	}

	return move;
}
size_t play_game(row_node_t*& rows)
{
	size_t current_user(0);
	move_t last_move{ 0,0 };
	while (get_size(rows) > 0)
	{
		if (current_user == 1)
		{
			system("cls");
		}
		print_gamestate(rows, last_move);

		if (current_user == 0)
		{
			last_move = player_move(rows);
		}
		else
		{
			cout << "Computers turn:\n";
			last_move = make_move(rows);
		}
		current_user = (current_user + 1) % 2;
	}
	cout << endl << endl;
	print_gamestate(rows, last_move);

	return current_user;
}