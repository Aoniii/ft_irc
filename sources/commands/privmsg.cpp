#include "Command.hpp"

/**
 * Command: PRIVMSG
 * Usage: PRIVMSG <target>{,<target>} :<message>
 * PRIVMSG is used to send private messages between users.
 */
void	Command::Privmsg(std::list<std::string> command, Client* client) {
	if (!client->isAuthenticate()) {
		client->send("[\e[31mERROR\e[0m] Please enter the password !");
		client->send("[\e[33mUSAGE\e[0m] PASS <password>");
		return;
	}
	if (client->getNickname().size() == 0) {
		client->send("[\e[31mERROR\e[0m] Please register !");
		client->send("[\e[33mUSAGE\e[0m] USER <username> <host> <servername> :<real name>");
		return;
	}
	if (command.size() != 3 || get(command, 2).at(0) != ':') {
		client->send("[\e[33mUSAGE\e[0m] PRIVMSG <target>{,<target>} :<message>");
		return;
	}

	std::list<std::string>	target = split(get(command, 1) + ",", ",");
	std::string 			message = get(command, 2).substr(1, get(command, 2).size() - 1);
	std::string	str = "<" + client->getNickname() + "> " + message;

	for (std::list<std::string>::iterator it = target.begin(); it != target.end(); it++) {
		if (!client->getServer()->haveUser(*it) && !client->getServer()->haveChannel(*it)) {
			client->send("[\e[31mERROR\e[0m] Unknown target !");
			continue;
		}
		if (client->getServer()->haveChannel(*it) && !client->getServer()->findChannel(*it)->haveUser(client->getClient()) && client->getServer()->findChannel(*it)->getFlag()->isExternNoSpeak()) {
			client->send("[\e[31mERROR\e[0m] You didn't have the authorization for " + *it + " !");
			continue;
		}
		if (client->getServer()->haveUser(*it)) {
			if (client->getServer()->findUser(*it)->getClient() != client->getClient())
				client->getServer()->findUser(*it)->send(str);
		} else if (client->getServer()->haveChannel(*it)) {
			if (client->getServer()->findChannel(*it)->getFlag()->isModeratorSpeakOnly() && \
			!client->getServer()->findChannel(*it)->haveOperator(client->getClient())) {
				client->send("[\e[31mERROR\e[0m] You didn't have the authorization to talk in this channel !");
				continue;
			}
			client->getServer()->findChannel(*it)->send(str);
		}
		std::cout << "[\e[32mINFO\e[0m] " + client->getNickname() + " send message to " + *it + "." << std::endl;
	}
}
