#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include <string>
#include <list>
#include "Flag.hpp"

class Client;

class Channel {
	private:
		std::list<int>	users;
		std::string		name;
		std::string		password;

		int				superOperator;
		std::list<int>	operators;
		Flag*			flag;

		std::string		topic;

	public:
		Channel(std::string name, std::string password, int op);
		~Channel(void);

		std::list<int>	getUsers() { return (users); }
		std::string		getName() const { return (name); }
		void			setName(std::string s) { this->name = s; }
		std::string		getPassword() { return (password); }

		void			setPassword(std::string password) { this->password = password; }

		int				getSuperOperator() { return (superOperator); }
		std::list<int>	getOperators() { return (operators); }
		Flag*			getFlag() { return (flag); }

		std::string		getTopic(void);
		void			setTopic(std::string topic);

		void	addUser(Client* client);
		void	removeUser(int fd);
		void	send(std::string message);
		bool	haveUser(int fd);

		bool	haveOperator(int fd);
		void	addOperator(int fd);
		void	removeOperator(int fd);

		bool	operator==(const Channel &channel) const;
};

#endif
