#include "Command.hpp"

/**
 * Command: JOIN
 * Usage: JOIN <channelname>{,<channelname>} [<password>]
 * The JOIN command is used by client to start listening a specific channel.
 */
void	Command::Join(std::list<std::string> command, Client* client) {
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
	if (command.size() < 2 || command.size() > 3) {
		client->send("[\e[33mUSAGE\e[0m] JOIN <channelname>{,<channelname>} [<password>]");
		return;
	}

	std::list<std::string>	channel = split(get(command, 1) + ",", ",");
	std::string 			password = (command.size() == 3 ? get(command, 2) : "");

	for (std::list<std::string>::iterator it = channel.begin(); it != channel.end(); it++) {
		if ((*it).at(0) != '&' && (*it).at(0) != '#') {
			client->send("[\e[31mERROR\e[0m] Channel name begin by '&' or '#' !");
			continue;
		}
		if ((*it).size() > 200) {
			client->send("[\e[31mERROR\e[0m] Channel name too long !");
			continue;
		}
		if (!isFormat(*it, "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890-_", 1)) {
			client->send("[\e[31mERROR\e[0m] Channel format isn't correct !");
			continue;
		}
		if (!client->getServer()->haveChannel(*it))
			client->getServer()->addChannel(Channel(*it, password, client->getClient()));

		std::string	str = client->getServer()->findChannel(*it)->getPassword();
		if (str.size() == 0 || str == password) {
			if (!client->getServer()->findChannel(*it)->haveUser(client->getClient())) {
				if (client->getServer()->findChannel(*it)->getFlag()->isPrivate()) {
					client->send("[\e[31mERROR\e[0m] This channel is private !");
					continue;
				}
				if (client->getServer()->findChannel(*it)->getFlag()->isInviteOnly()) {
					client->send("[\e[31mERROR\e[0m] This channel is invite only !");
					continue;
				}
				if (client->getServer()->findChannel(*it)->getUsers().size() >= \
				client->getServer()->findChannel(*it)->getFlag()->getLimit()) {
					client->send("[\e[31mERROR\e[0m] This channel is full !");
					continue;
				}
				client->getServer()->findChannel(*it)->addUser(client);
				client->send("[\e[32mINFO\e[0m] You have joined " + *it + ".");
				std::cout << "[\e[32mINFO\e[0m] " + client->getNickname() + " has join " + *it + "." << std::endl;
			}
		} else
			client->send("[\e[31mERROR\e[0m] Invalid password !");
	}
}
