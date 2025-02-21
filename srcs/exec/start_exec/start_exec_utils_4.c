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
	if (!arr || !*arr)
		return (0);
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
		&& data->line[data->l[index_1]->pos[data->l[
				index_1]->cmnd_count - 1][last_one(data->l[
						index_1]->cmnds[data->l[
								index_1]->cmnd_count - 1])] + i]
			&& (((size_t)i <= ft_strlen(data->l[index_1]->cmnds[data->l[
								index_1]->cmnd_count - 1][
									last_one(data->l[index_1]->cmnds[
					data->l[index_1]->cmnd_count - 1])])
					&& data->line[data->l[index_1]->pos[
					data->l[index_1]->cmnd_count - 1][
					last_one(data->l[index_1]->cmnds[
					data->l[index_1]->cmnd_count - 1])] + i]
						== data->l[index_1]->cmnds[data->l[
								index_1]->cmnd_count - 1][
									last_one(data->l[index_1]->cmnds[
					data->l[index_1]->cmnd_count - 1])][i])
						|| data->line[data->l[index_1]->pos[
					data->l[index_1]->cmnd_count - 1][
					last_one(data->l[index_1]->cmnds[
					data->l[index_1]->cmnd_count - 1])] + i] != '\n'))
		return (1);
	return (0);
}

void	set_here_continue(t_pipex *data, int index_1, int i, int check)
{
	int	lol;

	lol = data->here_2;
	if (check == -1 && data->l[index_1]->cmnds[0][0][0]
		&& (i == 1 || data->l[index_1]->cmnds[i]))
	{
		i = 0;
		while (set_here_util_2(data, index_1, i))
			i++;
		data->here_2 = data->l[index_1]->pos[data->l[
			index_1]->cmnd_count - 1][last_one(data->l[
				index_1]->cmnds[data->l[index_1]->cmnd_count - 1])] + i + 1;
		data->here_2_old = data->l[index_1]->pos[data->l[
			index_1]->cmnd_count - 1][last_one(data->l[
				index_1]->cmnds[data->l[index_1]->cmnd_count - 1])] + i + 1;
		if (lol == data->here_2)
			data->here_2_old = count_nl(data, index_1);
	}
	else if (check >= 0 && data->l[index_1]->cmnd_count)
		data->here_2_old = find_key(data, index_1, i, check + 1);
	while (data->here_2 && data->line[data->here_2 - 1]
		&& data->line[data->here_2] && data->here_2 < data->chars_in_line
		&& (data->line[data->here_2] == '\n'
			|| is_space(data->line[data->here_2])) && ++data->here_2)
		data->here_2_old++;
}

int	set_here(t_pipex *data, int index_1)
{
	int	i;
	int	j;
	int	check;
	int	check_2;

	i = -1;
	check = -1;
	check_2 = 0;
	while (++i != INT_MIN && set_here_util_1(data, index_1, i))
	{
		j = -1;
		while (data->l[index_1]->cmnds[i][++j] && data->l[index_1]->ex > i)
		{
			if (!ft_strncmp(data->l[index_1]->cmnds[i][j], "<<", 3)
				&& !data->l[index_1]->red_cmnd[i][j])
			{
				check = j;
				check_2 = i;
			}
		}
		j = 0;
	}
	set_here_continue(data, index_1, check_2, check);
	return (1);
}
