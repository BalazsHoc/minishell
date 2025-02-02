/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec_utils_4.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:39:00 by bhocsak           #+#    #+#             */
/*   Updated: 2025/02/02 14:39:04 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	last_one(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	if (i > 0)
		return (i - 1);
	return (0);
}

int	set_here_util_1(t_pipex *data, int index_1, int i)
{
	if (data->l[index_1]->cmnds[i] && data->l[index_1]->cmnds[i][0]
		&& data->l[index_1]->cmnds[i][0][0] && data->l[index_1]->cmnds[i][0][1]
		&& !is_quote_one(data->l[index_1]->cmnds[i][0][0])
			&& !is_quote_one(data->l[index_1]->cmnds[i][0][1]))
		return (1);
	return (0);
}

int	set_here_util_2(t_pipex *data, int index_1, int i)
{
	if (!(is_quote_one(data->l[index_1]->cmnds[0][0][0])
		&& is_quote_one(data->l[index_1]->cmnds[0][0][1] == 34))
		&& data->line[data->l[index_1]->pos_in_line[data->l[
				index_1]->cmnd_count - 1][last_one(data->l[
						index_1]->cmnds[data->l[
								index_1]->cmnd_count - 1])] + i]
			&& data->line[data->l[index_1]->pos_in_line[
					data->l[index_1]->cmnd_count - 1][
					last_one(data->l[index_1]->cmnds[
					data->l[index_1]->cmnd_count - 1])] + i] != '\n')
		return (1);
	return (0);
}

void	set_here_continue(t_pipex *data, int index_1, int i, int check)
{
	if (!check && data->l[index_1]->cmnds[0][0][0])
	{
		i = 0;
		while (set_here_util_2(data, index_1, i))
			i++;
		data->here_2 = data->l[index_1]->pos_in_line[data->l[
			index_1]->cmnd_count - 1][last_one(data->l[
				index_1]->cmnds[data->l[index_1]->cmnd_count - 1])] + i + 1;
		data->here_2_old = data->l[index_1]->pos_in_line[data->l[
			index_1]->cmnd_count - 1][last_one(data->l[
				index_1]->cmnds[data->l[index_1]->cmnd_count - 1])] + i + 1;
	}
	else if (check && data->l[index_1]->cmnd_count)
		data->here_2_old = find_key(data, index_1, i, check + 1);
}

void	set_here(t_pipex *data, int index_1)
{
	int	i;
	int	j;
	int	check;

	i = -1;
	check = 0;
	while (!check && ++i != INT_MIN && set_here_util_1(data, index_1, i))
	{
		j = -1;
		while (data->l[index_1]->cmnds[i][++j])
		{
			if (!ft_strncmp(data->l[index_1]->cmnds[i][j], "<<", 3)
				&& !data->l[index_1]->red_cmnd[i][j])
			{
				check = j;
				break ;
			}
		}
		j = 0;
	}
	set_here_continue(data, index_1, i, check);
}
