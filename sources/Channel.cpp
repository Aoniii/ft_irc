#include "Client.hpp"

Channel::Channel(std::string name, std::string password, int op) {
	std::cout << "[\e[32mINFO\e[0m] New channel created (" + name + ")." << std::endl;
	this->name = name;
	this->password = password;
	this->superOperator = op;
	this->topic = "";
	this->flag = new Flag();
}

Channel::~Channel() {}

void	Channel::addUser(Client* client) {
	this->users.push_back(client->getClient());
}

void	Channel::removeUser(int fd) {
	this->users.remove(fd);
}

void	Channel::send(std::string message) {
	for (std::list<int>::iterator it = this->users.begin(); it != this->users.end(); it++) {
		write(*it, (message + "\n").c_str(), message.length() + 1);
	}
}

bool	Channel::haveUser(int fd) {
	std::list<int>::iterator	it;
	std::list<int>::iterator	end;

	it = this->users.begin();
	end = this->users.end();

	while (it != end) {
		if (*it == fd)
			return (true);
		it++;
	}
	return (false);
}

bool	Channel::operator==(const Channel &channel) const {
	return (channel.getName() != this->name);
}

std::string	Channel::getTopic(void) {
	return (this->topic);
}

void	Channel::setTopic(std::string topic) {
	this->topic = topic;
}

bool	Channel::haveOperator(int fd) {
	if (fd == this->superOperator)
		return (true);

	std::list<int>::iterator	it;
	std::list<int>::iterator	end;

	it = this->operators.begin();
	end = this->operators.end();

	while (it != end) {
		if (*it == fd)
			return (true);
		it++;
	}
	return (false);
}

void	Channel::addOperator(int fd) {
	if (!haveOperator(fd))
		this->operators.push_back(fd);
}

void	Channel::removeOperator(int fd) {
	if (fd == this->superOperator)
		return;
	if (haveOperator(fd))
		this->operators.remove(fd);
}
