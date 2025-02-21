/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:51:13 by bhocsak           #+#    #+#             */
/*   Updated: 2025/02/02 14:51:15 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_cmnds(t_pipex *d, int index_1, int i)
{
	d->l[index_1]->cmnds = ft_calloc(sizeof(char **),
			(d->l[index_1]->cmnd_count + 1), d);
	d->l[index_1]->cmnds[d->l[index_1]->cmnd_count] = NULL;
	while (++i < d->l[index_1]->cmnd_count)
	{
		if (!count_elem(d, index_1, i, d->here_2 - 1)
			&& d_in(d, 0, 0) != -1)
		{
			d->l[index_1]->cmnds[i] = ft_calloc(sizeof(char *), (1 + 1), d);
			d->l[index_1]->cmnds[i][0] = ft_calloc(sizeof(char), (1 + 1), d);
		}
		else
		{
			d->l[index_1]->cmnds[i] = ft_calloc(sizeof(char *),
					(count_elem(d, index_1, i, d->here_2 - 1) + 1), d);
			fill_cmnds(d, index_1, i, d->here_2 - 1);
		}
	}
}

void	init_red_cmnds(t_pipex *data, int index_1)
{
	int	j;
	int	count;

	j = -1;
	data->l[index_1]->red_cmnd = ft_calloc(sizeof(int *),
			(data->l[index_1]->cmnd_count + 1), data);
	while (++j < data->l[index_1]->cmnd_count)
	{
		count = 0;
		while (count < count_elem(data, index_1, j, data->here_2 - 1))
			count++;
		data->l[index_1]->red_cmnd[j] = ft_calloc(sizeof(int), (count), data);
	}
}

void	init_pos_in_line(t_pipex *data, int index_1)
{
	int	j;
	int	count;

	j = -1;
	data->l[index_1]->pos = ft_calloc(sizeof(int *),
			(data->l[index_1]->cmnd_count + 1), data);
	while (++j < data->l[index_1]->cmnd_count)
	{
		count = 0;
		while (count < count_elem(data, index_1, j, data->here_2 - 1))
			count++;
		data->l[index_1]->pos[j] = ft_calloc(sizeof(int),
				(count), data);
	}
}

void	init_fds(t_pipex *data, int index)
{
	int	i;

	i = -1;
	while (++i < data->l[index]->cmnd_count)
	{
		data->l[index]->fd_infiles[i] = -1;
		data->l[index]->fd_ou[i] = -1;
		data->l[index]->pipes[i][1] = -1;
		data->l[index]->pipes[i][0] = -1;
		data->l[index]->buf_pipes[i][0] = -1;
		data->l[index]->buf_pipes[i][1] = -1;
		data->l[index]->binary[i] = 0;
	}
}

void	init_pipes_pids(t_pipex *data, int index)
{
	data->l[index]->fd_infiles = ft_calloc(sizeof(int),
			data->l[index]->cmnd_count, data);
	data->l[index]->fd_ou = ft_calloc(sizeof(int),
			data->l[index]->cmnd_count, data);
	data->l[index]->pipes = ft_calloc(sizeof(int) * 2,
			data->l[index]->cmnd_count, data);
	data->l[index]->buf_pipes = ft_calloc(sizeof(int) * 2,
			data->l[index]->cmnd_count, data);
	init_fds(data, index);
	create_pipes(data, index);
	if (data->pid)
	{
		free(data->pid);
		data->pid = NULL;
	}
	data->pid = ft_calloc(sizeof(pid_t), data->l[index]->cmnd_count, data);
}
