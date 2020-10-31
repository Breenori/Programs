#include<iostream>
#include<string>
#include<time.h>
using std::string;

int f(int x)
{
	return x + 3;
}

void halve(double &dob)
{
	dob = dob / 2;
}

int getRandomNumber(int const l, int const u)
{
	const int delta = std::abs(l-u) + 1;
	srand((int)time(0));
	return l + rand() % delta;

}

int main()
{
	srand((int)time(0));
	int a(0), b(0);
	std::cin >> a;
	if (std::cin.fail())
	{
		std::cout << "Fehler!";
		a = 10;
	}
	std::cin.clear();
	std::cin.ignore(INT_MAX,'\n');

	std::cin >> b;
	if (std::cin.fail())
	{
		std::cout << "Fehler!";
		b = 20;
	}
	std::cin.clear();
	std::cin.ignore(INT_MAX, '\n');

	//fehlereingabe: validen wert zuweisen, flags clearen und restlichen input ignorieren (parameter: maximaler int, maximale stringlänge oder bis delimiter.)

	for (int i(0); i < 1000; i++)
	{
		int r = a + rand() % (b - a + 1);
		std::cout << r << " ";
	}

	std::cout << std::endl << f(a) << std::endl;
	double d = 190;
	halve(d);

	std::cout << d << std::endl;
	std::cout << getRandomNumber(10, 33);
}