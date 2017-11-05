#include "sort.h"

#include <string>
#include <iterator>
#include <vector>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <iostream>
#include <fstream>
#include <ostream>
#include <set>
#include <utility>

namespace
{
	struct Line : public std::string {};

	std::istream & operator >> (std::istream & is, Line & line)
	{
		return std::getline(is, line);
	}
}

bool compareNoCase(std::string first, std::string second)
{
	int i = 0;
	while ((i < first.length()) && (i < second.length()))
	{
		if (tolower(first[i]) < tolower(second[i])) return true;
		else if (tolower(first[i]) > tolower(second[i])) return false;
		i++;
	}

	if (first.length() < second.length()) return true;
	else return false;
}


bool sort::process(Order order, Filter filter, Case compare, std::istream & input, std::ostream & output)
{
	std::vector<std::string> lines { std::istream_iterator<Line>(input), std::istream_iterator<Line>() };

	if (!lines.empty()) {
		if (Filter::unique == filter) {
			std::set<std::string> s(lines.begin(), lines.end());
			lines.assign(s.begin(), s.end());
		}

		if (Case::ignore == compare) {
			std::sort(lines.begin(), lines.end(),compareNoCase);
		}
		else{
			std::sort(lines.begin(), lines.end());
		}

		if (Order::descending == order) {
			std::reverse(lines.begin(),lines.end());
		}
	
		for (auto i = lines.begin(); i != lines.end(); ++i) {
			output << *i << std::endl;
		}

		//for (int i = 0; i < lines.size(); i++) {
		//	output << lines[i] << std::endl;
		//	output.flush();
		//}

		//const char delimiter = '\n';
		//for (int i = 0; i < lines.size();i++) {
		//	lines[i] = lines[i] + "\n";
		//	output.write(lines[i].c_str(),lines[i].size());
		//	output << delimiter;
		//}

		//bool write_sep = false;
		//for (const auto& e : lines) {
		//	if (write_sep)
		//		output << delimiter;
		//	else
		//		write_sep = true;
		//	output << e;
		//	std::flush(output);
		//}
		//output << delimiter;
		
		//std::copy(lines.begin(), lines.end(), std::ostream_iterator<std::string>(output));
	}

	return true;
}


