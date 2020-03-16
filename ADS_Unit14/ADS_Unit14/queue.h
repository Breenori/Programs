#if !defined QUEUE_H
#define QUEUE_H
#include<vector>
#include<iostream>
#include "data_type.h"
using namespace std;

struct queue_type {
	vector<data_type> buffer;
	size_t capacity;
	size_t size;
	size_t b;
	size_t e;
};

// Initializes a queue with the given capacity and setting it's other values to zero.
void init(queue_type& queue, size_t capacity);
// Returns whether a queue is empty.
bool empty(queue_type const& queue);
// Returns whether a queue is full.
bool full(queue_type const& queue);
// Returns whether an item could be added to the queue. (False = Queue is full)
bool enqueue(queue_type& queue, data_type const& d);
// Returns whether an item could be removed from the front of the queue. (False = Queue is empty)
bool dequeue(queue_type& queue, data_type& d);
// Prints the current state of the queue.
void print(queue_type const& queue);
#endif
