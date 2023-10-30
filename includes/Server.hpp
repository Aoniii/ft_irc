#ifndef SERVER_HPP
# define SERVER_HPP

# define MAX_EVENTS 100
# define BUFFER_SIZE 4096

#include <sys/epoll.h>
#include <algorithm>
#include "Client.hpp"
#include "Channel.hpp"

class Server {
	private:
		std::list<Client>	clients;
		std::list<Channel>	channels;
		int					server_fd;
		int					epfd;

	public:
		Server(int port);
		~Server(void);

		std::list<Client>	getClients(void);
		std::list<Channel>	getChannels(void);

		const int&	getServerFd(void) const;
		int			addClient(void);
		void		addChannel(Channel channel);
		void		waitEvent(void);
		void		giveCommand(std::string	buff, int fd);
		Client*		findClient(int fd);
		Client*		findUser(std::string name);
		Channel* 	findChannel(std::string name);
		bool		haveUser(std::string name);
		bool		haveChannel(std::string name);

		void		broadcast(std::string message);

		void		quit(int fd);
		
		static bool	run;
};

#endif
