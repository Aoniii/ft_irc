#include "Command.hpp"

/**
 * Command: KICK
 * Usage: KICK <channel> <user> :[<comment>]
 * The KICK command can be  used  to  forcibly  remove  a  user  from  a channel.
 */
void	Command::Kick(std::list<std::string> command, Client* client) {
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
	if (command.size() < 3 || command.size() > 4  || (command.size() == 4 && get(command, 3).at(0) != ':')) {
		client->send("[\e[33mUSAGE\e[0m] KICK <channel> <user> :[<comment>]");
		return;
	}
	if (!client->getServer()->haveUser(get(command, 2))) {
		client->send("[\e[31mERROR\e[0m] This user doesn't exist !");
		return;
	}
	if (!client->getServer()->haveChannel(get(command, 1))) {
		client->send("[\e[31mERROR\e[0m] This channel doesn't exist !");
		return;
	}
	if (!client->getServer()->findChannel(get(command, 1))->haveOperator(client->getClient())) {
		client->send("[\e[31mERROR\e[0m] You're not an operator !");
		return;
	}
	int	target = client->getServer()->findUser(get(command, 2))->getClient();
	if (!client->getServer()->findChannel(get(command, 1))->haveUser(target)) {
		client->send("[\e[31mERROR\e[0m] This user isn't on this channel !");
		return;
	}
	if (client->getServer()->findChannel(get(command, 1))->getSuperOperator() == target) {
		client->send("[\e[31mERROR\e[0m] This user is the main operator !");
		return;
	}
	if (client->getServer()->findChannel(get(command, 1))->haveOperator(target))
		client->getServer()->findChannel(get(command, 1))->removeOperator(target);
	client->getServer()->findChannel(get(command, 1))->removeUser(target);

	std::string	str = "[\e[32mINFO\e[0m] You're kick on " + get(command, 1);
	if (command.size() == 4)
		str += ": " + get(command, 3).substr(1, get(command, 3).size() - 1);
	else
		str += " !";
	client->getServer()->findUser(get(command, 2))->send(str);
	client->send("[\e[32mINFO\e[0m] " + get(command, 2) + " is kicked !");
	std::cout << "[\e[32mINFO\e[0m] " + client->getNickname() + " kick " + get(command, 2) + " on " + get(command, 1) + "." << std::endl;
}
