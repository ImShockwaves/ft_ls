# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccharrie <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/01 15:38:06 by ccharrie          #+#    #+#              #
#    Updated: 2018/01/04 11:12:40 by ccharrie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
RM = rm -rf
NAME = ft_ls
FLAGS = -Wall -Werror -Wextra
SRCS = nomorefilepls.c anothersft.c complemft.c gettersft.c parsingparams.c main.c parser.c lstbasicfc.c display.c filesort.c parsingtest.c checker.c getters.c
OBJS = $(SRCS:.c=.o)
MAKEFLAGS = s

.PHONY: all clean fclean

all: $(NAME)

$(NAME): $(OBJS)
		@make -C libft/
		@echo "\033[32;1mLibrary compilation done\033[0m"

		
		@$(CC) -o $(NAME) $(OBJS) -L libft/ -lft
		@echo "\033[36;1mProject compilation done\033[0m"

		@$(CC) -c $(FLAGS) $(SRCS) -I libft/

clean:
		@make clean -C libft/
	
		@$(RM) $(OBJS)

fclean: clean
		@make fclean -C libft/
	
		@$(RM) $(NAME)

		@echo "\033[31;1mClean done\033[0m"

re: fclean all
