/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:41:53 by bhocsak           #+#    #+#             */
/*   Updated: 2024/10/11 15:41:55 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_ops(t_pipex *data, int index_1)
{
	int	i;
	int	j;

	i = -1;
	data->l[index_1]->ops = ft_calloc(sizeof(char **),
			(data->l[index_1]->cmnd_count + 1), data);
	while (data->l[index_1]->cmnds[++i])
	{
		j = count_ops(data, index_1, i);
		if (j != -1)
		{
			data->l[index_1]->ops[i] = ft_calloc(sizeof(char *), (j + 1), data);
			data->l[index_1]->ops[i][j] = 0;
			if (j > 0)
				fill_ops(data, index_1, i);
		}
	}
}

void	init_paths(t_pipex *d, int i_1, int i_2)
{
	d->l[i_1]->paths = ft_calloc(sizeof(char *),
			(d->l[i_1]->cmnd_count + 1), d);
	while (++i_2 < d->l[i_1]->cmnd_count)
	{
		if (is_mini(d, i_1, i_2))
			d->l[i_1]->paths[i_2] = ft_strdup(d, "minicmnds");
		else if (!ft_strncmp(d->l[i_1]->ops[i_2][0], "echo", 5))
			d->l[i_1]->paths[i_2] = ft_strdup(d, "/usr/bin/echo");
		else if (d->l[i_1]->ops[i_2] && d->l[i_1]->ops[i_2][0]
			&& !one_of_those(d->l[i_1]->ops[i_2][0])
				&& !is_executable(d, i_1, i_2) && get_path(d))
		{
			d->l[i_1]->paths[i_2] = find_path(d, d->l[i_1]->ops[i_2][0]);
			if (!d->l[i_1]->paths[i_2])
				d->l[i_1]->paths[i_2] = ft_strdup(d, "pathnfound");
		}
		else if ((!ft_strncmp(d->l[i_1]->ops[i_2][0], ".", 2)
			|| !one_of_those(d->l[i_1]->ops[i_2][0]))
				&& check_executable(d, i_1, i_2)
					&& !one_of_those_2(d->l[i_1]->ops[i_2][0], 0))
			d->l[i_1]->paths[i_2] = ft_strdup(d, d->l[i_1]->ops[i_2][0]);
		else
			d->l[i_1]->paths[i_2] = ft_strdup(d, "pathnfound");
	}
}

void	init_lines(t_pipex *data, int i)
{
	data->chars_in_line = -1;
	data->line_count = 1;
	while (data->line[++data->chars_in_line])
	{
		if (data->line[data->chars_in_line] == '\n'
			&& data->line[data->chars_in_line + 1])
			data->line_count++;
	}
	while (data->chars_in_line && is_space(data->line[data->chars_in_line - 1]))
		data->chars_in_line--;
	data->l = ft_calloc(sizeof(t_lines *), (data->line_count + 1), data);
	while (++i < data->line_count)
	{
		data->l[i] = ft_calloc(sizeof(t_lines), 1, data);
		data->l[i]->cmnds = NULL;
		data->l[i]->ops = NULL;
		data->l[i]->paths = NULL;
		data->l[i]->red_cmnd = NULL;
		data->l[i]->pos = NULL;
		data->l[i]->pipes = NULL;
		data->l[i]->exit_codes = NULL;
		data->l[i]->cmnd_count = 0;
	}
}

int	init_line(t_pipex *data, int i)
{
	data->l[i]->cmnd_count = count_cmnds(data->line + data->here_2);
	data->l[i]->exit_codes = ft_calloc(sizeof(int),
			(data->l[i]->cmnd_count), data);
	data->l[i]->ex = INT_MAX;
	init_red_cmnds(data, i);
	data->l[i]->input = ft_calloc(sizeof(char *),
			data->l[i]->cmnd_count + 1, data);
	init_pos_in_line(data, i);
	init_cmnds(data, i, -1);
	handle_here(data, i, -1, 0);
	init_pipes_pids(data, i);
	return (1);
}

int does_key_exist(char *line, int i)
{
	while (line[++i])
	{
		if (is_char(line[i]))
			return (i);
	}
	return (0);
}

char *get_key(t_pipex *data, char *line, int i)
{
	int		j;
	char	*key;

	j = 0;
	while (line[i + j] && !is_delim_front(line, i + j))
		j++;
	key = ft_calloc(sizeof(char), j + 1, data);
	j = 0;
	while (line[i + j] && !is_delim_front(line, i + j))
		key[j] = line[i + j];
	return (key);
}

void	do_nonesense_here_doc(t_pipex *d, int check)
{
	int i;
	char *key;
	char *buf;

	i = d->here_2_old;
	key = NULL;
	buf = NULL;
	while (free_this(&buf) && ++i < check)
	{
		if (d->line[i] == '<' && d->line[i + 1] && d->line[i + 1] == '<'
			&& does_key_exist(d->line, i))
		{
			key = get_key(d, d->line, does_key_exist(d->line, i));
			buf = readline("> ");
			while (buf && !g_signal && (!ft_strcmp_2(buf, key)) && free_this(&buf))
				buf = readline("> ");
		}
	}
	if (g_signal)
		return (free_str(&buf));
}

int	syntax_redir_check_init(t_pipex *data, int i)
{
	int syn_check;
	int red_check;
	int check;

	syn_check = syntax_check(data, data->here_2_old, 0);
	init_line(data, i);
	if (syn_check)
		red_check = check_reds(data, i, -1, syn_check);
	else
		red_check = check_reds(data, i, -1, INT_MAX - 1);
	// printf("SYN: %d | RED: %d\n", syn_check, red_check);
	check = 0;
	if (syn_check && syn_check < red_check)
	{
		write(2, "bash: syntax error near unexpected token `|'\n", 46);
		set_err_old(data);
		check = syn_check;
	}
	else if (red_check)
		check = red_check;
	if (check)
		do_nonesense_here_doc(data, check);
	return (check);
}

void	parsing(t_pipex *data, int i)
{
	init_lines(data, -1);
	make_history(data);
	while (data->l[++i] && data->here_2_old < data->chars_in_line)
	{
		signal_change(NULL, 2);
		if (check_open(data, data->line))
		{
			write(2, "bash: syntax error: open quotes \n", 34);
			set_err_old(data);
			continue ;
		}
		if (syntax_redir_check_init(data, i))
			continue ;
			// if (check_reds(data, i, -1, check))
			// {
			// 	if (data->here_2_old >= data->chars_in_line)
			// 		return (free_lines(data));
			// 	else
			// 		continue ;
			// }
		init_rest(data, i);
	}
	free_lines(data);
}
