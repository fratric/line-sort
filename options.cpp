#include "options.h"

#include <iostream>
#include <fstream>
#include <ostream>
#include <string>

std::optional<std::tuple<Order, Filter, Case, char *>> options::parse(int argc, char * argv[])
{
	Order order { Order::ascending };
	Filter filter { Filter::all };
	Case compare { Case::sensitive };
	char * input{ nullptr };

	bool parametre[4] = { false,false,false,false };
	std::string par = argv[argc - 1];
	if (par.size()>2 && par[0] != '-' && argc>1)
	{
		input = argv[argc - 1];
		par[3] = true;
	}

	for (int i = 1; i < argc;i++) {
		std::string par = argv[i];
		if (par == "-r") {
			order = Order::descending;
			parametre[0] = true;
		}
		else if (par == "-u") {
			filter = Filter::unique;
			parametre[1] = true;
		}
		else if (par == "-i") {
			compare = Case::ignore;
			parametre[2] = true;
		}
	}

	int c = 0;
	for (int i = 0; i < 4;i++) {
		if (parametre[i] == true) {
			c++;
		}
	}

	if (argc-1!=c) {
		return {};
	}

	return std::make_tuple(order, filter, compare, input);
}
