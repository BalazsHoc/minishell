/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec_utils_5.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:39:13 by bhocsak           #+#    #+#             */
/*   Updated: 2025/02/02 14:39:16 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	first_invalid_in(t_pipex *data, int index_1, int index_2)
{
	int	i;
	int	fd;

	i = -1;
	fd = -1;
	while (data->l[index_1]->cmnds[index_2][++i])
	{
		if (!ft_strncmp(data->l[index_1]->cmnds[index_2][i], "<", 2)
			&& data->l[index_1]->cmnds[index_2][i + 1]
			&& data->l[index_1]->red_cmnd[index_2][i] == 0)
		{
			close_pipe(data, &fd);
			fd = open(data->l[index_1]->cmnds[index_2][i + 1], O_RDONLY);
			if (fd == -1)
				return (i + 1);
		}
	}
	close_pipe(data, &fd);
	return (0);
}

int	first_invalid_out(t_pipex *data, int index_1, int index_2)
{
	int	i;
	int	fd;

	i = -1;
	fd = -1;
	while (data->l[index_1]->cmnds[index_2][++i])
	{
		if ((!ft_strncmp(data->l[index_1]->cmnds[index_2][i], ">>", 3)
			|| !ft_strncmp(data->l[index_1]->cmnds[index_2][i], ">", 2))
			&& data->l[index_1]->cmnds[index_2][i + 1]
				&& data->l[index_1]->red_cmnd[index_2][i] == 0)
		{
			close_pipe(data, &fd);
			fd = open(data->l[index_1]->cmnds[index_2][i + 1],
					O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
				return (i + 1);
		}
	}
	close_pipe(data, &fd);
	return (i);
}

int	open_out_util_1(t_pipex *data, int index_1, int index_2)
{
	if (is_valid_in(data, index_1, index_2) == -1
		&& first_invalid_in(data, index_1, index_2)
		< first_invalid_out(data, index_1, index_2))
		return (1);
	return (0);
}

void	open_out_util_2(t_pipex *data, int index_1, int index_2, int i)
{
	write(2, "bash: ", 7);
	write(2, data->l[index_1]->cmnds[index_2][i + 1],
		ft_strlen(data->l[index_1]->cmnds[index_2][i + 1]));
	write(2, ": ", 3);
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 2);
	exit_child(data, index_1, index_2, 1);
}

int	open_out(t_pipex *d, int i_1, int i_2)
{
	int	i;
	int	fd;

	i = -1;
	fd = -1;
	if (open_out_util_1(d, i_1, i_2))
		return (-1);
	while (d->l[i_1]->cmnds[i_2][++i])
	{
		if ((!ft_strncmp(d->l[i_1]->cmnds[i_2][i], ">>", 3)
			|| !ft_strncmp(d->l[i_1]->cmnds[i_2][i], ">", 2))
				&& d->l[i_1]->red_cmnd[i_2][i] == 0)
		{
			close_pipe(d, &fd);
			if (!ft_strncmp(d->l[i_1]->cmnds[i_2][i], ">>", 3))
				fd = open(d->l[i_1]->cmnds[i_2][i + 1],
						O_WRONLY | O_CREAT | O_APPEND, 0644);
			else
				fd = open(d->l[i_1]->cmnds[i_2][i + 1 + if_th(d, i_1, i_2, i)],
						O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				return (open_out_util_2(d, i_1, i_2, i), -2);
		}
	}
	return (fd);
}
