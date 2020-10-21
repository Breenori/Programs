#include "heap_sort.h"

void HeapSort::sort(cont_type& v)
{
	// Make sure that biggest element is at v[0]
	build_heap(v);
	
	// Swap, heapify and repeat process til sorted.
	for (int i = v.size() - 1; i > 0; --i)
	{
		std::swap(v[0], v[i]);
		heapify(v, i, 0);
	}
}

void HeapSort::print(HeapSort::cont_type& v)
{
	// Print all elements of the container/vector
	std::cout << "<";
	for (int i(0); i < v.size(); i++)
	{
		if (i > 0)
		{
			std::cout << ", ";
		}
		std::cout << v[i];
	}
	std::cout << ">\n";
}

void HeapSort::print_tree(cont_type const& v)
{
	// Delegates to worker function
	print_tree_worker(v, 0, 0);
}

void main()
{
	HeapSort::cont_type v{ 7, 10, 15, 24,3, 1, 42, 31, 5, 6 };
	HeapSort::print(v);
	HeapSort::print_tree(v);
	HeapSort::sort(v);
	HeapSort::print(v);
	HeapSort::print_tree(v);
}