#include "Flag.hpp"
#include "utils.hpp"
#include "Client.hpp"

t_flag Flag::flags[] = {{"o", &Flag::o}, {"p", &Flag::p}, {"s", &Flag::s},
{"i", &Flag::i}, {"t", &Flag::t}, {"n", &Flag::n}, {"m", &Flag::m},
{"l", &Flag::l}, {"b", &Flag::b}, {"v", &Flag::v}, {"k", &Flag::k}};

Flag::Flag(void) {
	_p = false;
	_s = false;
	_i = false;
	_t = true;
	_n = true;
	_m = false;
	_l = 200;
	_b = "";
	_v = false;
}

Flag::~Flag(void) {}

void	Flag::use(std::list<std::string> command, Client* client) {
	for (int i = 0; i < 11; i++) {
		if (get(command, 2).find(this->flags[i].oper.at(0)) != std::string::npos)
			(this->*(flags[i].f))(command, client);
	}
}

void	Flag::o(std::list<std::string> command, Client* client) {
	if (command.size() < 5) {
		client->send("[\e[33mUSAGE\e[0m] MODE <channel> {[+|-]|o|p|s|i|t|n|m|l|b|v|k} [<limit>] [<user>] [<ban mask>] [<password>]");
		return;
	}
	if (!client->getServer()->haveUser(get(command, 4))) {
		client->send("[\e[31mERROR\e[0m] Invalid user !");
		return;
	}
	int	target = client->getServer()->findUser(get(command, 4))->getClient();
	if (!client->getServer()->findChannel(get(command, 1))->haveUser(target)) {
		client->send("[\e[31mERROR\e[0m] This user isn't on this channel !");
		return;
	}
	if (target == client->getServer()->findChannel(get(command, 1))->getSuperOperator()) {
		client->send("[\e[31mERROR\e[0m] This user is the main operator !");
		return;
	}
	if (get(command, 2).at(0) == '+') {
		if (client->getServer()->findChannel(get(command, 1))->haveOperator(target)) {
			client->send("[\e[31mERROR\e[0m] This user are already an operator !");
			return ;
		}
		client->getServer()->findChannel(get(command, 1))->addOperator(target);
		client->send("[\e[32mINFO\e[0m] " + get(command, 4) + " is an operator now.");
	} else if (get(command, 2).at(0) == '-') {
		if (!client->getServer()->findChannel(get(command, 1))->haveOperator(target)) {
			client->send("[\e[31mERROR\e[0m] This user are not an operator !");
			return ;
		}
		client->getServer()->findChannel(get(command, 1))->removeOperator(target);
		client->send("[\e[32mINFO\e[0m] " + get(command, 4) + " is no longer an operator.");
	} else {
		if (client->getServer()->findChannel(get(command, 1))->haveOperator(target)) {
			client->getServer()->findChannel(get(command, 1))->removeOperator(target);
			client->send("[\e[32mINFO\e[0m] " + get(command, 4) + " is no longer an operator.");
		} else {
			client->getServer()->findChannel(get(command, 1))->addOperator(target);
			client->send("[\e[32mINFO\e[0m] " + get(command, 4) + " is an operator now.");
		}
	}
}

void	Flag::p(std::list<std::string> command, Client* client) {
	if (get(command, 2).at(0) == '+') {
		if (this->_p) {
			client->send("[\e[31mERROR\e[0m] This channel is already private !");
			return;
		}
		client->send("[\e[32mINFO\e[0m] This channel is private now.");
		this->_p = true;
	} else if (get(command, 2).at(0) == '-') {
		if (!this->_p) {
			client->send("[\e[31mERROR\e[0m] This channel is already public !");
			return;
		}
		client->send("[\e[32mINFO\e[0m] This channel is public now.");
		this->_p = false;
	} else {
		if (this->_p) {
			client->send("[\e[32mINFO\e[0m] This channel is public now.");
			this->_p = false;
		} else {
			client->send("[\e[32mINFO\e[0m] This channel is private now.");
			this->_p = true;
		}
	}
}

void	Flag::s(std::list<std::string> command, Client* client) {
	if (get(command, 2).at(0) == '+') {
		if (this->_s) {
			client->send("[\e[31mERROR\e[0m] This channel is already secret !");
			return;
		}
		client->send("[\e[32mINFO\e[0m] This channel is secret now.");
		this->_s = true;
	} else if (get(command, 2).at(0) == '-') {
		if (!this->_s) {
			client->send("[\e[31mERROR\e[0m] This channel is'nt already secret !");
			return;
		}
		client->send("[\e[32mINFO\e[0m] This channel isn't secret now.");
		this->_s = false;
	} else {
		if (this->_s) {
			client->send("[\e[32mINFO\e[0m] This channel isn't secret now.");
			this->_s = false;
		} else {
			client->send("[\e[32mINFO\e[0m] This channel is secret now.");
			this->_s = true;
		}
	}
}

void	Flag::i(std::list<std::string> command, Client* client) {
	if (get(command, 2).at(0) == '+') {
		if (this->_i) {
			client->send("[\e[31mERROR\e[0m] This channel is already invite only !");
			return;
		}
		client->send("[\e[32mINFO\e[0m] This channel is invite only now.");
		this->_i = true;
	} else if (get(command, 2).at(0) == '-') {
		if (!this->_i) {
			client->send("[\e[31mERROR\e[0m] This channel isn't already invite only !");
			return;
		}
		client->send("[\e[32mINFO\e[0m] This channel isn't invite only now.");
		this->_i = false;
	} else {
		if (this->_i) {
			client->send("[\e[32mINFO\e[0m] This channel isn't invite only now.");
			this->_i = false;
		} else {
			client->send("[\e[32mINFO\e[0m] This channel is invite only now.");
			this->_i = true;
		}
	}
}

