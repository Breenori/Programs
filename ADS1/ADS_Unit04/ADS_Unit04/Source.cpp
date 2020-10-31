#include<iostream>
using std::cout;
using std::cin;

void main()
{
	int a(0);
	int b(0);
	int c(0);
	int d(0);

	cout << "Bitte a, b und c eingeben. \n";
	cin >> a >> b >> c >> d;
	cout << std::endl << "UND ";

	/*
	for (int i(a); i <= b; i++)
	{
		if (i % c == 0 && i % d == 0)
		{
			cout << i << " durch " << c << " und " << d << " teilbar." << std::endl;
		}
		else if (i % c == 0 || i % d == 0) {
			cout << i << " durch " << c << " oder " << d << " teilbar." << std::endl;
		}
	}*/

	bool first(true);
	for (int i(a); i <= b; i++)
	{
		if (i % c == 0 && i % d == 0)
		{
			if (!first)
			{
				cout << ", ";
			}
			cout << i;
			first = false;
		}
	}

	cout << std::endl << "ODER: ";

	first = true;
	for (int i(a); i <= b; i++)
	{
		if (i % c == 0 || i % d == 0)
		{
			if (!first)
			{
				cout << ", ";
			}
			cout << i;
			first = false;
		}
	}
}