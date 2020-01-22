#pragma once
#if !defined SLW_H
#define SLW_H
#include<vector>
#include<iostream>
using std::vector;
using std::ostream;
using std::cout;

struct slw_t {
	size_t max_size;
	vector<double> values;
	double sum;
};

void add_value(slw_t& slw, double const v);
void set_max_size(slw_t& slw, size_t const s);
void print(slw_t& slw, ostream& o = cout);
void clear(slw_t& slw);
void init(slw_t& slw);

#endif