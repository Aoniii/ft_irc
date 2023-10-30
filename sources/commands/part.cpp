#include "Command.hpp"

/**
 * Command: PART
 * Usage: PART <channelname>{,<channelname>}
 * 
 * The PART message causes the client sending the message to be removed
 * from the list of active users for all given channels listed in the
 * parameter string.
 */
void	Command::Part(std::list<std::string> command, Client* client) {
	if (!client->isAuthenticate()) {
		client->send("[\e[31mERROR\e[0m] Please enter the password !");
		client->send("[\e[33mUSAGE\e[0m] PASS <password>");
		return;
	}
	if (command.size() != 2) {
		client->send("[\e[33mUSAGE\e[0m] PART <channelname>{,<channelname>}");
		return;
	}

	std::list<std::string>	channel = split(get(command, 1) + ",", ",");

	for (std::list<std::string>::iterator it = channel.begin(); it != channel.end(); it++) {
		if (!client->getServer()->haveChannel(*it)) {
			client->send("[\e[31mERROR\e[0m] Channel doesn't exist !");
			continue;
		}
		if (!client->getServer()->findChannel(*it)->haveUser(client->getClient())) {
			client->send("[\e[31mERROR\e[0m] You are not in this channel !");
			continue;
		}
		if (client->getServer()->findChannel(*it)->haveUser(client->getClient())) {
			if (client->getServer()->findChannel(*it)->getSuperOperator() == client->getClient()) {
				client->getServer()->findChannel(*it)->send("[\e[32mINFO\e[0m] The channel " + *it + " is delete.");
				std::cout << "[\e[32mINFO\e[0m] The channel " + *it + " is delete." << std::endl;
				client->getServer()->findChannel(*it)->setName("");
				return ;
			} else if (client->getServer()->findChannel(*it)->haveOperator(client->getClient())) {
				client->getServer()->findChannel(*it)->getOperators().remove(client->getClient());
			}
			client->getServer()->findChannel(*it)->removeUser(client->getClient());
			client->send("[\e[32mINFO\e[0m] You have left " + *it + ".");
			std::cout << "[\e[32mINFO\e[0m] " + client->getNickname() + " leaves " + *it + "." << std::endl;
		}
	}
}
