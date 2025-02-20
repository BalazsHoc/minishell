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

void	set_old(t_pipex *data, int index_1, int index_2, int index_3)
{
	int	k;

	k = 0;
	while (data->line[data->l[index_1]->pos[index_2][index_3] + k]
		&& data->line[data->l[
				index_1]->pos[index_2][index_3] + k] != '\n')
		k++;
	if (data->line[data->l[index_1]->pos[index_2][index_3] + k] == '\n')
		k++;
	data->here_2_old = data->l[index_1]->pos[index_2][index_3] + k;
}

int	count_nl(t_pipex *data, int i)
{
	while (data->line[i] && data->line[i] != '\n')
		i++;
	while (data->line[i] && data->line[i] == '\n')
		i++;
	return (i);
}

void	make_history(t_pipex *data)
{
	char	*new;
	int		k;
	int		j;
	int		i;

	i = -1;
	while (data->line[++i])
	{
		k = 0;
		while (data->line[i + k] && data->line[i + k] != '\n')
			k++;
		new = ft_calloc(sizeof(char), (k + 1), data);
		j = -1;
		while (++j < k)
			new[j] = data->line[i + j];
		i += k;
		add_history(new);
		free_str(&new);
		if (!data->line[i])
			break ;
	}
}

void	handle_here_2(t_pipex *data, int index_1, int check, int check_2)
{
	int	this;

	this = 0;
	if (check < 0)
		return ;
	else
	{
		data->buf_int = data->here_2_old;
		if (data->here_2 && ++this)
			set_old(data, index_1, check_2, check);
		find_key(data, index_1, check_2, check + 1);
		data->buf_int = 0;
		if (!this)
			set_old(data, index_1, check_2, check);
	}
}

void	handle_here(t_pipex *data, int index_1, int i, int j)
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
	handle_here_2(data, index_1, check, check_2);
}
