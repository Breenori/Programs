#include<iostream>
using std::cout;
using std::cin;

void main() {
	int a(0);
	int b(0);
	int c(0);

	cout << "Please enter a, b und c:\n";
	cin >> a >> b >> c;
	cout << std::endl;

	if (a != 0)
	{
		float p(b / a);
		float q(c / a);
		float D(pow((p / 2), 2) - q);

		if (D >= 0)
		{
			int x1 = -(p / 2) + sqrt(D);
			int x2 = -(p / 2) - sqrt(D);

			if (x1 == x2)
			{
				cout << "x = " << x1 << std::endl;
			}
			else
			{
				cout << "x1 = " << x1 << std::endl;
				cout << "x2 = " << x2 << std::endl;
			}
		}
		else
		{
			cout << "x1 = " << -(p / 2) << "+i" << (sqrt(-D)) << std::endl;
			cout << "x2 = " << -(p / 2) << "-i" << (sqrt(-D)) << std::endl;
		}
	}
	else
	{
		if (b != 0)
		{
			float x = -c / b;
			cout << "x = " << x;
		}
		else
		{
			if (c != 0)
			{
				cout << "Valid for none.";
			}
			else
			{
				cout << "Valid for all.";
			}
		}
	}
}