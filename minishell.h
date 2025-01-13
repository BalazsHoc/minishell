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


typedef struct lines_s
{
	char 	***cmnds;
	char	***ops;

	char	**paths;

	int		**red_cmnd;
	int		**pos_in_line;
	int		(*pipes)[2];
	int		*exit_codes;
	char	*cur_line;

	int		cmnd_count;

}	t_lines;

typedef struct pipex_s
{
	struct	lines_s		**lines;
	char				**cur_env;
	char				**export;
	char				**buf_array;

	char				*input;
	char				*line;
	char				*cur_path;
	char				*buf_str;

	int					line_count;
	int					chars_in_line;
	int					here;
	int					here_2;
	int					here_2_old;
	int					last_exit_status;
	int					fd_out;
	int					buf_int;
	int					count_elem;

	pid_t				*pid;

	struct sigaction main_sa;

}	t_pipex;

int		main(int argc, char **argv, char **env);

//	parsing.c

void	parsing(t_pipex *data);

//	util_checks.c

int		check_reds(t_pipex *data, int index_1);
int		check_open(char *line);
int		syntax_check(char *line, int i, int count);

//	check_folder.c

void    check_folder(t_pipex *data, int index);

//	init_cmnds.c

void	fill_cmnds(t_pipex *data, int i, int index_1, int here);

int		dollar_in(char *line, int j, int open);
int		count_expansion(t_pipex *data, int i, int open);
int		is_delim_back(char *str, int i);
int		is_delim_front(char *str, int i);


//	init_ops.c


void	ft_strcpy(char *s1, char *s2);
void    fill_ops(t_pipex *data, int index_1, int index_2);
// void    fill_echo_exit(t_pipex *data, int index);

int		count_ops(t_pipex *data, int index_1, int index_2);
int		count_env(char **env);
int		echo_exit_code(char **arr);

//	inti_paths.c

void 	set_cur_path(t_pipex *data);

char	*find_path(t_pipex*data, char *cmnd);

int		is_mini(t_pipex *data, int index_1, int index_2);

//	count.c

void	set_line_count(t_pipex *data);
int		count_cmnds(char *line, int index);
int		count_elem(t_pipex *data, int index_1, int i, int here);
int		count_chars(t_pipex *data, int i, int open);
int		count_chars_2(t_pipex *data, int i);
int		check_for_empty(t_pipex *data, int i);


//	parsing_utils_is_1.c

int		is_or(char *cur);
int		is_quote_two(char c);
int		is_quote_one(char c);
int		is_quote(char c);
int		is_space(char c);

//	parsing_utils_is_2.c

int		is_or(char *cur);
int		is_red(t_pipex *data, int index_1, int index_2, int index_3);
int		is_red_1(char c);
int		is_red_clean(char *str, int index);
int		is_real_pipe(char *line, int index);
int		is_red_in(char *str, int index);
int		is_red_out(char *str, int index);


// start_exec.c

char	*get_input(t_pipex *data, int index_1, int index_2, int index_3);
void	start_exec(t_pipex *data, int index, int i, int status);
int		is_red_inline(t_pipex *data, int index_1, int index_2);
int		is_in_inline(t_pipex *data, int index_1, int index_2);

int		last_one(char **arr);

//	signal_handling.c
void	signal_main(int sig);
void	signal_back(t_pipex *data);
void	signal_change(int flag);

//void	terminal_settings();


//	start_exec_utils.c

int		is_valid_cwd(t_pipex *data);
int		here_doc(t_pipex *data, int index_1, int index_2);
int		open_out(t_pipex *data, int index_1, int index_2);
int		bigger_one(char *s1, char *s2);

int		find_key(t_pipex *data, int index_1, int index_2, int index_3);


void	mini_parent(t_pipex *data, int index_1, int index_2);
void	mini_child(t_pipex *data, int index_1, int index_2);

char	*malloc_cpy_export(t_pipex *data, char *str, int track, int i);

//	exec.c

void	exec_mini(t_pipex *data, int index_1, int index_2);
void	exec_cmnd(t_pipex *data, int index_1, int index_2);
char 	*join_this(char *s1, char *s2);

//	exec_cmnd_utils.c

char	*create_tmp(t_pipex *data, int index, char *tmp_name, int count);
void	close_pipes(t_pipex *data, int index);
void	close_pipe(t_pipex *data, int fd);
void	close_pipes_2(t_pipex *data, int index_1, int index_2);
void	create_pipes(t_pipex *data, int index);

int		check_here_doc(t_pipex *data, int index_1, int index_2);
int		check_infile(t_pipex *data, int index_1, int index_2);
//	free.c

int		free_this(char *s);
void	free_struct(t_pipex *data);
void	free_list_list(char ***arr);
void	free_list(char **arr);
void	free_str(char *s);
void	free_lines(t_pipex *data);
void	free_env(char **env);

//	exit_child.c

void	error_code(t_pipex *data);
void	exit_child(t_pipex *data, int index_1, int index_2, int errnum);

//	env.c


char	*malloc_str(size_t size, t_pipex *data);

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
