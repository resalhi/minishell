# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ressalhi <ressalhi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/10 11:43:45 by ressalhi          #+#    #+#              #
#    Updated: 2022/08/25 14:09:05 by ressalhi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC =	main.c ft_split.c expand.c env.c errors.c parsing.c redirections.c \
		remove_trash.c utils.c utils2.c dollar.c dollar2.c dollar3.c dollar_utils.c \
		dollar4.c unset.c echo.c ft_export.c ft_export2.c builtins.c pipes.c pipe_utils.c \
		here_doc.c ft_itoa.c ft_cd.c ft_exit.c wait.c files.c child_parent.c fullfill.c \
		valhala.c dedicate.c signal.c errors2.c utils3.c utils4.c ft_cd1.c \

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -lreadline -L/Users/$(USER)/.brew/opt/readline/lib -I/Users/$(USER)/.brew/opt/readline/include -o $(NAME)

clean :
	rm -rf $(OBJ)
fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re
