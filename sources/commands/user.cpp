#include "Command.hpp"

/**
 * Command: USER
 * Usage: USER <username> <host> <servername> :<real name>
 * 
 * The USER message is used at the beginning of connection to specify
 * the username, hostname, servername and realname of new user.
 */
void	Command::User(std::list<std::string> command, Client* client) {
	if (!client->isAuthenticate()) {
		client->send("[\e[31mERROR\e[0m] Please enter the password !");
		client->send("[\e[33mUSAGE\e[0m] PASS <password>");
		return;
	}
	if (command.size() != 5 || get(command, 4).at(0) != ':') {
		client->send("[\e[33mUSAGE\e[0m] USER <username> <host> <servername> :<real name>");
		return;
	}
	if (client->getRealname().size() != 0) {
		client->send("[\e[31mERROR\e[0m] You're already registered !");
		return;
	}

	std::string	user = get(command, 1);
	if (user.size() > 200) {
		client->send("[\e[31mERROR\e[0m] Username too long !");
		return;
	}
	if (!isFormat(user, "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890-_{}[]\\|", 0)) {
		client->send("[\e[31mERROR\e[0m] Username format isn't correct !");
		return;
	}
	std::string	tmp = client->getNickname();
	client->setNickname("");
	if (client->getServer()->haveUser(user)) {
		client->send("[\e[31mERROR\e[0m] Username already claim !");
		client->setNickname(tmp);
		return;
	}

	client->setNickname(user);
	client->setRealname(get(command, 4).substr(1, get(command, 4).size() - 1));
	client->send("[\e[32mINFO\e[0m] User registered.");
	std::cout << "[\e[32mINFO\e[0m] New user registered (" + client->getNickname() + ")." << std::endl;
}