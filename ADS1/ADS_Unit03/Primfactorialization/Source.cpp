#include<iostream>
#include<math.h>
using std::cin;
using std::cout;

bool isPrime(long p);

void main()
{
	long a(0);

	cout << "Please enter a number: ";
	cin >> a;
	cout << std::endl;
	if (a > 1)
	{
		if (isPrime(a))
		{
			cout << a;
		}
		else
		{
			while (!isPrime(a))
			{
				/*for (long i(2); i < (a/2); i++)
				{
					if (isPrime(i))
					{
						if (a % i == 0)
						{
							cout << i << " ";
							a = a / i;
							//break;
						}
					}
				}*/
				for (long i(a / 2); i >= 2; i--)
				{
					if (isPrime(i))
					{
						if (a % i == 0)
						{
							cout << i << " ";
							a = a / i;
							break;
						}
					}
				}
			}
			cout << a;
		}
	}
}

bool isPrime(long p) {
	long vergleich = p / 2;
	bool flag(false);

	if (p != 2 && p % 2 == 0)
	{
		return false;
	}
	else
	{
		for (long i(2); i <= vergleich; i++)
		{
			if (p % i == 0)
			{
				flag = true;
				break;
			}
		}
	}

	return !flag;
}