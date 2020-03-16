#include "data_type.h"

bool convert(char c, data_type& data)
{
	if (c >= '0' && c <= '9')
	{
		data.content = ct_number;
		data.number = c - '0';
	}
	else if (c == '+')
	{
		data.content = ct_add;
		data.number = -1;
	}
	else if (c == '-')
	{
		data.content = ct_sub;
		data.number = -1;
	}
	else if (c == '/')
	{
		data.content = ct_div;
		data.number = -1;
	}
	else if (c == '*')
	{
		data.content = ct_mul;
		data.number = -1;
	}
	else if (c == '(')
	{
		data.content = ct_lpar;
		data.number = -1;
	}
	else if (c == ')')
	{
		data.content = ct_rpar;
		data.number = -1;
	}
	else
	{
		return false;
	}
	return true;
}
