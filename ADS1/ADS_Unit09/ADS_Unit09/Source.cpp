#include<iostream>
#include<vector>
using namespace std;

enum rt_roletype { seas, oida, wos, geht};

struct name {
	string vorname;
	string nachname;
};

typedef std::vector<std::vector<double>> matrix;

void sort(std::vector<int>& numbers);
void rotate(std::vector<int>& nums, int const b, int const e);
void print_all(std::vector<int> const& nums);

void main()
{
	std::vector<int> numbers = { 3, 5, 1, 10, 8 };
	sort(numbers);
	print_all(numbers);
}




void sort(std::vector<int>& numbers)
{
	for (int i(0); i < numbers.size() - 1; i++)
	{
		int j = i;
		for (int k(i + 1); k < numbers.size(); k++)
		{
			if (numbers[k] < numbers[j])
			{
				j = k;
			}
		}

		if (j > i)
		{
			rotate(numbers, i, j);
		}
	}
}

void rotate(std::vector<int>& nums, int const b, int const e)
{
	int tmp(nums[e]);
	for (int i(e - 1); i >= b; i--)
	{
		nums[i + 1] = nums[i];
	}
	nums[b] = tmp;
}

void print_all(std::vector<int> const& nums)
{
	for (int i(0); i < nums.size(); i++)
	{
		if (i > 0)
		{
			cout << ", ";
		}
		cout << nums[i];
	}
}