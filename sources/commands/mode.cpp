#include "Command.hpp"
#include "Flag.hpp"

/**
 * Command: MODE
 * Usage: MODE <channel> {[+|-]|o|p|s|i|t|n|b|v} [<limit>] [<user>] [<ban mask>] [<password>]
 * 
 * The MODE command is provided so that channel operators may change the
 * characteristics of `their' channel.
 */
void	Command::Mode(std::list<std::string> command, Client* client) {
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
	if (command.size() < 3 || command.size() > 7) {
		client->send("[\e[33mUSAGE\e[0m] MODE <channel> {[+|-]|o|p|s|i|t|n|m|l|b|v|k} [<limit>] [<user>] [<ban mask>] [<password>]");
		return;
	}
	if (!client->getServer()->haveChannel(get(command, 1))) {
		client->send("[\e[31mERROR\e[0m] Invalid channel !");
		return;
	}
	if (!client->getServer()->findChannel(get(command, 1))->haveOperator(client->getClient())) {
		client->send("[\e[31mERROR\e[0m] You're not an operator !");
		return;
	}
	if (!isCorrectFlag(get(command, 2))) {
		client->send("[\e[31mERROR\e[0m] Invalid flags !");
		return;
	}
	client->getServer()->findChannel(get(command, 1))->getFlag()->use(command, client);
}
