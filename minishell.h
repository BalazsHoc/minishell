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

typedef struct pipex_s
{
	// char	***operations;
	char 	***cmnds;
	char	**paths;

	// char	*infile;
	// char	*outfile;
	// char	**redirections;
	// char 	**cmnds;
}	t_pipex;

int		main(int argc, char **argv, char **env);

//	parsing.c

void	parsing(char *line, char **env);

//	parsing_utils.c

int		count_chars(char *line);
int		count_elem(char *line, int i);
int		is_space(char c);
int		count_cmnds(char *line);
int 	syntax_check(char *line, int i);

//	parsing_utils_2.c

int		is_or(char *cur);
int		cmnds_start(char **arr);

//	free.c

void	free_struct(t_pipex *data);
void	free_a(char *line, t_pipex *data);
void	free_list_list(char ***arr);
void	free_list(char **arr);
void	free_str(char **s);

//	find_path.c

char *find_path(char **env, char *cmnd);

//	exit_child.c

void	error_code(t_pipex *data, char *line, int ex);
void	exit_child(int errnum, char *line, t_pipex *data);

#endif