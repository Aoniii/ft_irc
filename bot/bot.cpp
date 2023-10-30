#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <signal.h>
#include "../includes/utils.hpp"

void	signal_handler(int signal) {
	(void) signal;
	exit(0);
}

int main(int ac, char **av)
{
	struct sockaddr_in	address;
	int 				bot_fd;
	static std::string			cmd("ALL ");

	signal(SIGINT, signal_handler);
	if (ac != 3) {
		std::cerr << "[\e[31mERROR\e[0m] Invalid number of arguments !" << std::endl;
		std::cerr << "Usage: ./jacob <ip> <port>" << std::endl;
		return (1);
	}

	std::string	s(av[2]);
	for (size_t i = 0; i < s.length(); i++) {
		if (s.at(i) < '0' || s.at(i) > '9') {
			std::cerr << "[\e[31mERROR\e[0m] Port isn't number  !" << std::endl;
			return (1);
		}
	}
	int	port = std::atoi(av[2]);
	if (port < 1024 || port > 65535) {
		std::cerr << "[\e[31mERROR\e[0m] Invalid port number !" << std::endl;
		std::cerr << "Range: 1024 -> 65535" << std::endl;
		return (1);
	}

	cmd += JACOB;
	cmd += " :Date is ";
	if ((bot_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		std::cerr << "Error: cannot create socket" << std::endl;
		return 1;
	}

	memset((char *)&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr(av[1]);
	address.sin_port = htons(atoi(av[2]));

	if (connect(bot_fd ,(struct sockaddr*)&address,sizeof(address)) < 0){
   		std::cerr << "Error: cannot connect bot to server" << std::endl;
		return 1;
	}
	time_t now;
    struct tm * tm;;
    char date[15];

	while (1){
    	
		now = time(NULL);
		tm = localtime(&now);
		strftime(date, sizeof(date), "%F", tm);
		cmd += date;
		cmd += '\n';
		if (send(bot_fd , cmd.c_str(), cmd.size(), 0) < 0){
   			std::cerr << "Error: cannot send a string to server" << std::endl;
			return 1;
		}
		std::cout << cmd << std::endl;
		cmd = cmd.substr(0, 14 + strlen(JACOB));
		sleep(6);
	}

}
