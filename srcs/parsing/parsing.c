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

// TAKE THAT OUT
// void	print_that_shit(t_pipex *data, int index_1)
// {
// 	int	i;
// 	int	j;

// 	i = -1;
// 	printf("|\n");
// 	while (data->l[index_1]->cmnds[++i])
// 	{
// 		j = -1;
// 		while (data->l[index_1]->cmnds[i][++j])
// 		{
// 			if (data->l[index_1]->cmnds[i][j])
// 				printf("ELEM: %d:%d | |%s| ", i, j,
// data->l[index_1]->cmnds[i][j]);
// 			printf("\n");
// 		}
// 		j = -1;
// 		if (data->l[index_1]->ops && data->l[index_1]->ops[i])
// 		{
// 			while (data->l[index_1]->ops[i][++j])
// 				printf("OP:   %d:%d | |%s|\n", i, j,
// data->l[index_1]->ops[i][j]);
// 		}
// 		printf("PATH: |%s|\n", data->l[index_1]->paths[i]);
// 	}
// }

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
			&& !one_of_those(d, i_1, i_2)
				&& !is_executable(d, i_1, i_2) && get_path(d))
		{
			d->l[i_1]->paths[i_2] = find_path(d, d->l[i_1]->ops[i_2][0]);
			if (!d->l[i_1]->paths[i_2])
				d->l[i_1]->paths[i_2] = ft_strdup(d, "pathnfound");
		}
		else if (check_executable(d, i_1, i_2))
			d->l[i_1]->paths[i_2] = ft_strdup(d, d->l[i_1]->ops[i_2][0]);
		else
			d->l[i_1]->paths[i_2] = ft_strdup(d, "pathnfound");
	}
}

void	init_lines(t_pipex *data)
{
	int	i;

	i = -1;
	data->chars_in_line = -1;
	data->line_count = 1;
	while (data->line[++data->chars_in_line])
	{
		if (data->line[data->chars_in_line] == '\n'
			&& data->line[data->chars_in_line + 1])
			data->line_count++;
	}
	data->l = ft_calloc(sizeof(t_lines *), (data->line_count + 1), data);
	while (++i < data->line_count)
	{
		data->l[i] = ft_calloc(sizeof(t_lines), 1, data);
		data->l[i]->cmnds = NULL;
		data->l[i]->ops = NULL;
		data->l[i]->paths = NULL;
		data->l[i]->red_cmnd = NULL;
		data->l[i]->pos_in_line = NULL;
		data->l[i]->pipes = NULL;
		data->l[i]->exit_codes = NULL;
		data->l[i]->cmnd_count = 0;
	}
}

void	init_line(t_pipex *data, int i)
{
	data->l[i]->cmnd_count = count_cmnds(data->line + data->here_2);
	data->l[i]->exit_codes = ft_calloc(sizeof(int),
			(data->l[i]->cmnd_count), data);
	init_red_cmnds(data, i);
	data->l[i]->input = ft_calloc(sizeof(char *),
			data->l[i]->cmnd_count + 1, data);
	init_pos_in_line(data, i);
	init_cmnds(data, i, -1);
	make_history(data, i, -1, 0);
	init_pipes_pids(data, i);
}

void	parsing(t_pipex *data)
{
	int	i;

	i = -1;
	init_lines(data);
	if (!syntax_check(data, -1, 0))
		return (write(2, "bash: syntax error near unexpected token `|'\n", 46),
			data->last_exit_status = 2, add_history(data->line),
			free_lines(data));
	if (check_open(data->line))
		return (write(2, "bash: syntax error: open quotes \n", 34),
			data->last_exit_status = 2, add_history(data->line),
			free_lines(data));
	while (data->l[++i] && data->here_2_old < data->chars_in_line)
	{
		signal_change(NULL, 2);
		init_line(data, i);
		if (!check_reds(data, i, -1, -1))
			return (free_lines(data));
		init_ops(data, i);
		init_paths(data, i, -1);
		check_folder(data, i, -1, -1);
		start_exec(data, i, -1, 0);
	}
	free_lines(data);
}
