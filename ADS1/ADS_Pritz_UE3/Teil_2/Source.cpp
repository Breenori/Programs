#include<iostream>
using std::string;
using std::cin;
using std::cout;

void print_special(int x);
void print_lowerhundred(int x);
void print_lowerthousand(int x);

void main()
{
	int x(0);
	cout << "Bitte geben Sie die zu uebersetzende Zahl (<1000) ein: ";
	cin >> x;

	if (std::cin.fail())
	{
		x = -1;
	}
	std::cin.clear();
	std::cin.ignore(INT_MAX, '\n');
	
	if (x < 1000 && x >= 0 && x)
	{
		cout << std::endl << "Diese Zahl wird so ausgesprochen: " << std::endl;

		if (x < 20)
		{
			print_special(x);
		}
		else if (x < 100)
		{
			print_lowerhundred(x);
		}
		else
		{
			print_lowerthousand(x);
		}
	}
	else
	{
		cout << "Ungueltige Zahl.";
	}

}

void print_special(int x)
{
	string number_dict[20] = { "null", "eins", "zwei", "drei", "vier", "fuenf", "sechs", "sieben", "acht", "neun", "zehn",
							   "elf", "zwoelf", "dreizehn", "vierzehn", "fuenfzehn", "sechzehn", "siebzehn", "achtzehn", "neunzehn" };

	cout << number_dict[x];
}
void print_lowerhundred(int x)
{
	string tens_dict[10] = { "zehn", "zwanzig", "dreissig", "vierzig", "fuenfzig", "sechzig", "siebzig", "achtzig", "neunzig" };

	if ((x % 10 == 0))
	{
		cout << tens_dict[x / 10 - 1];
	}
	else
	{
		if (x % 10 != 1)
		{
			print_special(x % 10);
		}
		else
		{
			cout << "ein";
		}
		cout << "und" << tens_dict[(x % 100) / 10 - 1];
	}
}
void print_lowerthousand(int x)
{
	if (x / 100 > 1)
	{
		print_special(x/100);
	}
	cout << "hundert";

	if (x % 100 != 0)
	{
		if (x % 100 >= 20)
		{
			print_lowerhundred(x % 100);
		}
		else
		{
			print_special(x % 20);
		}
	}
}