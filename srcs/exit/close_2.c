/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:47:50 by bhocsak           #+#    #+#             */
/*   Updated: 2025/02/02 14:47:51 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	cl_chi_pipes(t_pipex *data, int index_1, int index_2)
{
	close_childs_p_a(data, index_1);
	close_pipes(data, index_1, index_2);
	close_pipe(data, &data->fd_in);
	return (1);
}

void	close_pipes(t_pipex *data, int index_1, int index_2)
{
	if (data->l[index_1]->fd_infiles)
		close_pipe(data, &data->l[index_1]->fd_infiles[index_2]);
	if (data->l[index_1]->fd_ou)
		close_pipe(data, &data->l[index_1]->fd_ou[index_2]);
}

void	close_pipes_array(t_pipex *data, int index_1)
{
	int	i;

	i = -1;
	if (!data->l[index_1] || !data->l[index_1]->pipes
		|| !data->l[index_1]->pipes[0])
		return ;
	while (++i < data->l[index_1]->cmnd_count)
	{
		if (data->l[index_1]->pipes[i][0] > 0)
			close_pipe(data, &data->l[index_1]->pipes[i][0]);
		if (data->l[index_1]->pipes[i][1] > 0)
			close_pipe(data, &data->l[index_1]->pipes[i][1]);
		if (data->l[index_1]->buf_pipes
			&& data->l[index_1]->buf_pipes[i][0] > 0)
			close_pipe(data, &data->l[index_1]->buf_pipes[i][0]);
		if (data->l[index_1]->buf_pipes
			&& data->l[index_1]->buf_pipes[i][1] > 0)
			close_pipe(data, &data->l[index_1]->buf_pipes[i][1]);
	}
}

void	close_children_pipe(t_pipex *data, int *fd)
{
	if (*fd >= 0 && close(*fd) == -1)
	{
		perror("close");
		er_c(data);
	}
	*fd = -1;
}

void	close_pipe(t_pipex *data, int *fd)
{
	if (fd && *fd > 0 && close(*fd) == -1)
	{
		perror("close");
		er_c(data);
	}
	if (fd)
		*fd = -1;
}
