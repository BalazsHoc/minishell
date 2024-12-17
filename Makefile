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

#	COMPILING

CC				= cc
CFLAGS			= -Wall -Wextra -Werror -g
RL_FLAGS		= -lreadline -lncurses

#	LIBFT

LIBFT_PATH		= srcs/libft/
LIBFT			= $(LIBFT_PATH)libft.a


#	GNL

GNL_PATH		= srcs/get_next_line/
GNL				= $(GNL_PATH)get_next_line.a

#	SRCS && OBJS

SRCS			= main.c srcs/free.c srcs/exit_clean.c srcs/signal_handling.c start_exec.c start_exec_utils.c exec.c exec_cmnd_utils.c
OBJ				= $(SRCS:.c=.o)

#	PARSING

DIR_PARSING		= srcs/parsing/
SRCS_PARSING	= parsing.c init_paths.c init_cmnds.c init_ops.c parsing_utils_is_1.c parsing_utils_is_2.c util_checks.c count.c check_folder.c
PATH_PARSING	= $(addprefix $(DIR_PARSING), $(SRCS_PARSING))
OBJ_PARSING		= $(PATH_PARSING:.c=.o)

%.o : %.c
	@$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJ) $(OBJ_PARSING)
	@make -C $(LIBFT_PATH) all
	@make -C $(GNL_PATH) all
	@$(CC) $(CFLAGS) $(OBJ) $(OBJ_PARSING) $(LIBFT) $(GNL) -o $(NAME) $(RL_FLAGS)

all: $(NAME)

clean:
	@make -C $(LIBFT_PATH) clean
	@make -C $(GNL_PATH) clean
	@rm -f $(OBJ) $(OBJ_PARSING)

fclean: clean
	@make -C $(LIBFT_PATH) fclean
	@make -C $(GNL_PATH) fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re