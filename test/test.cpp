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

	SECTION("bad option") 
	{
		char * argv[] = {"line-sort","-dsfadsc"};
		REQUIRE(options::parse(_countof(argv), argv) == false);  //este toto kukni, asi nesedi navratova hodnota
	}

	SECTION("bad option and file")
	{
		char * argv[] = { "line-sort","-dsfadsc","input" };
		REQUIRE(options::parse(_countof(argv), argv) == false);
	}

	SECTION("2 bad option")
	{
		char * argv[] = { "line-sort","-dsfadsc","-input" };
		REQUIRE(options::parse(_countof(argv), argv) == false);
	}

	SECTION("bad option and file")
	{
		char * argv[] = { "line-sort","-ri","-ur","input" };
		REQUIRE(options::parse(_countof(argv), argv) == false);
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
	}
}

TEST_CASE("Sorting")
{
	SECTION("ascending")
	{
		std::ostringstream output {};

		REQUIRE(sort::process(Order::ascending, Filter::all, Case::sensitive, data::empty, output) == true);
		REQUIRE(output.str() == "");

		//output.str("");
		//REQUIRE(sort::process(Order::ascending, Filter::all, Case::sensitive, data::one_char, output) == true);
		//REQUIRE(output.str() == " \n");

		//output.str("");
		//REQUIRE(sort::process(Order::ascending, Filter::all, Case::sensitive, data::one_line, output) == true);
		//REQUIRE(output.str() == "\n");

		//output.str("");
		//REQUIRE(sort::process(Order::ascending, Filter::all, Case::sensitive, data::numbered, output) == true);
		//REQUIRE(output.str() == "1\n2\n3\n4\n5\n9\n");
	}

	SECTION("ascending - unique")
	{
	}

	SECTION("ascending - unique - ignore case")
	{
	}

	SECTION("descending")
	{
	}

	SECTION("descending - unique")
	{
	}

	SECTION("descending - unique - ignore case")
	{
	}
}

