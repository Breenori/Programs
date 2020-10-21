#ifndef MERGESORT_H
#define MERGESORT_H
#include "FileManipulator.h"

static std::size_t const LEFT = 0;	// Left file
static std::size_t const RIGHT = 1;	// Right file

class MergeSort {

public:
	typedef FileManipulator fm;
	typedef std::string value_type;

	value_type c_wf[2][2]; // c_wf = choose writefile
	bool c_wf_swap;

	MergeSort()
	{
		c_wf_swap = false;
	}

	void sort(value_type const& filename);

private:

	value_type const& getSrc(const size_t& i);
	value_type const& getDst(const size_t& i);
	
	void merge(const size_t& k);
	void swap();
};

#endif