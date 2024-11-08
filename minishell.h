/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:13:34 by bhocsak           #+#    #+#             */
/*   Updated: 2024/10/08 10:13:39 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "srcs/get_next_line/get_next_line.h"
# include "srcs/libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <fcntl.h>
# include <stdint.h>
# include <limits.h>
# include <signal.h>
# include <errno.h>

# include <sys/types.h>
# include <sys/wait.h>

# ifndef BUF_SIZE
# define BUF_SIZE 50
# endif


typedef struct pipex_s
{

	char 	***cmnds;
	char 	***ops;

	char	**paths;
	char	**mini_env;

	char	*input;

}	t_pipex;

int		main(int argc, char **argv, char **env);

//	parsing.c

void	parsing(char *line, char **env);

//	util_checks.c

int		check_reds(t_pipex *data);
int		check_open(char *line);
int		syntax_check(char *line, int i, int count);

//	init_cmnds.c

char	**fill_cmnds(char **arr, char *line, int i, int k);

int		count_cmnds(char *line);
int		count_elem(char *line, int i, int count);
int		count_chars(char *line, int i, int open);

//	init_ops.c

void    fill_ops(t_pipex *data, int index);

int		count_ops(t_pipex *data, int index);
int		count_env(char **env);

//	inti_paths.c

char	*find_path(char **env, char *cmnd);

//	parsing_utils_is_1.c

int		is_or(char *cur);
int		is_quote_two(char c);
int		is_quote_one(char c);
int		is_quote(char c);
int		is_space(char c);

//	parsing_utils_is_2.c

int		is_or(char *cur);
int		is_red(t_pipex *data, int index_1, int index_2);
int		is_red_1(char c);
int		is_red_clean(char *str, int index);
int		is_real_pipe(char *line, int index);

// start_exec.c

void	start_exec(t_pipex *data);

char	*get_input(t_pipex *data, int index_1, int index_2);

int		is_red_inline(t_pipex *data, int index);

//	start_exec_utils.c

int		here_doc(t_pipex *data, int index);
int		mini_commands(t_pipex *data, int *index);
int		open_out(t_pipex *data, int index);

// exec_cmnd.c

char	*exec_cmnd(t_pipex *data, int index);
char 	*join_this(char *s1, char *s2);

//	free.c

void	free_struct(t_pipex *data);
void	free_a(char *line, t_pipex *data);
void	free_list_list(char ***arr);
void	free_list(char **arr);
void	free_str(char *s);

//	find_path.c

char	*find_path(char **env, char *cmnd);

//	exit_child.c

void	error_code(t_pipex *data, char *line, int ex, int errnum);
void	exit_child(int errnum, char *line, t_pipex *data);

#endif
