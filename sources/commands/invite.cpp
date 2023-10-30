#include "Command.hpp"

/**
 * Command: INVITE
 * Usage: INVITE <nickname> <channel>
 * The INVITE message is used to invite users to a channel.
 */
void	Command::Invite(std::list<std::string> command, Client* client) {
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
	if (command.size() != 3) {
		client->send("[\e[33mUSAGE\e[0m] INVITE <nickname> <channel>");
		return;
	}
	if (!client->getServer()->haveUser(get(command, 1))) {
		client->send("[\e[31mERROR\e[0m] This user doesn't exist !");
		return;
	}
	if (!client->getServer()->haveChannel(get(command, 2))) {
		client->send("[\e[31mERROR\e[0m] This channel doesn't exist !");
		return;
	}
	if (!client->getServer()->findChannel(get(command, 2))->haveOperator(client->getClient())) {
		client->send("[\e[31mERROR\e[0m] You're not an operator !");
		return;
	}
	if (client->getServer()->findChannel(get(command, 2))->haveUser(client->getServer()->findUser(get(command, 1))->getClient())) {
		client->send("[\e[31mERROR\e[0m] This user is already on this channel !");
		return;
	}
	client->getServer()->findChannel(get(command, 2))->addUser(client->getServer()->findUser(get(command, 1)));
	client->send("[\e[32mINFO\e[0m] " + get(command, 1) + " is invited !");
	client->getServer()->findUser(get(command, 1))->send("[\e[32mINFO\e[0m] You were invited on " + get(command, 2) + " !");
	std::cout << "[\e[32mINFO\e[0m] " + client->getNickname() + " invite " + get(command, 1) + " on " + get(command, 2) + "." << std::endl;
}
