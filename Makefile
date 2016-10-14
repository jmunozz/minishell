# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmunoz <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/03 14:58:59 by jmunoz            #+#    #+#              #
#    Updated: 2016/10/10 17:23:27 by jmunoz           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS= -Wall -Wextra -Werror
CC= gcc -I Includes/
SRC= Sources/minishell.c \
	 Sources/support.c \
	 Sources/builtins.c \
	 Sources/debug.c \
	 Sources/env.c \
	 Sources/setenv.c \
	 Sources/signals.c \
	 Sources/errors.c \
	 Sources/echo.c\
	 Sources/cd.c\
	 Sources/main.c
LIBS= Libs/
OBJ= $(SRC:.c=.o)
NAME= minishell

all: lib $(NAME)

lib:
	@make -C $(LIBS)libft

cleanlib:
	@make clean -C $(LIBS)libft

fcleanlib:
	@make fclean -C $(LIBS)libft

%.o : %.c
	@$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $@ $(OBJ) -L $(LIBS)libft/ -lft

clean: cleanlib
	@rm -rf $(OBJ)

fclean: fcleanlib clean
	@rm $(NAME)

re: fclean all
