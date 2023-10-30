#include "Command.hpp"
#include "utils.hpp"

/**
 * Command: ALL
 * Usage: ALL <password> :<message>
 * ALL is commande for the bot to broadcast message with password.
 */
void	Command::All(std::list<std::string> command, Client* client) {
	std::string	tmp = JACOB;
	if (command.size() != 3 && get(command, 2).at(0) != ':') {
		client->send("[\e[31mERROR\e[0m] ALL: unknown command !");
		return;
	}
	if (get(command, 1) != tmp) {
		client->send("[\e[31mERROR\e[0m] ALL: unknown command !");
		return;
	}

	tmp = get(command, 2).substr(1, get(command, 2).size() - 1);
	std::cout << "[\e[32mINFO\e[0m] The bot broadcast a message." << std::endl;
	client->getServer()->broadcast(tmp);
}