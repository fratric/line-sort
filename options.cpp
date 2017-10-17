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

	bool parametre[3] = { false,false,false };

	for (int i = 1; i < argc;i++) {
		std::string par = argv[i];
		if (par == "-r" && parametre[0] == false) {
			order = Order::descending;
			parametre[0] = true;
		}
		else if (par == "-u" && parametre[1] == false) {
			filter = Filter::unique;
			parametre[1] = true;
		}
		else if (par == "-i" && parametre[2] == false) {
			compare = Case::ignore;
			parametre[2] = true;
		}
	}
	
	int c = 0;
	for (int i = 0; i < 3; i++) {
		if (parametre[i] == true) {
			c++;
		}
	}

	if (argc-1==4)
	{
		input = argv[argc - 1];
		c++;
	}
	else if (argc-1==3 && c!=3) {
		input = argv[argc - 1];
		c++;
	}
	else if (argc-1==2 && c!=2) {
		input = argv[argc - 1];
		c++;
	}
	else if (argc-1==1 && c!=1) {
		input = argv[argc - 1];
		c++;
	}

	if (argc-1>c) {
		return {};
	}

	return std::make_tuple(order, filter, compare, input);
}
