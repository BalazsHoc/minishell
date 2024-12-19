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
# include <termios.h>
# include <errno.h>
# include <dirent.h>

# include <sys/types.h>
# include <sys/wait.h>

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 50
# endif

# ifndef MAX_CMNDS
# define MAX_CMNDS 50
# endif

# ifndef BUF_SIZE_ENV
# define BUF_SIZE_ENV 5000
# endif


typedef struct pipex_s
{

	char 	***cmnds;
	char 	***ops;

	char	**paths;
	char	**cur_env;
	char	**export;

	char	*input;
	char	*line;
	char	*cur_path;

	int		*exit_codes;

	int		last_exit_status;
	int		fd_out;
	int		cmnd_count;

}	t_pipex;

int		main(int argc, char **argv, char **env);

//	parsing.c

void	parsing(t_pipex *data);

//	util_checks.c

int		check_reds(t_pipex *data);
int		check_open(char *line);
int		syntax_check(char *line, int i, int count);

//	check_folder.c

void    check_folder(t_pipex *data);

//	init_cmnds.c

int		dollar_in(char *line, int j, int open);
int		count_expansion(t_pipex *data, int i, int open, char **env);

char	**fill_cmnds(char **arr, t_pipex *data, int i, char **env);


//	init_ops.c


void	ft_strcpy(char *s1, char *s2);
void    fill_ops(t_pipex *data, int index);
void    fill_echo_exit(t_pipex *data, int index);

int		count_ops(t_pipex *data, int index);
int		count_env(char **env);
int		echo_exit_code(char **arr);

//	inti_paths.c

void 	set_cur_path(t_pipex *data);

char	*find_path(t_pipex*data, char *cmnd);

int		is_mini(t_pipex *data, int i);

//	count.c

int		count_cmnds(char *line);
int		count_elem(t_pipex *data, int i, int count);
int		count_chars(char *line, int i, int open);


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
int		is_red_in(char c);
int		is_red_out(char c);


// start_exec.c

void 	start_exec(t_pipex *data);

int		is_red_inline(t_pipex *data, int index);
int		is_in_inline(t_pipex *data, int index);

//	signal_handling.c
void	signal_main(int sig);
void    signal_head();
void    signal_change(int flag);


//	start_exec_utils.c

int		is_valid_cwd(t_pipex *data);
char	*get_input(t_pipex *data, int index_1, int index_2);
int		here_doc(t_pipex *data, int index);
int		open_out(t_pipex *data, int index);
int		bigger_one(char *s1, char *s2);

void	mini_parent(t_pipex *data, int index, int cmnd_count, int (*pipes)[2]);
void	mini_child(t_pipex *data, int index);

char	*malloc_cpy_export(t_pipex *data, char *str, int track, int i);

//	exec.c

void	exec_mini(t_pipex *data, int index, int (*pipes)[2]);
void	exec_cmnd(t_pipex *data, int index, int (*pipes)[2], pid_t *pid);
char 	*join_this(char *s1, char *s2);

//	exec_cmnd_utils.c

char	*create_tmp(t_pipex *data, int index, char *tmp_name, int count);
void	close_pipes(int (*pipes)[2], int cmnd_count);
void	create_pipes(int (*pipes)[2], int cmnd_count);


//	free.c

int		free_this(char *s);
void	free_struct(t_pipex *data);
void	free_list_list(char ***arr);
void	free_list(char **arr);
void	free_str(char *s);
void	free_env(char **env);

//	exit_child.c

void	error_code(t_pipex *data);
void	exit_child(t_pipex *data, int index, int errnum);

//	env.c

// void	init_env(char **env);


//	get_next_line.c

char	*get_next_line(int fd, t_pipex *data);
char	*gnl_join_buffer(char *line, char *buffer);

void	*gnl_calloc(size_t nmemb, size_t size);

//	get_next_line_utils.c

char	*gnl_fromnl(char *buf);
char	*gnl_strcpy(char *buf, t_pipex *data);

int		gnl_newline(char *str);
int		gnl_strlen(char *str);

void	gnl_free(char **ptr);

#endif
