#include<iostream>
#include<string>
using namespace std;

enum direction_type { ascending, descending };

// Returns a number. Reads til the input is valid and adresses possible "cin"-issues
int read_number();
// Returns if a given number is prime or not
bool isPrime(int const p);
// Prints all prime factors of a given number on the console
void print_primefactors(int num);

void main()
{
	int input_num(read_number());

	print_primefactors(input_num);
}

int read_number()
{
	int num(0);
	cout << "Please enter a number to be factorialized: \n";
	cin >> num;

	// make sure the user enters a valid number
	while (cin.fail())
	{
		num = 0;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "The value must be numeric (MAX:" << INT_MAX << "): ";
		cin >> num;
	}
	// If there's something after the number, clear it.
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	return num;
}
bool isPrime(int const p) {
	// numbers above p/2 always cause a number less than 2 in case of division.
	// since those numbers are irrelevant for prime check, we just loop to half of the number or till we find a divisor.
	int vergleich = p / 2;
	bool flag(false);

	int divisor(2);
	while (divisor <= vergleich && !flag)
	{
		if (p % divisor == 0)
		{
			flag = true;
		}
		divisor++;
	}
	

	return !flag;
}
void print_primefactors(int num)
{
	if (num > 1)
	{
		direction_type dir(ascending);
		string ans("");

		// ask for direction til we get a valid answer
		do {
			cout << "List them ascending or descending? (a/d) ";
			getline(cin, ans);
		} while (ans != "a" && ans != "d" && ans != "ascending" && ans != "descending");

		if (ans == "d" || ans == "descending")
		{
			dir = descending;
		}

		// If the number is already prime, it can't be divided further...
		if (isPrime(num))
		{
			cout << num;
		}
		else
		{
			cout << std::endl;
			if (dir == ascending)
			{
				cout << "The primefactors in ascending order are: \n";
			}
			else if (dir == descending)
			{
				cout << "The primefactors in descending order are: \n";
			}
			
			// ... if not, we repeat division until the number itself is prime
			while (!isPrime(num))
			{
				int divisor(2);
				int end(num / 2);

				// divisor and end were initialized with values for ascending. If descending, we just swap them.
				if (dir == descending)
				{
					swap(divisor, end);
				}

				//since the number isn't prime it MUST have a divisor -> stop condition
				bool division_flag(false);
				while (!division_flag)
				{
					if (isPrime(divisor) && num % divisor == 0)
					{
						// if we find a divisor, we print it and divide the number by it and also set the flag to check the next value
						cout << divisor << " ";
						num = num / divisor;
						division_flag = true;
					}

					if (dir == ascending)
						divisor++;
					else
						divisor--;
				}
			}

			cout << num;
		}
	}
	else
	{
		cout << std::endl << "Entered number isn't greater than 1. Terminating. \n";
	}
}
