#include "Command.hpp"

/**
 * Command: PASS
 * Usage: PASS <password>
 * The PASS command is used to set a 'connection password'.
 */
void	Command::Pass(std::list<std::string> command, Client* client) {
	if (client->isAuthenticate()) {
		client->send("[\e[32mINFO\e[0m] You're already connected.");
		return;
	}
	if (command.size() != 2) {
		client->send("[\e[33mUSAGE\e[0m] PASS <password>");
		return;
	}
	if (get(command, 1) != Command::password) {
		client->send("[\e[31mERROR\e[0m] Invalid password !");
		return;
	} else {
		client->send("[\e[32mINFO\e[0m] Valid password.");
		client->setAuthenticate();
	}
}
