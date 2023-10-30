#ifndef FLAG_HPP
# define FLAG_HPP

#include <cstdlib>
#include <string>
#include <list>

class Client;

class Flag {
	private:
		static struct s_flag	flags[];
		bool					_p;
		bool					_s;
		bool					_i;
		bool					_t;
		bool					_n;
		bool					_m;
		size_t					_l;
		std::string				_b;
		bool					_v;

	public:
		Flag(void);
		~Flag(void);

		void	use(std::list<std::string> command, Client* client);

		void	o(std::list<std::string> command, Client* client);
		void	p(std::list<std::string> command, Client* client);
		void	s(std::list<std::string> command, Client* client);
		void	i(std::list<std::string> command, Client* client);
		void	t(std::list<std::string> command, Client* client);
		void	n(std::list<std::string> command, Client* client);
		void	m(std::list<std::string> command, Client* client);
		void	l(std::list<std::string> command, Client* client);
		void	b(std::list<std::string> command, Client* client);
		void	v(std::list<std::string> command, Client* client);
		void	k(std::list<std::string> command, Client* client);

		bool		isPrivate(void) { return (_p); }
		bool		isInviteOnly(void) { return (_i); }
		bool		isTopicOperatorOnly(void) { return (_t); }
		size_t		getLimit(void) { return (_l); }
		std::string	getMask(void) { return (_b); }
		bool		isModeratorSpeakOnly(void) { return (_v); }
		bool		isExternNoSpeak(void) { return (_n); }
};

typedef struct s_flag {
	std::string	oper;
	void		(Flag::*f)(std::list<std::string>, Client*);
}				t_flag;

#endif
