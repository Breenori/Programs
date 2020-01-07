#include<iostream>
#include<vector>
#include<time.h>

void print_vector(std::vector<int> const& v);
void multiply(std::vector<int>& v, int n);
double average(std::vector<int>const& v);
int sum(std::vector<int> const& v);
void init(std::vector<int>& v, int const n, bool fill_rand, bool fill_inc, bool fill_dec);

double median(std::vector<int>const& v);
void sort(std::vector<int>& v);
void rotate(std::vector<int>& v, const int b, const int e);



int main()
{
	std::vector<int> v;
	v.push_back(10);
	v.push_back(12);
	v.push_back(5);
	v.push_back(4);
	v[3] = 3;

	//print_vector(v);

	/*multiply(v,200);
	print_vector(v);
	std::cout << std::endl << average(v);
	std::cout << "\n\n";
	*/
	init(v, 20, true, false, false);
	print_vector(v);

	std::cout << "\n\n";
	
	std::cout << std::endl << "Median: " << median(v) << std::endl;

	sort(v);
	print_vector(v);
}

void print_vector(std::vector<int> const& v)
{
	for (int i(0); i < std::size(v); i++)
	{
		if (i != 0)
		{
			std::cout << ", ";
		}
		std::cout << v[i];
	}
}
void multiply(std::vector<int>& v, int n)
{
	for (int i(0); i < std::size(v); i++)
	{
		v[i] = v[i] * n;
	}
}
double average(std::vector<int>const& v)
{
	return 1.0 * sum(v) / std::size(v);
}
int sum(std::vector<int> const& v)
{
	int sum(0);
	for (int i(0); i < std::size(v); i++)
	{
		sum += v[i];
	}

	return sum;
}
void init(std::vector<int>& v, int const n, bool fill_rand, bool fill_inc, bool fill_dec)
{
	v.clear();
	v.resize(n);

	srand((int)time(0));

	for (int i(0); i < n; i++)
	{
		if (fill_rand)
		{
			v[i] = rand() % n;
		}
		else if (fill_inc)
		{
			v[i] = i;
		}
		else if (fill_dec)
		{
			v[i] = n - i - 1;
		}
	}
}

double median(std::vector<int>const& v)
{
	if (std::size(v))
	{
		return 0;
	}

	std::vector<int> tmp = v;
	sort(tmp);

	if (std::size(tmp) % 2 == 0)
	{
		return (tmp[std::size(tmp) / 2 - 1] + tmp[std::size(tmp) / 2]) / 2.0;
	}
	else
	{
		return (tmp[std::size(tmp) / 2]);
	}
}
void sort(std::vector<int>& v)
{
	for (int i(0); i < std::size(v)-1; i++)
	{
		int j = i;
		for (int k(i+1); k < std::size(v); k++)
		{
			if (v[k] < v[j])
			{
				j = k;
			}
		}

		if (j > i)
		{
			rotate(v, i, j + 1);
		}
	}
}
void rotate(std::vector<int> &v, const int b, const int e)
{
	if (b > e)
	{
		return;
	}

	int tmp = v[e - 1];
	
	for(int i(e - 2); i >= b; i--)
	{
		bool a = (i >= b);
		v[i + 1] = v[i];
	}
	

	v[b] = tmp;
}