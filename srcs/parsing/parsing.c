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

// void	print_that_shit(t_pipex *data, int index_1)
// {
// 	int	i;
// 	int	j;

// 	// i = -1;
// 	printf("|\n");
// 	// while (data->cur_env[++i])
// 	// 	printf("%s\n", data->cur_env[i]);
// 	i = -1;
// 	while (data->l[index_1]->cmnds[++i])
// 	{
// 		j = -1;
// 		while (data->l[index_1]->cmnds[i][++j])
// 		{
// 			if (data->l[index_1]->cmnds[i][j])
// 				printf("ELEM: %d:%d | |%s| ", i,
// 					j, data->l[index_1]->cmnds[i][j]);
// 			if (data->l[index_1]->red_cmnd[i][j])
// 				printf("X\n");
// 			else if (data->l[index_1]->binary[i])
// 				printf("X\n");
// 			else
// 				printf("\n");
// 		}
// 		// j = -1;
// 		// if (data->l[index_1]->ops && data->l[index_1]->ops[i])
// 		// {
// 		// 	while (data->l[index_1]->ops[i][++j])
// 		// 		printf("OP:   %d:%d | |%s|\n", i,
// 		// 			j, data->l[index_1]->ops[i][j]);
// 		// }
// 		// if (data->l[index_1]->input)
// 		// printf("PATH: |%s|\n", data->l[index_1]->paths[i]);
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
			&& !one_of_those(d->l[i_1]->ops[i_2][0])
				&& !is_executable(d, i_1, i_2) && get_path(d))
		{
			d->l[i_1]->paths[i_2] = find_path(d, d->l[i_1]->ops[i_2][0]);
			if (!d->l[i_1]->paths[i_2])
				d->l[i_1]->paths[i_2] = ft_strdup(d, "pathnfound");
		}
		else if ((!ft_strncmp(d->l[i_1]->ops[i_2][0], ".", 2)
			|| !one_of_those(d->l[i_1]->ops[i_2][0]))
				&& !one_of_those_2(d->l[i_1]->ops[i_2][0], 0)
				&& check_executable(d, i_1, i_2))
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
		data->l[i]->limit = INT_MAX;
		data->l[i]->ops = NULL;
		data->l[i]->paths = NULL;
		data->l[i]->red_cmnd = NULL;
		data->l[i]->pos = NULL;
		data->l[i]->pipes = NULL;
		data->l[i]->exit_codes = NULL;
		data->l[i]->cmnd_count = 0;
	}
}

int	init_line(t_pipex *data, int i, int limit)
{
	data->l[i]->limit = re_calc_limit(data, limit);
	data->l[i]->cmnd_count
		= count_cmnds(data->line + data->here_2, data->l[i]->limit);
	data->l[i]->exit_codes = ft_calloc(sizeof(int),
			(data->l[i]->cmnd_count), data);
	data->l[i]->ex = INT_MAX;
	init_red_cmnds(data, i);
	data->l[i]->input = ft_calloc(sizeof(char *),
			data->l[i]->cmnd_count + 1, data);
	data->l[i]->binary = ft_calloc(sizeof(int), data->l[i]->cmnd_count, data);
	init_pos_in_line(data, i);
	init_cmnds(data, i, -1);
	handle_here(data, i, -1, 0);
	init_pipes_pids(data, i);
	return (1);
}

void	parsing(t_pipex *data, int i)
{
	init_lines(data, -1);
	make_history(data);
	while (data->l[++i] && data->here_2_old < data->chars_in_line
		&& !g_signal)
	{
		signal_change(NULL, 2);
		if (check_open(data, data->line))
		{
			write(2, "bash: syntax error: open quotes \n", 34);
			data->last_exit_status = 1;
			break ;
		}
		if (syn_red_check_ini(data, i, -1, -1) != -1
			|| !data->l[i]->cmnds[0][0]
			|| !data->l[i]->cmnds[0][0][0])
			continue ;
		init_rest(data, i);
	}
	free_lines(data);
}
