#include "FileManipulator.h"

size_t FileManipulator::partition(std::string const& src, std::vector<std::string> const& dst) 
{
	std::ifstream in(src);
	std::vector<std::ofstream*> out;

	//create outputstreams based on input parameter dst
	for (size_t n(0); n < dst.size(); n++)
	{
		out.push_back(new std::ofstream(dst[n]));
	}

	size_t n(0); // amount of total elements. For arithmetic functions (like determining the middle)
	value_type value;

	while (in >> value)
	{
		std::ofstream& outFile = *(out[n % dst.size()]);
		if (outFile)
		{
			outFile << value << " ";
		}
		n++;
	}

	// free the output streams
	for (size_t i(0); i < out.size(); i++)
	{
		delete out[i];
	}

	return n;
}