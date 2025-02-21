/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:47:43 by bhocsak           #+#    #+#             */
/*   Updated: 2025/02/02 14:47:45 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	close_childs_p_a(t_pipex *data, int index_1)
{
	int	i;

	i = -1;
	if (!data->l[index_1] || !data->l[index_1]->pipes
		|| !data->l[index_1]->pipes[0])
		return ;
	while (++i < data->l[index_1]->cmnd_count)
	{
		if (data->l[index_1]->pipes[i][0] >= 0)
			close_children_pipe(data, &data->l[index_1]->pipes[i][0]);
		if (data->l[index_1]->pipes[i][1] >= 0)
			close_children_pipe(data, &data->l[index_1]->pipes[i][1]);
		if (data->l[index_1]->buf_pipes
			&& data->l[index_1]->buf_pipes[i][0] >= 0)
			close_children_pipe(data, &data->l[index_1]->buf_pipes[i][0]);
		if (data->l[index_1]->buf_pipes
			&& data->l[index_1]->buf_pipes[i][1] >= 0)
			close_children_pipe(data, &data->l[index_1]->buf_pipes[i][1]);
	}
}

void	close_buf_pipes(t_pipex *data, int index_1, int index_2)
{
	if (data->l[index_1]->buf_pipes[index_2][0] > 0)
		close_pipe(data, &data->l[index_1]->buf_pipes[index_2][0]);
	if (data->l[index_1]->buf_pipes[index_2][1] > 0)
		close_pipe(data, &data->l[index_1]->buf_pipes[index_2][1]);
}

void	create_pipes(t_pipex *data, int index)
{
	int	i;

	i = -1;
	while (++i < data->l[index]->cmnd_count)
	{
		data->l[index]->pipes[i][0] = -1;
		data->l[index]->pipes[i][1] = -1;
	}
	i = -1;
	while (++i < data->l[index]->cmnd_count)
	{
		if (pipe(data->l[index]->pipes[i]) == -1)
		{
			perror("pipe");
			data->l[index]->pipes[i][0] = -1;
			data->l[index]->pipes[i][1] = -1;
			er_c(data);
		}
	}
}

void	create_buf_pipe(t_pipex *data, int index_1, int index_2)
{
	if (pipe(data->l[index_1]->buf_pipes[index_2]) == -1)
	{
		perror("pipe");
		er_c(data);
	}
}

void	close_everything(t_pipex *data, int index_1)
{
	int	i;

	i = -1;
	if (!data || !data->l || !data->l[index_1])
		return ;
	while (++i < data->l[index_1]->cmnd_count)
		close_pipes(data, index_1, i);
	close_pipes_array(data, index_1);
}
