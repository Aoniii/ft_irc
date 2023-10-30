#include "Server.hpp"
#include "utils.hpp"

Server::Server(int port) {
	struct epoll_event	event;
	struct sockaddr_in	address;
	int 				option = 1;
	
	this->server_fd = -1;
	this->epfd = -1;

	//create socket server
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		std::cerr << "cannot create socket" << std::endl;
		return;
	}

	memset((char *)&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	address.sin_port = htons(port);

	//to reuse same port
	if (setsockopt(server_fd , SOL_SOCKET, SO_REUSEADDR, &option, sizeof(int)) < 0)
		std::cerr << "Error setsockopt" << std::endl;

	//bind server_fd
	if (bind(server_fd,(struct sockaddr *)&address,sizeof(address)) < 0) {
		std::cerr << "bind failed" << std::endl;
		Server::run = false;
		return;
	}

	//server listen clients connection
	listen(server_fd, 10);
	//create epoll to manage multiple clients
	epfd = epoll_create1(0);

	if (epfd < 0) {
		std::cerr << "Error epoll_create1(0)!" << std::endl;
		return ;
	}

	memset(&event, 0, sizeof(struct epoll_event));
	event.events = EPOLLIN | EPOLLET;
	event.data.fd = server_fd;

	//add server fd to epoll
	if (epoll_ctl(epfd, EPOLL_CTL_ADD, server_fd, &event) != 0) {
		std::cerr << "Error epol_ctl add!" << std::endl;
		return ;
	}
}

std::list<Client>	Server::getClients(void) {
	return (this->clients);
}

std::list<Channel>	Server::getChannels(void) {
	return (this->channels);
}

Client*	Server::findClient(int fd) {
	std::list<Client>::iterator	it;
	std::list<Client>::iterator	end;

	it = this->clients.begin();
	end = this->clients.end();

	while (it != end) {
		if (it->getClient() == fd) {
			return (&(*it));
		}
		it++;
	}
	return (NULL);
}

Client*	Server::findUser(std::string name) {
	std::list<Client>::iterator	it;
	std::list<Client>::iterator	end;

	it = this->clients.begin();
	end = this->clients.end();

	name = toLower(name);
	while (it != end) {
		if (toLower(it->getNickname()) == name) {
			return (&(*it));
		}
		it++;
	}
	return (NULL);
}

Channel*	Server::findChannel(std::string name) {
	std::list<Channel>::iterator	it;
	std::list<Channel>::iterator	end;

	it = this->channels.begin();
	end = this->channels.end();

	while (it != end) {
		if (it->getName() == name) {
			return (&(*it));
		}
		it++;
	}
	return (NULL);
}

bool	Server::haveUser(std::string name) {
	std::list<Client>::iterator	it;
	std::list<Client>::iterator	end;

	it = this->clients.begin();
	end = this->clients.end();

	name = toLower(name);
	while (it != end) {
		if (toLower(it->getNickname()) == name) {
			return (true);
		}
		it++;
	}
	return (false);
}

bool	Server::haveChannel(std::string name) {
	return (findChannel(name) ? true : false);
}

void	Server::giveCommand(std::string	buff, int fd) {
	Client*	tmp;

	tmp = this->findClient(fd);
	if (tmp)
		tmp->takeCommand(buff);
}

void		Server::waitEvent(void) {
	struct epoll_event	events[MAX_EVENTS];
	struct epoll_event	event;
	char				buff[BUFFER_SIZE];
	int					nfds;

	while (run)  {
		memset(&events, 0, sizeof(struct epoll_event) * MAX_EVENTS);
		//wait events from epoll fds
    	nfds = epoll_wait(epfd, events, MAX_EVENTS, 0);
		if (nfds == 0)                                                                                                                                                  
			continue;
    	for (int n = 0; n < nfds; n++) {
			//mean new client ask for a connection
        	if (events[n].data.fd == server_fd) {
            	int client = this->addClient();
				memset(&event, 0, sizeof(struct epoll_event));
            	event.events = EPOLLIN | EPOLLET;
            	event.data.fd = client;
            	
				//add client fd to epoll
				if (epoll_ctl(epfd, EPOLL_CTL_ADD, client, &event) == -1) {
                	std::cerr << "epoll set insertion error: fd= " << client << std::endl;
            		return;
            	}
        	}
			//mean this is a msg from an existing client
			else {
				memset(&buff, 0, sizeof(char) * BUFFER_SIZE);
				//catch msg in buffer
				if (recv(events[n].data.fd, buff, BUFFER_SIZE, 0) <= 0)
					findClient(events[n].data.fd)->quit();
				else
					this->giveCommand(buff, events[n].data.fd);
				//std::cout << buff << std::flush;
        	}
    	}
	}
}

const int& Server::getServerFd(void) const {
	return (server_fd);	
}

int	Server::addClient(void) {
	Client new_client(this, server_fd);

	clients.push_back(new_client);
	return (new_client.getClient());
}

void	Server::addChannel(Channel channel) {
	this->channels.push_back(channel);
}

Server::~Server(void) {

	for (std::list<Client>::iterator it = clients.begin(); it != clients.end(); it++)
		if (it->getClient() != 0)
			it->closeFd();

	if (server_fd != -1)
		close(server_fd);
	if (epfd != -1)
		close(epfd);

	for (std::list<Channel>::iterator it = channels.begin(); it != channels.end(); it++)
		if (it->getFlag())
			delete it->getFlag();
}

void	Server::broadcast(std::string message) {
	for (std::list<Client>::iterator it = clients.begin(); it != clients.end(); it++) {
		if ((*it).isAuthenticate())
			(*it).send(message);
	}
}

void	Server::quit(int fd) {
	std::list<Channel>::iterator	it;
	std::list<Channel>::iterator	end;

	it = this->channels.begin();
	end = this->channels.end();

	while (it != end) {
		if (!it->haveUser(fd)) {
			it++;
			continue;
		}
		if (it->getSuperOperator() == fd) {
			it->send("[\e[32mINFO\e[0m] The channel " + it->getName() + " is delete.");
			std::cout << "[\e[32mINFO\e[0m] The channel " + it->getName() + " is delete." << std::endl;
			it->setName("");
			it++;
			continue;
		} else if (it->haveOperator(fd)) {
			it->getOperators().remove(fd);
		}
		it->removeUser(fd);
		it++;
	}
}

bool Server::run = true;
