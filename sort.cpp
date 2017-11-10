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

void setSame(std::vector<std::string> & vekt) {
	for (int i = 0; i < vekt.size(); i++) {
		for (int j = i; j < vekt.size(); j++) {
			if (i != j) {
				std::string vi;
				std::string vj;
				vi = vekt[i];
				vj = vekt[j];
				std::transform(vi.begin(), vi.end(), vi.begin(), ::tolower);
				std::transform(vj.begin(), vj.end(), vj.begin(), ::tolower);
				if (vi==vj) {
					vekt[i] = vekt[j];
				}
			}
		}
	}
}

void filterWhiteSpace(std::vector<std::string> & vekt) {
	for (std::vector<std::string>::iterator i = vekt.begin(); i != vekt.end();) {
		bool emp = true;
		for (int j = 0; j < (*i).length(); j++) {
			char c = (*i)[j];
			if (!std::isspace(c)) {
				emp = false;
			}
		}
		if (emp) {
			i=vekt.erase(i);
		}
		else {
			++i;
		}
	}
}

bool sort::process(Order order, Filter filter, Case compare, FilterSpace space ,std::istream & input, std::ostream & output)
{
	std::vector<std::string> lines { std::istream_iterator<Line>(input), std::istream_iterator<Line>() };
	if (!lines.empty()) {
		if (FilterSpace::whitespace == space) {
			filterWhiteSpace(lines);
		}
		if (Case::ignore == compare && Filter::unique == filter) {
			setSame(lines);
		}
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
		//std::copy(lines.begin(), lines.end(), std::ostream_iterator<std::string>(output));
	}
	return true;
}


