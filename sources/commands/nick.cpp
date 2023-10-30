#include "Command.hpp"

/**
 * Command: NICK
 * Usage: NICK <nickname>
 * NICK message is used to give user a nickname or change the previous one.
 */
void	Command::Nick(std::list<std::string> command, Client* client) {
	if (!client->isAuthenticate()) {
		client->send("[\e[31mERROR\e[0m] Please enter the password !");
		client->send("[\e[33mUSAGE\e[0m] PASS <password>");
		return;
	}
	if (command.size() != 2) {
		client->send("[\e[33mUSAGE\e[0m] NICK <nickname>");
		return;
	}

	std::string	user = get(command, 1);
	if (user.size() > 200) {
		client->send("[\e[31mERROR\e[0m] Nickname too long !");
		return;
	}
	if (!isFormat(user, "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890-_{}[]\\|", 0)) {
		client->send("[\e[31mERROR\e[0m] Nickname format isn't correct !");
		return;
	}

	std::string	tmp = client->getNickname();
	client->setNickname("");
	if (client->getServer()->haveUser(user)) {
		client->send("[\e[31mERROR\e[0m] Nickname already claim !");
		client->setNickname(tmp);
		return;
	}
	client->setNickname(get(command, 1));
	client->send("[\e[32mINFO\e[0m] " + client->getNickname() + " as a new nickname.");
	if (tmp.size() == 0)
		std::cout << "[\e[32mINFO\e[0m] Set nickname to " + get(command, 1) + " !"<< std::endl;
	else
		std::cout << "[\e[32mINFO\e[0m] " + tmp + " changes its name to " + get(command, 1) + " !"<< std::endl;
}
