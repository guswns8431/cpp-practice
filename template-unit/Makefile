# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jseo <jseo@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/28 12:22:39 by jseo              #+#    #+#              #
#    Updated: 2021/09/29 16:53:26 by jseo             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BLACK				= 		"\033[0;30m"
GRAY				= 		"\033[1;30m"
RED					=		"\033[0;31m"
GREEN				=		"\033[0;32m"
YELLOW				=		"\033[1;33m"
PURPLE				=		"\033[0;35m"
CYAN				=		"\033[0;36m"
WHITE				=		"\033[1;37m"
EOC					=		"\033[0;0m"
LINE_CLEAR			=		"\x1b[1A\x1b[M"

CC					=		g++
CFLAGS				=		-Wall -Wextra -Werror -std=c++17
CDEBUG				=		-g -fsanitize=address
RM					=		rm -f
NAME				=		test

FILES				=		main.cpp
SRCS				=		$(addprefix ./, $(FILES))
OBJS				=		$(SRCS:.cpp=.o)

%.o					:		%.cpp
		@echo $(YELLOW) "Compiling...\t" $@ $(EOC) $(LINE_CLEAR)
		@$(CC) $(CFLAGS) $(CDEBUG) -I./ -o $@ -c $<

$(NAME)				:		$(OBJS)
		@echo $(GREEN) "Object File Completed!\n\n" $(EOC)
		@echo $(YELLOW) "Executable Building..." $(EOC)
		@$(CC) $(CFLAGS) $(CDEBUG) -I./ -o $(NAME) $(OBJS)
		@echo $(GREEN) "Ready to be Executed!\n\n"

.PHONY				:		all
all					:		$(NAME)

.PHONY				:		clean
clean				:
		@echo $(YELLOW) "Object File Cleaning..." $(EOC)
		@$(RM) $(OBJS)
		@echo $(RED) "Object File Cleaned!\n\n" $(EOC)

.PHONY				:		fclean
fclean				:		clean
		@echo $(YELLOW) "Executable Removing..." $(EOC)
		@$(RM) $(NAME)
		@echo $(RED) "Executable Removed!\n\n" $(EOC)

.PHONY				:		re
re					:		fclean all

