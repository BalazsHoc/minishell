# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/08 10:14:43 by bhocsak           #+#    #+#              #
#    Updated: 2024/10/08 10:14:45 by bhocsak          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT_PATH = srcs/libft/
LIBFT = $(LIBFT_PATH)libft.a
GET_NEXT_LINE_PATH = srcs/get_next_line/
GET_NEXT_LINE = $(GET_NEXT_LINE_PATH)get_next_line.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RL_FLAGS = -lreadline -lncurses

SRCS = main.c srcs/parsing.c srcs/parsing_utils.c srcs/free.c srcs/find_path.c srcs/exit_clean.c srcs/parsing_utils_2.c

OBJ = $(SRCS:.c=.o)

%.o : %.c
	@$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJ)
	@make -C $(LIBFT_PATH) all
	@make -C $(GET_NEXT_LINE_PATH) all
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(GET_NEXT_LINE) -o $(NAME) $(RL_FLAGS)

all: $(NAME)

clean:
	@make -C $(LIBFT_PATH) clean
	@make -C $(GET_NEXT_LINE_PATH) clean
	@rm -f $(OBJ)

fclean: clean
	@make -C $(LIBFT_PATH) fclean
	@make -C $(GET_NEXT_LINE_PATH) fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fceal re