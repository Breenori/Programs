#include "slw.h"

void shift_left(vector<double>& slw);

void set_size(slw_t& slw, size_t s)
{

}

void add_value(slw_t& slw, double v)
{
	if (slw.size > slw.values.size())
	{
		slw.values.push_back(v);
	}
	else
	{
		shift_left(slw.values);
		slw.values[slw.size - 1] = v;
	}
}

void shift_left(vector<double>& slw)
{
	for (int i(0); i < slw.size() - 1; i++)
	{
		slw[i] = slw[i + 1];
	}
}