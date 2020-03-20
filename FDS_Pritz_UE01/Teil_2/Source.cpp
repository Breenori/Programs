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
void append(row_node_t* & head, size_t const value, size_t len=35);
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

	// if it returns 0, the user won
	if (play_game(rows) == 0)
	{
		cout << "Congratulations! You won! :)";
	}
	else
	{
		cout << "You lost! Better luck next time! ;)";
	}
	cout << endl << endl;
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
	// Get every line of the file.
	if (in)
	{
		while (getline(in, line))
		{
			// Convert it to int.
			// By doing this instead of using "cin" directly, we ensure that 1 line results in 1 value.
			val = std::stoi(line);
			// Appends the value to the linked list.
			append(head, val);
		}
	}

	in.close();
}
void append(row_node_t* & head, size_t const value, size_t len)
{
	// Value should be above 1 (empty rows are removed either way) and less/equal 35 to fit into the 80 width console. (35 elements, 35 whitespaces = 70 + "Row x:")
	if (value >= 1 && value <= len)
	{
		// Creates a new node and initializes it.
		row_node_t* new_node = new row_node_t;
		new_node->data = value;
		new_node->next = nullptr;

		// If the list is empty, set new node as head.
		if (head == nullptr)
		{
			head = new_node;
		}
		else
		{
			// If the list isn't empty, set it's address to the member "next" of the last element.
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

	// Count all elements in the list by waiting for a nullptr (at member "next" of last element)
	while (head_ref != nullptr)
	{
		head_ref = head_ref->next;
		counter++;
	}

	return counter;
}
size_t& element_at(row_node_t* const & head, size_t const index)
{
	// Similiar to "index out of bounds exception" for vectors, we have to make sure that we can access the element.
	// Otherwise we can't return a reference to an element.
	assert(head != nullptr);
	assert(index < get_size(head));

	row_node_t* head_ref = head;

	// Get the right address
	for (int i(0); i < index; i++)
	{
		head_ref = head_ref->next;
	}

	// Return the address so we can work with it. Works as setter and getter.
	return head_ref->data;
}
void remove_empty_rows(row_node_t* & head)
{
	// Check first node
	if (head != nullptr)
	{
		if (head->data == 0)
		{
			// If data is null and head is null, the node can be deleted and the list is now empty.
			if (head->next == nullptr)
			{
				delete head;
				head = nullptr;
			}
			// If there is a successor, make the successor the new head.
			else
			{
				row_node_t* tmp = head->next;
				delete head;
				head = tmp;
			}
		}
	}

	// Check successor nodes.
	row_node_t* head_ref = head;
	while (head_ref != nullptr)
	{
		// If there is a successor
		if (head_ref->next != nullptr)
		{
			// If the successor is zero
			if (head_ref->next->data == 0)
			{
				// Delete the first successor and set the 2nd successor as next.
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
	// Print an overview of the last move.
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

	// Print the playing field. (all rows and stones)
	while (head_ref != nullptr)
	{
		cout << "Row " << counter << ": ";
		for (size_t block(0); block < head_ref->data; block++)
		{
			if (block > 0)
			{
				cout << " ";
			}
			if ((block) % 5 == 0)
			{
				cout << " ";
			}
			cout << (char)178;
		}
		cout << endl << endl;

		head_ref = head_ref->next;
		counter++;
	}

	// If list empty, print that no stones are available. Game ends.
	if (get_size(head) == 0)
	{
		cout << "\n*ding ding ding*\nTHERE ARE NO MORE STONES!\n";
	}
	cout << endl;
}
size_t get_min_rows(row_node_t* const& head)
{
	row_node_t* head_ref = head;
	size_t counter(0);

	// Count every row where only one stone is left.
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
	if (head != nullptr)
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
				counter = 1;
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
			// Generally the cpu has lost at this point (if the player is good) but we can try to bamboozle him.
			else if (allrows - minrows == 2)
			{
				move.amount = head_ref->data - 1;
			}
			// Reduce amount of rows as long as other conditions aren't met.
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
	else
	{
		return { 0,0 };
	}
}
move_t player_move(row_node_t* & head)
{
	if (head != nullptr)
	{
		// Let the user pick the row.
		move_t move;
		cout << "Which row do you want to pick from?\n";
		move.row = get_number();
		while (move.row < 1 || move.row > get_size(head))
		{
			cout << "That row doesn't exist! Please re-enter: ";
			move.row = get_number();
		}
		cout << endl;

		// Let the user pick the amount of stones.
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
	return { 0,0 };
}
size_t play_game(row_node_t*& rows)
{
	// 0 = user, 1 = computer
	size_t current_user(0);
	// stores the last move made. element 1 = rows, element 2 = amount.
	move_t last_move{ 0,0 };

	// As long as stones/rows are left, repeat gameloop.
	while (get_size(rows) > 0)
	{
		// Clear the screen everytime the CPU starts playing.
		if (current_user == 1)
		{
			system("cls");
		}
		print_gamestate(rows, last_move);

		// Depending on current_user, either player or cpu gets to move.
		if (current_user == 0)
		{
			last_move = player_move(rows);
		}
		else
		{
			cout << "Computers turn:\n";
			last_move = make_move(rows);
		}

		// change player.
		current_user = (current_user + 1) % 2;
	}
	cout << endl << endl;
	print_gamestate(rows, last_move);

	return current_user;
}