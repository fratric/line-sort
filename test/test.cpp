#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "options.h"
#include "sort.h"

#include <sstream>

TEST_CASE("Options")	//na zadanie testovat parsovaciu funkciu
{
	SECTION("no options")
	{
		char * argv[] = { "line-sort" };
		REQUIRE(options::parse(1, argv) == std::make_tuple(Order::ascending, Filter::all, Case::sensitive, (char *) nullptr));
	}

	SECTION("no options and input") {
		char * argv[] = { "line-sort" , "input" };
		REQUIRE(options::parse(_countof(argv), argv) == std::make_tuple(Order::ascending, Filter::all, Case::sensitive, (char *) "input"));
	}

	SECTION("reversed")
	{
		char * argv[] = { "line-sort" , "-r"};
		REQUIRE(options::parse(_countof(argv), argv) == std::make_tuple(Order::descending, Filter::all, Case::sensitive, (char *) nullptr));
	}

	SECTION("reversed and input") {
		char * argv[] = { "line-sort" , "-r" , "input" };
		REQUIRE(options::parse(_countof(argv), argv) == std::make_tuple(Order::descending, Filter::all, Case::sensitive, (char *) "input"));
	}


	SECTION("unique")
	{
		char * argv[] = { "line-sort" , "-u" };
		REQUIRE(options::parse(_countof(argv), argv) == std::make_tuple(Order::ascending, Filter::unique, Case::sensitive, (char *) nullptr));
	}

	SECTION("unique and input") {
		char * argv[] = { "line-sort" , "-u" , "input" };
		REQUIRE(options::parse(_countof(argv), argv) == std::make_tuple(Order::ascending, Filter::unique, Case::sensitive, (char *) "input"));
	}

	SECTION("ignore case")
	{
		char * argv[] = { "line-sort" , "-i"};
		REQUIRE(options::parse(_countof(argv), argv) == std::make_tuple(Order::ascending, Filter::all, Case::ignore, (char *) nullptr));
	}

	SECTION("ignore case and input") {
		char * argv[] = { "line-sort" , "-i" , "input" };
		REQUIRE(options::parse(_countof(argv), argv) == std::make_tuple(Order::ascending, Filter::all, Case::ignore, (char *) "input"));
	}

	SECTION("multiple 3")
	{
		char * argv[] = { "line-sort" , "-r" , "-i" , "-u" };
		REQUIRE(options::parse(_countof(argv), argv) == std::make_tuple(Order::descending, Filter::unique, Case::ignore, (char *) nullptr));
	}

	SECTION("multiple 3 and input")
	{
		char * argv[] = { "line-sort" , "-r" , "-i" , "-u" , "input" };
		REQUIRE(options::parse(_countof(argv), argv) == std::make_tuple(Order::descending, Filter::unique, Case::ignore, (char *) "input"));
	}

	SECTION("multiple 2")
	{
		char * argv[] = { "line-sort" , "-r" , "-u" };
		REQUIRE(options::parse(_countof(argv), argv) == std::make_tuple(Order::descending, Filter::unique, Case::sensitive, (char *) nullptr));
	}

	SECTION("multiple 2 and input")
	{
		char * argv[] = { "line-sort" , "-r" , "-u" , "input"};
		REQUIRE(options::parse(_countof(argv), argv) == std::make_tuple(Order::descending, Filter::unique, Case::sensitive, (char *) "input"));
	}

	SECTION("bad option and file")
	{
		char * argv[] = { "line-sort","-dsfadsc","input" };
		REQUIRE_FALSE(options::parse(_countof(argv), argv).has_value());
	}

	SECTION("2 bad option")
	{
		char * argv[] = { "line-sort","-dsfadsc","-input" };
		REQUIRE_FALSE(options::parse(_countof(argv), argv).has_value());
	}

	SECTION("2 bad option and file")
	{
		char * argv[] = { "line-sort","-ri","-ur","input" };
		REQUIRE_FALSE(options::parse(_countof(argv), argv).has_value());
	}

	SECTION("1. patology case multiple -r")
	{
		char * argv[] = { "line-sort","-r","-r" };
		REQUIRE(options::parse(_countof(argv), argv) == std::make_tuple(Order::descending, Filter::all, Case::sensitive, (char *) "-r"));
	}


	SECTION("2. patology case multiple -r")
	{
		char * argv[] = { "line-sort","-r","-r","input" };
		REQUIRE_FALSE(options::parse(_countof(argv), argv).has_value());
	}

	SECTION("first argument")
	{
		char * argv[] = { "line-sort","-r","-r","input" };
		REQUIRE_FALSE(options::parse(_countof(argv), argv).has_value());
	}
}

namespace
{
	namespace data
	{
		std::istringstream empty { R"()" };
		std::istringstream one_char { R"( )" };
		std::istringstream one_line { R"(
)" };
		std::istringstream numbered { R"(1
3
9
4
5
2
)" };
		std::istringstream pismenka{ R"(C
z
a
B

b
A
a
)" };

	}
}

