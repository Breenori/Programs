#include "slw.h"

void shift_left(vector<double>& slw);

void set_max_size(slw_t& slw, size_t const s)
{
	slw.max_size = s;
}
void add_value(slw_t& slw, double const v)
{
	if (slw.max_size > slw.values.size())
	{
		slw.values.push_back(v);
	}
	else
	{
		slw.sum -= slw.values[0];
		shift_left(slw.values);
		slw.values[slw.max_size - 1] = v;
	}
	slw.sum += v;
}
void shift_left(vector<double>& slw)
{
	for (int i(0); i < slw.size() - 1; i++)
	{
		slw[i] = slw[i + 1];
	}
}
void clear(slw_t& slw)
{
	slw.max_size = 0;
	slw.sum = 0;
}
void init(slw_t& slw)
{
	slw.max_size = 0;
	slw.sum = 0;
}
void print(slw_t& slw, ostream& o)
{
	o << slw.max_size << std::endl;
	for (size_t i(0); i < slw.values.size(); i++)
	{
		if (i > 0)
		{
			o << ", ";
		}
		o << slw.values[i];
	}

}