void	Flag::t(std::list<std::string> command, Client* client) {
	if (get(command, 2).at(0) == '+') {
		if (this->_t) {
			client->send("[\e[31mERROR\e[0m] This channel topic is already editable by operator only !");
			return;
		}
		client->send("[\e[32mINFO\e[0m] This channel topic is editable by operator only now.");
		this->_t = true;
	} else if (get(command, 2).at(0) == '-') {
		if (!this->_t) {
			client->send("[\e[31mERROR\e[0m] This channel topic is already editable by everyone !");
			return;
		}
		client->send("[\e[32mINFO\e[0m] This channel topic is editable by everyone now.");
		this->_t = false;
	} else {
		if (this->_t) {
			client->send("[\e[32mINFO\e[0m] This channel topic is editable by everyone now.");
			this->_t = false;
		} else {
			client->send("[\e[32mINFO\e[0m] This channel topic is editable by operator only now.");
			this->_t = true;
		}
	}
}

void	Flag::n(std::list<std::string> command, Client* client) {
	if (get(command, 2).at(0) == '+') {
		if (this->_n) {
			client->send("[\e[31mERROR\e[0m] This channel have already no message in a channel from customers outside the channel !");
			return;
		}
		client->send("[\e[32mINFO\e[0m] This channel have no message in a channel from customers outside the channel now.");
		this->_n = true;
	} else if (get(command, 2).at(0) == '-') {
		if (!this->_n) {
			client->send("[\e[31mERROR\e[0m] This channel have already message in a channel from customers outside the channel !");
			return;
		}
		client->send("[\e[32mINFO\e[0m] This channel have message in a channel from customers outside the channel now.");
		this->_n = false;
	} else {
		if (this->_n) {
			client->send("[\e[32mINFO\e[0m] This channel have message in a channel from customers outside the channel now.");
			this->_n = false;
		} else {
			client->send("[\e[32mINFO\e[0m] This channel have no message in a channel from customers outside the channel now.");
			this->_n = true;
		}
	}
}

void	Flag::m(std::list<std::string> command, Client* client) {
	if (get(command, 2).at(0) == '+') {
		if (this->_m) {
			client->send("[\e[31mERROR\e[0m] This channel is already moderate !");
			return;
		}
		client->send("[\e[32mINFO\e[0m] This channel is moderate now.");
		this->_m = true;
	} else if (get(command, 2).at(0) == '-') {
		if (!this->_m) {
			client->send("[\e[31mERROR\e[0m] This channel isn't already moderate !");
			return;
		}
		client->send("[\e[32mINFO\e[0m] This channel isn't moderate now.");
		this->_m = false;
	} else {
		if (this->_m) {
			client->send("[\e[32mINFO\e[0m] This channel isn't moderate now.");
			this->_m = false;
		} else {
			client->send("[\e[32mINFO\e[0m] This channel is moderate now.");
			this->_m = true;
		}
	}
}

void	Flag::l(std::list<std::string> command, Client* client) {
	if (command.size() < 4) {
		client->send("[\e[33mUSAGE\e[0m] MODE <channel> {[+|-]|o|p|s|i|t|n|m|l|b|v|k} [<limit>] [<user>] [<ban mask>] [<password>]");
		return;
	}
	if (!isFormat(get(command, 3), "0123456789", 0)) {
		client->send("[\e[31mERROR\e[0m] Invalid argument !");
		return;
	}
	size_t	i = (size_t) atoi(get(command, 3).c_str());
	if (i < 1 || i > 200) {
		client->send("[\e[31mERROR\e[0m] Invalid argument !");
		return;
	}
	if (client->getServer()->findChannel(get(command, 1))->getUsers().size() > i) {
		client->send("[\e[31mERROR\e[0m] There are too many people in the channel to limit a " + get(command, 3) + " !");
		return;
	}
	this->_l = i;
	client->send("[\e[32mINFO\e[0m] This channel has been resized.");
}

void	Flag::b(std::list<std::string> command, Client* client) {
	if (command.size() < 6) {
		client->send("[\e[33mUSAGE\e[0m] MODE <channel> {[+|-]|o|p|s|i|t|n|m|l|b|v|k} [<limit>] [<user>] [<ban mask>] [<password>]");
		return;
	}
	this->_b = get(command, 5);
}

void	Flag::v(std::list<std::string> command, Client* client) {
	if (get(command, 2).at(0) == '+') {
		if (this->_v) {
			client->send("[\e[31mERROR\e[0m] This channel is already only moderator can speak !");
			return;
		}
		client->send("[\e[32mINFO\e[0m] This channel is only moderator can speak now.");
		this->_v = true;
	} else if (get(command, 2).at(0) == '-') {
		if (!this->_v) {
			client->send("[\e[31mERROR\e[0m] This channel is already everyone can speak ! !");
			return;
		}
		client->send("[\e[32mINFO\e[0m] This channel is everyone can speak now.");
		this->_v = false;
	} else {
		if (this->_v) {
			client->send("[\e[32mINFO\e[0m] This channel is everyone can speak now.");
			this->_v = false;
		} else {
			client->send("[\e[32mINFO\e[0m] This channel is only moderator can speak now.");
			this->_v = true;
		}
	}
}

void	Flag::k(std::list<std::string> command, Client* client) {
	if (command.size() < 7) {
		client->send("[\e[33mUSAGE\e[0m] MODE <channel> {[+|-]|o|p|s|i|t|n|m|l|b|v|k} [<limit>] [<user>] [<ban mask>] [<password>]");
		return;
	}
	client->getServer()->findChannel(get(command, 1))->setPassword(get(command, 6));
}

