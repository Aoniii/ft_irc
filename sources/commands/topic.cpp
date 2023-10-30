#include "Command.hpp"

/**
 * Command: TOPIC
 * Usage: TOPIC <channel> :[<topic>]
 * The TOPIC message is used to change or view the topic of a channel.
 */
void	Command::Topic(std::list<std::string> command, Client* client) {
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
	if (command.size() < 2 || command.size() > 3 || (command.size() == 3 && get(command, 2).at(0) != ':')) {
		client->send("[\e[33mUSAGE\e[0m] TOPIC <channel> :[<topic>]");
		return;
	}
	if (!client->getServer()->haveChannel(get(command, 1))) {
		client->send("[\e[31mERROR\e[0m] This channel doesn't exist !");
		return;
	}

	std::string	tmp;
	if (command.size() == 2) {
		tmp = client->getServer()->findChannel(get(command, 1))->getTopic();
		if (tmp.size() != 0)
			client->send("[\e[36mTOPIC\e[0m] " + tmp);
		else
			client->send("[\e[36mTOPIC\e[0m] This channel doesn't have any topic !");
	} else {
		if (!client->getServer()->findChannel(get(command, 1))->haveOperator(client->getClient()) && 
		client->getServer()->findChannel(get(command, 1))->getFlag()->isTopicOperatorOnly()) {
			client->send("[\e[31mERROR\e[0m] You're not the operator of this channel !");
			return ;
		}
		tmp = get(command, 2).substr(1, get(command, 2).size() - 1);
		client->getServer()->findChannel(get(command, 1))->setTopic(tmp);
		client->send("[\e[32mINFO\e[0m] Topic updated !");
		std::cout << "[\e[32mINFO\e[0m] Channel " + get(command, 1) + " have new topic :" + tmp << std::endl;
	}
}
