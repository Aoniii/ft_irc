NAME	= ircserv

CC		= c++
CFLAGS	= -Wall -Wextra -Werror -std=c++98 -g

INCS	= includes

SRCS	=	sources/main.cpp \
			sources/Client.cpp \
			sources/Command.cpp \
			sources/Server.cpp \
			sources/Channel.cpp \
			sources/utils.cpp \
			sources/commands/invite.cpp \
			sources/commands/join.cpp \
			sources/commands/kick.cpp \
			sources/commands/mode.cpp \
			sources/commands/nick.cpp \
			sources/commands/notice.cpp \
			sources/commands/part.cpp \
			sources/commands/pass.cpp \
			sources/commands/privmsg.cpp \
			sources/commands/quit.cpp \
			sources/commands/topic.cpp \
			sources/commands/user.cpp \
			sources/commands/all.cpp \
			sources/Flag.cpp

BOT			=	jacob

SRCS_BOT	=	bot/bot.cpp

OBJS		= $(SRCS:.cpp=.o)
OBJS_DIR 	= objects
OBJS_PATH	= $(addprefix $(OBJS_DIR)/, $(OBJS))

$(OBJS_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	@$(CC) -I $(INCS) $(CFLAGS) -c $< -o $@
	@printf "\033[2K\r\033[3;35m$<: \033[3;36mloading..\033[0m"

$(NAME) : $(OBJS_PATH)
	@$(CC) $(CFLAGS) $(OBJS_PATH) -o $(NAME)
	@printf "\033[2K\r\033[4;34m$(NAME):\033[0m \033[1;32mCompiled [√]\033[0m\n"

bot :
	@$(CC) $(CFLAGS) $(SRCS_BOT) -o $(BOT)
	@printf "\033[2K\r\033[4;34m$(BOT):\033[0m \033[1;32mCompiled [√]\033[0m\n"

all: $(NAME)

clean:
	@rm -rf $(OBJS_DIR)
	@printf "\033[2K\r\033[4;34m$(NAME):\033[0m \033[1;31mObject Delete \033[1;32m[√]\033[0m\n"

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(BOT)
	@printf "\033[2K\r\033[4;34m$(NAME):\033[0m \033[1;31m$(NAME) Delete \033[1;32m[√]\033[0m\n"

re: fclean all

.PHONY: all clean fclean re bot