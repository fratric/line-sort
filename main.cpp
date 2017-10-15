
#include <iostream>
#include <fstream>
#include <ostream>

#include "options.h"
#include "sort.h"

int main(int argc, char * argv[])
{
	auto options = options::parse(argc, argv);
	if (!options)
	{
		// print "help"
		return -1;
	}

	Order order;
	Filter filter;
	Case compare;
	char * file;

	std::tie(order, filter, compare, file) = options.value();

	std::fstream fs;
	if (file)
	{
		fs.open(file);
		if (fs.bad())
		{
			// print "file error"
			std::cerr << "error" << std::endl;
			return -1;
		}
	}

	std::istream & input = file ? fs : std::cin;
	
	if (!sort::process(order, filter, compare, input, std::cout))
	{
		// print "sort error"
		std::cerr << "error" << std::endl;
		return -1;
	}
	return 0;
}

