#include <signal.h> 
#include "Server.hpp"
#include "Command.hpp"

void	signal_handler(int signal) {
	(void) signal;
	Server::run = false;
}

int main(int ac, char **av) {
	if (ac != 3) {
		std::cerr << "[\e[31mERROR\e[0m] Invalid number of arguments !" << std::endl;
		std::cerr << "Usage: ./ircserv <port> <password>" << std::endl;
		return (1);
	}
	std::string	s(av[1]);
	for (size_t i = 0; i < s.length(); i++) {
		if (s.at(i) < '0' || s.at(i) > '9') {
			std::cerr << "[\e[31mERROR\e[0m] Port isn't number  !" << std::endl;
			return (1);
		}
	}
	int	port = std::atoi(av[1]);
	if (port < 1024 || port > 65535) {
		std::cerr << "[\e[31mERROR\e[0m] Invalid port number !" << std::endl;
		std::cerr << "Range: 1024 -> 65535" << std::endl;
		return (1);
	}
	size_t	end = std::string(av[2]).find_first_of(" \t\n\v\f\r", 0);
	if (end < std::string(av[2]).length())
	{
		std::cerr << "[\e[31mERROR\e[0m] Invalid password !" << std::endl;
		std::cerr << "Contains whitespace" << std::endl;
		return (1);
	}
	signal(SIGINT, signal_handler);
	Command::password = std::string(av[2]);
	Server(port).waitEvent();
	return (0);
}
