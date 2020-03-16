#if !defined STACK_MACHINE_H
#define STACK_MACHINE_H
#include<string>
#include "queue.h"
using namespace std;

// Returns the result of a given expression by evaluating it using a stack-machine.
int evaluate(string const& str);
// Returns whether a given expression could be converted to a UPN-Queue
bool prepare_upn(string const& str, queue_type& upn_q);
#endif