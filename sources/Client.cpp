#include "Client.hpp"
#include "Server.hpp"
#include "Channel.hpp"

Client::Client(Server* server, int server_fd) {
	struct sockaddr_in	address;
	socklen_t 			len;

	len = 0;
	this->server = server;
	this->nickname = "";
	this->realname = "";
	this->authenticate = false;
	memset(&address, 0, sizeof(struct sockaddr));
	//accept a client connection to server
	fd = accept(server_fd ,(struct sockaddr*)&address, &len);
	std::cout << "[\e[32mINFO\e[0m] New connection." << std::endl;
}

Server*	Client::getServer(void) {
	return (this->server);
}

const int&	Client::getClient(void) const {
	return (fd);
}

void		Client::takeCommand(std::string str) {
	Command	exec_command;
	size_t	sep;

	command += str;
	sep = command.find_first_of("\n", 0);
	while (command.size() && sep != std::string::npos) {
		exec_command.parseCommand(command.substr(0, sep + 1), this);
		command.erase(0, sep + 1);
		sep = command.find_first_of("\n");
	}
}

void	Client::closeFd(void) {
	close(fd);
}

void	Client::quit(void) {
	this->getServer()->quit(this->fd);
	this->nickname = "";
	close(this->fd);
	this->fd = 0;
}

Client::~Client(void) {}

void	Client::setNickname(std::string nickname) {this->nickname = nickname;}
void	Client::setRealname(std::string realname) {this->realname = realname;}
void	Client::setAuthenticate(void) {authenticate = true;}

const std::string&	Client::getNickname(void) const {return (nickname);}
const std::string&	Client::getRealname(void) const {return (realname);}
const bool&			Client::isAuthenticate(void) const {return (authenticate);}

void	Client::send(std::string str) {
	write(this->fd, (str + "\n").c_str(), str.length() + 1);
}

bool	Client::operator==(const Client &client) const {
	return (client.getClient() != this->fd);
}
