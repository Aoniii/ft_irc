#ifndef COMMAND_HPP
# define COMMAND_HPP

#include <iostream>
#include "Client.hpp"
#include "Server.hpp"
#include "utils.hpp"

class Client;
class Command;

typedef struct s_command {
	std::string	oper;
	void		(Command::*f)(std::list<std::string>, Client*);
}				t_command;

class Command {
	private:
		static t_command	commands[];

	public:
		Command(void);
		~Command(void);

		void	parseCommand(std::string input_command, Client* client);

		void	Pass(std::list<std::string> command, Client* client);
		void	Nick(std::list<std::string> command, Client* client);
		void	User(std::list<std::string> command, Client* client);
		void	Privmsg(std::list<std::string> command, Client* client);
		void	Join(std::list<std::string> command, Client* client);
		void	Part(std::list<std::string> command, Client* client);
		void	Notice(std::list<std::string> command, Client* client);
		void	Quit(std::list<std::string> command, Client* client);
		void	Kick(std::list<std::string> command, Client* client);
		void	Mode(std::list<std::string> command, Client* client);
		void	Invite(std::list<std::string> command, Client* client);
		void	Topic(std::list<std::string> command, Client* client);
		void	All(std::list<std::string> command, Client* client);

		static std::string	password;
};

#endif
