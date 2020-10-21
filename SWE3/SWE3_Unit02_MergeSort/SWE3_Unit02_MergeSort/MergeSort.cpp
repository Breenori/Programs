#include "MergeSort.h"
#include<vector>

void MergeSort::sort(value_type const& filename)
{
	size_t k(1);
	std::vector<value_type> src;
	src.push_back(getSrc(LEFT));
	src.push_back(getSrc(RIGHT));

	// 1) partition
	size_t const n(fm::partition(filename, src));
	// 2) merge
	// 3) copy result in source file
	
	
}

// Returns the current filename for reading
MergeSort::value_type const& MergeSort::getSrc(const size_t& i)
{
	return c_wf[c_wf_swap ? RIGHT : LEFT][i];
}

// Returns the current filename for writing
MergeSort::value_type const& MergeSort::getDst(const size_t& i)
{
	return c_wf[c_wf_swap ? LEFT : RIGHT][i];
}

void MergeSort::swap()
{
	c_wf_swap = !c_wf_swap;
}


int main()
{
	std::string const filename("file-to-sort.txt");

	MergeSort ms = MergeSort();
	ms.c_wf[0][0] = "f0.txt";
	ms.c_wf[0][1] = "f1.txt";
	ms.c_wf[1][0] = "g0.txt";
	ms.c_wf[1][1] = "g1.txt";

	ms.sort(filename);

	return 0;
}