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


#	SRCS && OBJS

SRCS			= main.c srcs/signal_handling_1.c
OBJ				= $(SRCS:.c=.o)


#	LIBFT

DIR_LIBFT		= srcs/libft/
SRCS_LIBFT		= utils_libft_01.c utils_libft_02.c utils_libft_03.c utils_libft_04.c
PATH_LIBFT		= $(addprefix $(DIR_LIBFT), $(SRCS_LIBFT))
OBJ_LIBFT		= $(PATH_LIBFT:.c=.o)


#	PARSING

DIR_PARSING		= srcs/parsing/
SRCS_PARSING	= parsing.c init_1.c make_history.c one_of_those.c  init_paths.c init_ops.c parsing_utils_1.c parsing_utils_2.c parsing_utils_3.c parsing_utils_4.c parsing_utils_5.c checks_1.c checks_2.c checks_3.c count.c count_utils.c init_cmnds/init_cmnds.c init_cmnds/init_cmnds_exp_1.c init_cmnds/init_cmnds_exp_2.c init_cmnds/init_cmnds_exp_3.c init_cmnds/init_cmnds_exp_count_1.c init_cmnds/init_cmnds_exp_count_2.c init_cmnds/init_cmnds_utils_1.c init_cmnds/init_cmnds_utils_2.c init_cmnds/init_cmnds_utils_3.c init_cmnds/init_cmnds_utils_4.c
PATH_PARSING	= $(addprefix $(DIR_PARSING), $(SRCS_PARSING))
OBJ_PARSING		= $(PATH_PARSING:.c=.o)


#	EXEC

DIR_EXEC		= srcs/exec/
SRCS_EXEC		= exec.c exec_utils_1.c exec_utils_2.c exec_mini/mini_cd_1.c exec_mini/mini_cd_2.c exec_mini/mini_exit_1.c exec_mini/mini_exit_2.c exec_mini/mini_export_1.c exec_mini/mini_export_2.c exec_mini/mini_export_3.c exec_mini/mini_export_4.c exec_mini/mini_export_5.c exec_mini/mini_unset_1.c exec_mini/mini_unset_2.c  exec_mini/start_mini_exec_1.c exec_mini/start_mini_exec_2.c start_exec/start_exec_utils_1.c start_exec/start_exec_utils_2.c start_exec/start_exec_utils_3.c start_exec/start_exec_utils_4.c start_exec/start_exec_utils_5.c  start_exec/start_exec_utils_6.c start_exec/start_exec_utils_7.c start_exec/start_exec_utils_8.c start_exec/start_exec.c
PATH_EXEC		= $(addprefix $(DIR_EXEC), $(SRCS_EXEC))
OBJ_EXEC		= $(PATH_EXEC:.c=.o)


#	EXIT

DIR_EXIT		= srcs/exit/
SRCS_EXIT		= close_1.c close_2.c exit_clean.c free_1.c free_2.c
PATH_EXIT		= $(addprefix $(DIR_EXIT), $(SRCS_EXIT))
OBJ_EXIT		= $(PATH_EXIT:.c=.o)


%.o : %.c
	@$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJ) $(OBJ_PARSING) $(OBJ_LIBFT) $(OBJ_EXEC) $(OBJ_EXIT)
	@$(CC) $(CFLAGS) $(OBJ_PARSING) $(OBJ_LIBFT) $(OBJ_EXEC) $(OBJ_EXIT) $(OBJ) -o $(NAME) $(RL_FLAGS)

all: $(NAME)

clean:
	@rm -f $(OBJ) $(OBJ_PARSING) $(OBJ_LIBFT) $(OBJ_EXEC) $(OBJ_EXIT)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re