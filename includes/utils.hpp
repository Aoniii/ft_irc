#ifndef UTILS_HPP
# define UTILS_HPP

#include <string>
#include <list>
#include <algorithm>
#include <sstream>

#define JACOB "18b81a00-0d76-4cd2-9ef1-39441b60eb9a"

template<typename T>
std::string				toString(const T& value);
std::list<std::string>	split(std::string str, std::string delimiter);
std::string				get(std::list<std::string> lst, size_t index);
bool					isFormat(std::string name, std::string format, size_t start);
std::string				toLower(std::string str);
bool					isCorrectFlag(std::string str);

#endif
