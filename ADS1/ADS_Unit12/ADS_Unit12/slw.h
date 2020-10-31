#pragma once
#if !defined SLW_H
#define SLW_H
#include<vector>
#include<iostream>
using std::vector;
using std::ostream;

struct slw_t {
	size_t size;
	vector<double> values;
};

void add_value(slw_t& slw, double v);
void set_size(slw_t& slw, size_t s);
void print(slw_t& slw, ostream& o);
void clear(slw_t& slw);

#endif