#include "Command.hpp"

/**
 * Command: NOTICE
 * Usage: NOTICE <target>{,<target>} :<message>
 * The NOTICE message is used similarly to PRIVMSG.
 */
void	Command::Notice(std::list<std::string> command, Client* client) {
	if (!client->isAuthenticate())
		return;
	if (client->getNickname().size() == 0)
		return;
	if (command.size() != 3 || get(command, 2).at(0) != ':')
		return;

	std::list<std::string>	target = split(get(command, 1) + ",", ",");
	std::string 			message = get(command, 2).substr(1, get(command, 2).size() - 1);
	std::string	str = "<" + client->getNickname() + "> " + message;

	for (std::list<std::string>::iterator it = target.begin(); it != target.end(); it++) {
		if (!client->getServer()->haveUser(*it) && !client->getServer()->haveChannel(*it))
			continue;
		if (client->getServer()->haveChannel(*it) && !client->getServer()->findChannel(*it)->haveUser(client->getClient()) && client->getServer()->findChannel(*it)->getFlag()->isExternNoSpeak())
			continue;
		if (client->getServer()->haveUser(*it)) {
			client->getServer()->findUser(*it)->send(str);
		} else if (client->getServer()->haveChannel(*it)) {
			if (client->getServer()->findChannel(*it)->getFlag()->isModeratorSpeakOnly() && \
			!client->getServer()->findChannel(*it)->haveOperator(client->getClient()))
				continue;
			client->getServer()->findChannel(*it)->send(str);
		}
		std::cout << "[\e[32mINFO\e[0m] " + client->getNickname() + " send message to " + *it + "." << std::endl;
	}
}
