#include "stack_machine.h"
#include "stack.h"
#include "queue.h"

int evaluate(string const& str)
{
	queue_type upn_q;
	// By setting the capacities to the length of the string we prevent running out of queue-slots.
	// This way, every calculation, however long it may be, can be evaluated.
	init(upn_q, str.size());

	// If the UPN queue could be built without failure: proceed.
	// Else: Return 0 (unable to evaluate)
	if (prepare_upn(str, upn_q))
	{
		stack_type help_s;
		init(help_s, str.size());
		data_type d;

		// Work through all the elements in the UPN-Queue
		while (!empty(upn_q))
		{
			if (dequeue(upn_q, d))
			{
				// If it is a number, we put it on the help stack.
				if (d.content == ct_number)
				{
					push(help_s, d);
				}
				// If it's an operator, the following is done:
				// The last two numbers are taken off the help stack and treated according to the operator.
				// The result is then pushed back on the help stack.
				else
				{
					if (help_s.size >= 2)
					{
						data_type param1;
						data_type param2;
						pop(help_s, param1);
						pop(help_s, param2);
						data_type result;
						result.content = ct_number;
						switch (d.content)
						{
							case ct_add:
								result.number = param2.number + param1.number;
								break;
							case ct_sub:
								result.number = param2.number - param1.number;
								break;
							case ct_mul:
								result.number = param2.number * param1.number;
								break;
							case ct_div:
								result.number = param2.number / param1.number;
								break;
						}
						push(help_s, result);
					}
					// If an operator is read but there are less than 2 numbers on the stack the evaluation can't proceed.
					else
					{
						cout << "ERROR! Insufficient amount of parameters on help stack.\n";
						return 0;
					}
				}
			}
		}
		// If there's only one element on the help stack, the evaluation has completed successfully.
		// If there are more elements remaining that indicates, that some operators may be missing or the numbers weren't single digit. Return 0.
		if (help_s.size == 1)
		{
			pop(help_s, d);
			return d.number;
		}
	}
	return 0;
}

bool prepare_upn(string const& str, queue_type& upn_q)
{
	queue_type input_q;
	stack_type help_s;
	init(input_q, str.size());
	init(help_s, str.size());
	data_type d;

	// Every char in the string is converted to our specific data_type
	for (int i(0); i < str.size(); i++)
	{
		if (convert(str[i], d))
		{
			enqueue(input_q, d);
		}
		else
		{
			cout << "ERROR! Invalid character (" << str[i] << ") found.\n";
			return false;
		}
	}

	// Using the input queue we build the UPN queue.
	while (!empty(input_q))
	{
		if (dequeue(input_q, d))
		{
			// If its a number, simply add it to the upn queue
			if (d.number >= 0)
			{
				enqueue(upn_q, d);
			}
			// Operators get pushed on the help stack
			else if (d.content != ct_rpar)
			{
				if (d.content != ct_lpar)
				{
					push(help_s, d);
				}
			}
			// If it's a right bracket we need to take one operator off the help stack and put it on the UPN queue
			else
			{
				if (pop(help_s, d))
				{
					enqueue(upn_q, d);
				}
				// If there's no operator on the helpstack, throw an error.
				else
				{
					cout << "ERROR! Insufficient items on help stack.\n";
					return false;
				}
			}
		}
	}

	// All remaining operators outside the brackets need to be taken from the help stack and added to the queue.
	while (!empty(help_s))
	{
		if (pop(help_s, d))
		{
			enqueue(upn_q, d);
		}
	}
	return true;
}
