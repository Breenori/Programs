#ifndef HEAP_SORT_H
#define HEAP_SORT_H

#include<iostream>
#include<iomanip>
#include<vector>

class HeapSort {

public:
	// Type of container
	typedef std::vector<int> cont_type;
	// Type of element
	typedef std::size_t index_type;
	// Type of element-index in container
	typedef cont_type::size_type size_type;

	static void sort(cont_type& v);
	static void print(cont_type& v);

	static void print_tree(cont_type const& v);

private:
	// Variable to change how wide the tree will be (how far each layer will be from each other)
	static const size_t TREE_SPACING_MULTIPLIER = 5;

	static void build_heap(cont_type& v)
	{
		// Call heapify for all relevant elements (every element where left or right child exists)
		// ^ Done in order to assure heap property (children smaller than parent)
		for (int i = v.size() / 2 - 1; i >= 0; --i)
		{
			heapify(v, v.size(), i);
		}
	}

	static void heapify(cont_type& v, size_type const n, index_type const i)
	{
		// Get left child, right child and parent.
		index_type const l = left(i);
		index_type m = i;
		index_type const r = right(i);

		// check if left child is bigger
		if((l < n) && (v[l] > v[i]))
		{
			m = l;
		}

		// check if right child is bigger
		if ((r < n) && (v[r] > v[m]))
		{
			m = r;
		}

		// If left or right child is bigger than current element (middle), swap it.
		if (m > i)
		{
			std::swap(v[i], v[m]);
			heapify(v, n, m);
		}
	}

	// returns the left child of a given node i
	static index_type left(index_type const i)
	{
		return 2 * i + 1;
	}
	// returns the right child of a given node i
	static index_type right(index_type const i)
	{
		return 2 * (i + 1);
	}
	// returns the partent of a given node i
	static index_type parent(index_type const i)
	{
		return (i - 1) / 2;
	}

	// Prints the data container as a vertical tree.
	static void print_tree_worker(cont_type const& v, size_t const index, size_t const depth)
	{
		// Recursion floor: Index out of bounds
		if (index < v.size())
		{
			// Print the "tree" in the order of: Right, Parent, Left
			print_tree_worker(v, right(index), depth + 1);
			std::cout << std::setw(TREE_SPACING_MULTIPLIER * depth) << " " << v[index] << std::endl;
			print_tree_worker(v, left(index), depth + 1);
		}
	}

};

#endif