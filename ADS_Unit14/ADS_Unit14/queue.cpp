#include "queue.h"

void init(queue_type& queue, size_t capacity)
{
	queue.capacity = capacity;
	queue.buffer.resize(capacity);
	queue.b = 0;
	queue.e = 0;
	queue.size = 0;
}
bool empty(queue_type const& queue)
{
	return queue.size == 0;
}
bool full(queue_type const& queue)
{
	return queue.size == queue.capacity;
}
bool enqueue(queue_type& queue, data_type const& d)
{
	if (full(queue))
	{
		return false;
	}
	// e = end of the queue. add element to the end of the q and increase it for next use of enqueue.
	else {
		queue.buffer[queue.e++] = d;
		queue.size++;
	}
	return true;
}
bool dequeue(queue_type& queue, data_type& d)
{
	if (empty(queue))
	{
		return false;
	}
	// b = next item in the queue. Use the current element at b and increase b for next use.
	else 
	{
		d.content = queue.buffer[queue.b].content;
		d.number = queue.buffer[queue.b].number;
		queue.size--;
		queue.b++;
	}
	return true;
}
void print(queue_type const& queue)
{
	for (int i(0); i < queue.size; i++)
	{
		if (queue.buffer[i].content == ct_number)
		{
			cout << queue.buffer[i].number;
		}
		else
		{
			switch (queue.buffer[i].content)
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
