#if !defined STACK_H
#define STACK_H
#include<vector>
#include<iostream>
#include "data_type.h"
using namespace std;

struct stack_type {
	vector<data_type> buffer;
	size_t capacity;
	size_t size;
};

// Initializes a stack with the given capacity and setting it's other values to zero.
void init(stack_type& stack, size_t capacity);
// Returns whether a stack is empty or not.
bool empty(stack_type const& stack);
// Returns whether a stack is full or not.
bool full(stack_type const& stack);
// Returns whether an item could be added to the stack (False = stack is full)
bool push(stack_type& stack, data_type const& d);
// Returns whether an item could be removed from the top of the stack (False = stack is empty)
bool pop(stack_type& stack, data_type& d);
// Returns whether an item could be read from the top of the stack. (False = stack is empty)
// This does NOT remove the item.
bool top(stack_type const& stack, data_type& d);
// Prints the current state of the stack
void print(stack_type const& stack);
#endif