#include<iostream>
#include<cstdint>
#include "pfc-mini.hpp"

namespace fds {
	struct testStruct {
		union {
			uint8_t a[2];
			uint16_t b;
		};
	};
	
	void print_testStruct(testStruct const& ts)
	{
		std::cout << ts.a[0] << " " << ts.a[1] << "\n";
	}
}

void main()
{
	fds::testStruct t1;
	t1.a[0] = 5;
	t1.a[1] = 9;

	std::cout << t1.b;
	std::cout << std::endl;

	for (int i(0); i < 100; ++i)
	{
		std::cout << pfc::get_random_uniform(0,100) << " ";
	}
}