#include "utils.hpp"

template<typename T>
std::string toString(const T& value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

std::list<std::string>	split(std::string str, std::string delimiter) {
	std::list<std::string>	lst;

	std::string token;
	size_t		start = 0;
	size_t		end = 0;
	while (end + 1 != str.length()) {
		start = str.find_first_not_of(delimiter, end);
		end = str.find_first_of(delimiter, start);
		if (end >= str.length())
			break;
		if (str.at(start) == ':')
			end = str.size() - 1;
		else
		{
			end = str.find_first_of(delimiter, start);
			if (end >= str.length())
				break;
		}
		token = str.substr(start, end - start);
		lst.push_back(token);
	}
	return (lst);
}

std::string	get(std::list<std::string> lst, size_t index) {
	std::list<std::string>::iterator	it = lst.begin();
	std::advance(it, index);
	return (*it);
}

bool	isFormat(std::string name, std::string format, size_t start) {
	for (size_t i = start; i < name.size(); i++) {
		if (format.find(name.at(i)) == std::string::npos)
			return (false);
	}
	return (true);
}

std::string	toLower(std::string str) {
	std::string	out = "";

	for (size_t i = 0; i < str.size(); i++) {
		if (str.at(i) >= 'A' && str.at(i) <= ']')
			out += (str.at(i) + 32);
		else
			out += str.at(i);
	}
	return (out);
}

bool	isCorrectFlag(std::string str) {
	size_t		i = 0;
	std::string	format = "opsitnmlbvk";

	if (str.at(0) == '+' || str.at(0) == '-')
		i++;
	while (i < str.size()) {
		if (format.find(str.at(i)) == std::string::npos)
			return (false);
		i++;
	}
	return (true);
}