TEST_CASE("Sorting")
{
	SECTION("ascending")
	{
		//std::ostringstream output {};

		//REQUIRE(sort::process(Order::ascending, Filter::all, Case::sensitive, data::empty, output) == true);
		//REQUIRE(output.str() == "");

		//output.str("");
		//REQUIRE(sort::process(Order::ascending, Filter::all, Case::sensitive, data::one_char, output) == true);
		//REQUIRE(output.str() == " \n");

		//output.str("");
		//REQUIRE(sort::process(Order::ascending, Filter::all, Case::sensitive, data::one_line, output) == true);
		//REQUIRE(output.str() == "\n");

		//output.str("");
		//REQUIRE(sort::process(Order::ascending, Filter::all, Case::sensitive, data::numbered, output) == true);
		//REQUIRE(output.str() == "1\n2\n3\n4\n5\n9\n");

		//output.str("");
		//REQUIRE(sort::process(Order::ascending, Filter::all, Case::sensitive, data::pismenka, output) == true);
		//REQUIRE(output.str() == "\nA\nB\nC\na\na\nb\nz\n");
	}

	SECTION("ascending - unique")
	{
		//std::ostringstream output{};

		//REQUIRE(sort::process(Order::ascending, Filter::unique, Case::sensitive, data::empty, output) == true);
		//REQUIRE(output.str() == "");

		//output.str("");
		//REQUIRE(sort::process(Order::ascending, Filter::unique, Case::sensitive, data::one_char, output) == true);
		//REQUIRE(output.str() == " \n");

		//output.str("");
		//REQUIRE(sort::process(Order::ascending, Filter::unique, Case::sensitive, data::one_line, output) == true);
		//REQUIRE(output.str() == "\n");

		//output.str("");
		//REQUIRE(sort::process(Order::ascending, Filter::unique, Case::sensitive, data::numbered, output) == true);
		//REQUIRE(output.str() == "1\n2\n3\n4\n5\n9\n");

		//output.str("");
		//REQUIRE(sort::process(Order::ascending, Filter::unique, Case::sensitive, data::pismenka, output) == true);
		//REQUIRE(output.str() == "\nA\nB\nC\na\nb\nz\n");

	}

	SECTION("ascending - unique - ignore case")
	{
		//std::ostringstream output{};

		//REQUIRE(sort::process(Order::ascending, Filter::unique, Case::ignore, data::empty, output) == true);
		//REQUIRE(output.str() == "");

		//output.str("");
		//REQUIRE(sort::process(Order::ascending, Filter::unique, Case::ignore, data::one_char, output) == true);
		//REQUIRE(output.str() == " \n");

		//output.str("");
		//REQUIRE(sort::process(Order::ascending, Filter::unique, Case::ignore, data::numbered, output) == true);
		//REQUIRE(output.str() == "1\n2\n3\n4\n5\n9\n");

		//output.str("");
		//REQUIRE(sort::process(Order::ascending, Filter::unique, Case::ignore, data::pismenka, output) == true);
		//REQUIRE(output.str() == "\nA\na\nB\nb\nC\nz\n");

	}

	SECTION("descending")
	{
		//std::ostringstream output {};

		//REQUIRE(sort::process(Order::descending, Filter::all, Case::sensitive, data::empty, output) == true);
		//REQUIRE(output.str() == "");

		//output.str("");
		//REQUIRE(sort::process(Order::descending, Filter::all, Case::sensitive, data::one_char, output) == true);
		//REQUIRE(output.str() == " \n");

		//output.str("");
		//REQUIRE(sort::process(Order::descending, Filter::all, Case::sensitive, data::one_line, output) == true);
		//REQUIRE(output.str() == "\n");

		//output.str("");
		//REQUIRE(sort::process(Order::descending, Filter::all, Case::sensitive, data::numbered, output) == true);
		//REQUIRE(output.str() == "9\n5\n4\n3\n2\n1\n");

		//output.str("");
		//REQUIRE(sort::process(Order::descending, Filter::all, Case::sensitive, data::pismenka, output) == true);
		//REQUIRE(output.str() == "z\nb\na\na\nC\nB\nA\n\n");

	}

	SECTION("descending - unique")
	{
		//std::ostringstream output{};

		//REQUIRE(sort::process(Order::descending, Filter::unique, Case::sensitive, data::empty, output) == true);
		//REQUIRE(output.str() == "");

		//output.str("");
		//REQUIRE(sort::process(Order::descending, Filter::unique, Case::sensitive, data::one_char, output) == true);
		//REQUIRE(output.str() == " \n");

		//output.str("");
		//REQUIRE(sort::process(Order::descending, Filter::unique, Case::sensitive, data::one_line, output) == true);
		//REQUIRE(output.str() == "\n");

		//output.str("");
		//REQUIRE(sort::process(Order::descending, Filter::unique, Case::sensitive, data::numbered, output) == true);
		//REQUIRE(output.str() == "9\n5\n4\n3\n2\n1\n");

		//output.str("");
		//REQUIRE(sort::process(Order::descending, Filter::unique, Case::sensitive, data::pismenka, output) == true);
		//REQUIRE(output.str() == "z\nb\na\nC\nB\nA\n\n");

	}

	SECTION("descending - unique - ignore case")
	{
		std::ostringstream output{};

		REQUIRE(sort::process(Order::descending, Filter::unique, Case::ignore, data::empty, output) == true);
		REQUIRE(output.str() == "");

		output.str("");
		REQUIRE(sort::process(Order::descending, Filter::unique, Case::ignore, data::one_char, output) == true);
		REQUIRE(output.str() == " \n");

		output.str("");
		REQUIRE(sort::process(Order::descending, Filter::unique, Case::ignore, data::one_line, output) == true);
		REQUIRE(output.str() == "\n");

		output.str("");
		REQUIRE(sort::process(Order::descending, Filter::unique, Case::ignore, data::numbered, output) == true);
		REQUIRE(output.str() == "9\n5\n4\n3\n2\n1\n");

		output.str("");
		REQUIRE(sort::process(Order::descending, Filter::unique, Case::ignore, data::pismenka, output) == true);
		REQUIRE(output.str() == "z\nC\nb\nB\na\nA\n\n");
	}
}

