#include "Command.hpp"

/**
 * Command: QUIT
 * Usage: QUIT :[<Quit message>]
 * A client session is ended with a quit message.
 */
void	Command::Quit(std::list<std::string> command, Client* client) {
	if (command.size() > 2 || (command.size() == 2 && get(command, 1).at(0) != ':')) {
		client->send("[\e[33mUSAGE\e[0m] QUIT :[<Quit message>]");
		return;
	}

	std::string	str = "[\e[32mINFO\e[0m] ";
	if (client->getNickname().size() != 0)
		str += client->getNickname();
	else
		str += "A user";
	str += " leaves";
	if (command.size() == 2)
		str += ": " + get(command, 1).substr(1, get(command, 1).size() - 1);
	else
		str += " !";

	client->getServer()->broadcast(str);
	std::cout << str << std::endl;

	client->quit();
}
