#include<iostream>
using std::cout;
using std::cin;

void main()
{
	cout << "Please enter a value: ";
	int a(0);
	cin >> a;

	switch (a)
	{
		case 0:
			cout << "zero\n";
			break;
		case 1:
			cout << "ichi\n";
			break;
		case 2:
			cout << "ni\n";
			break;
		case 3:
			cout << "tres\n";
			break;
		default:
			cout << a << std::endl;
			break;
	}
	cout << std::endl;


	int x(0);
	while (x >= 0)
	{
		cout << "Insert a positive number: ";
		cin >> x;
	}

	do {
		cout << "Insert a negative number: ";
		cin >> x;
	} while (x < 0);
	cout << std::endl;



	cout << "Please enter dividend: ";
	cin >> x;
	cout << std::endl;

	cout << "Please enter divisor: ";
	int d(0);
	cin >> d;
	cout << std::endl;

	if (x % d == 0)
	{
		cout << x << " CAN be divided by " << d << " without a remainder.\n";
	}
	else {
		cout << x << " CANNOT be divided by " << d << " without a remainder.\n";
	}

}