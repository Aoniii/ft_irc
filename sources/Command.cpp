#include "Command.hpp"

Command::Command(void) {}
Command::~Command(void) {}

void	Command::parseCommand(std::string input_command, Client* client) {
	std::list<std::string>	lst;

	if (input_command.length() <= 1)
		return;
	lst = split(input_command, " \t\n\v\f\r");
	if (lst.empty())
		return ;
	for (int i = 0; i < 13; i++) {
		if (this->commands[i].oper == *lst.begin()) {
			(this->*(commands[i].f))(lst, client);
			return;
		}
	}
	client->send("[\e[31mERROR\e[0m] " + *lst.begin() + ": unknown command !");
}

t_command Command::commands[] = {{"PASS", &Command::Pass}, {"NICK", &Command::Nick}, 
{"USER", &Command::User}, {"JOIN", &Command::Join}, {"PRIVMSG", &Command::Privmsg},
{"PART", &Command::Part}, {"NOTICE",  &Command::Notice}, {"QUIT",  &Command::Quit},
{"KICK",  &Command::Kick}, {"MODE",  &Command::Mode}, {"INVITE",  &Command::Invite},
{"TOPIC",  &Command::Topic}, {"ALL", &Command::All}};

std::string Command::password = "";
