#ifndef CLIENT_HPP
# define CLIENT_HPP

#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <string>
#include <unistd.h>
#include <list>
#include "Command.hpp"
#include "Channel.hpp"

class Server;

class Client {
	private:
		int						fd;
		Server*					server;
		std::string				command;
		std::string				nickname;
		std::string				realname;
		bool					authenticate;
	
	public:
		Client(Server* server, int server_fd);
		~Client(void);

		Server*	getServer(void);

		const int&	getClient(void) const;
		void		closeFd(void);
		void		takeCommand(std::string str);
		void		quit(void);

		void	setNickname(std::string nickname);
		void	setRealname(std::string realname);
		void	setAuthenticate(void);

		const std::string&	getNickname(void) const;
		const std::string&	getRealname(void) const;
		const bool&			isAuthenticate(void) const;

		void	send(std::string str);

		bool	operator==(const Client &client) const;
};

#endif
