#include "stack.h"

void init(stack_type& stack, size_t capacity)
{
	stack.capacity = capacity;
	stack.buffer.resize(capacity);
	stack.size = 0;
}
bool empty(stack_type const& stack)
{
	return stack.size == 0;
}
bool full(stack_type const& stack)
{
	return stack.size == stack.capacity;
}
bool push(stack_type& stack, data_type const& d)
{
	if (full(stack))
	{
		return false;
	}
	else {
		stack.buffer[stack.size++] = d;
	}
	return true;
}
bool pop(stack_type& stack, data_type& d)
{
	if (empty(stack))
	{
		return false;
	}
	else
	{
		d.content = stack.buffer[stack.size-1].content;
		d.number = stack.buffer[stack.size-1].number;
		stack.size--;
	}
	return true;
}
bool top(stack_type const& stack, data_type& d)
{
	if (empty(stack))
	{
		return false;
	}
	else
	{
		d.content = stack.buffer[stack.size-1].content;
		d.number = stack.buffer[stack.size-1].number;
	}
	return true;
}
void print(stack_type const& stack)
{
	for (int i(0); i < stack.size; i++)
	{
		if (stack.buffer[i].content == ct_number)
		{
			cout << stack.buffer[i].number;
		}
		else
		{
			switch (stack.buffer[i].content)
			{
			case ct_add:
				cout << "+";
				break;
			case ct_sub:
				cout << "-";
				break;
			case ct_mul:
				cout << "*";
				break;
			case ct_div:
				cout << "/";
				break;
			}
		}
	}
}