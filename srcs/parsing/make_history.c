/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:52:01 by bhocsak           #+#    #+#             */
/*   Updated: 2025/02/02 14:52:02 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_nl(t_pipex *data)
{
	int	i;

	i = 0;
	while (data->line[i + data->here_2] && data->line[i + data->here_2] != '\n')
		i++;
	return (i);
}

void	make_history_3(t_pipex *data, int i)
{
	char	*new;
	int		j;

	data->buf_int = 0;
	if (i == 0)
	{
		i = count_nl(data);
		data->buf_int = data->here_2_old;
	}
	else if (i == data->buf_int)
		data->buf_int = 0;
	new = ft_calloc(sizeof(char), (i + 1), data);
	j = -1;
	while (++j < i)
		new[j] = data->line[data->buf_int + j];
	add_history(new);
	free_str(&new);
}

void	set_old(t_pipex *data, int index_1, int index_2, int index_3)
{
	int	k;

	k = 0;
	while (data->line[data->l[index_1]->pos_in_line[index_2][index_3] + k]
		&& data->line[data->l[
				index_1]->pos_in_line[index_2][index_3] + k] != '\n')
		k++;
	if (data->line[data->l[index_1]->pos_in_line[index_2][index_3] + k] == '\n')
		k++;
	data->here_2_old = data->l[index_1]->pos_in_line[index_2][index_3] + k;
}

void	make_history_2(t_pipex *data, int index_1, int check, int check_2)
{
	if (check < 0)
		make_history_3(data, 0);
	else
	{
		data->buf_int = data->here_2_old;
		set_old(data, index_1, check_2, check);
		find_key(data, index_1, check_2, check + 1);
		check = data->here_2 - data->buf_int - 1;
		make_history_3(data, check + 1);
		data->buf_int = 0;
	}
}

void	make_history(t_pipex *data, int index_1, int i, int j)
{
	int	check;
	int	check_2;

	check = -1;
	check_2 = -1;
	while (data->l[index_1]->cmnds[++i])
	{
		j = -1;
		while (data->l[index_1]->cmnds[i][++j])
		{
			if (!ft_strncmp(data->l[index_1]->cmnds[i][j], "<<", 3)
				&& !data->l[index_1]->red_cmnd[i][j])
			{
				check = j;
				check_2 = i;
			}
		}
	}
	make_history_2(data, index_1, check, check_2);
}
