#include<iostream>
#include<thread>
// using std::cout
// using std::cin

void main() 
{
	std::cout << "Please insert x:";
	int x(0);
	std::cin >> x;
	std::cout << "Your chosen number was: " << x << "\n";

	if (x < 0)
	{
		std::cout << "The entered number is negative. (" << x << ")\n";
	}
	else if (x > 0)
	{
		std::cout << "The entered number is positive. (" << x << ")\n";
	}
	else
	{
		std::cout << "The entered number is Zero. (" << x << ")\n";
	}


	std::cout << "Please insert y:";
	int y(0);
	std::cin >> y;
	std::cout << "Your chosen number was: " << y << "\n";

	if (y < 0)
	{
		std::cout << "The entered number is negative. (" << y << ")\n";
	}
	else if (y > 0)
	{
		std::cout << "The entered number is positive. (" << y << ")\n";
	}
	else
	{
		std::cout << "The entered number is Zero. (" << y << ")\n";
	}

	int i(x);
	if (x < y)
	{
		while (i <= y)
		{
			std::cout << i++ << " ";
		}
	}
	else if (x > y)
	{
		
		while (i >= y)
		{
			std::cout << i-- << " ";
		}
		
		/*x = x + y;
		y = x - y;
		x = x - y;

		i = x;

		while (i <= y)
		{
			std::cout << i++ << " ";
		}*/
	}
	else
	{
		std::cout << x;
	}

	std::cout << "\n\n\n";
}