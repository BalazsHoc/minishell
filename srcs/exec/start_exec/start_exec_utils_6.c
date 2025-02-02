/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec_utils_6.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:39:24 by bhocsak           #+#    #+#             */
/*   Updated: 2025/02/02 14:39:43 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	is_red_inline(t_pipex *data, int index_1, int index_2)
{
	int	i;
	int	check;

	i = -1;
	check = -1;
	while (data->l[index_1]->cmnds[index_2]
		&& data->l[index_1]->cmnds[index_2][++i])
	{
		if (!ft_strncmp(data->l[index_1]->cmnds[index_2][i], "<", 2))
			check = i;
		if (!ft_strncmp(data->l[index_1]->cmnds[index_2][i], "<<", 3))
			check = i;
	}
	return (check);
}

int	bigger_one_2(int j, int i)
{
	if (i > j)
		return (i);
	return (j);
}

int	is_valid_in(t_pipex *data, int index_1, int index_2)
{
	int	i;
	int	fd;
	int	check;

	i = -1;
	fd = -1;
	check = 0;
	while (data->l[index_1]->cmnds[index_2][++i])
	{
		if (!ft_strncmp(data->l[index_1]->cmnds[index_2][i], "<", 2)
			&& !data->l[index_1]->red_cmnd[index_2][i] && data->l[
					index_1]->cmnds[index_2][i + 1]
			&& data->l[index_1]->red_cmnd[index_2][i] == 0)
		{
			fd = open(data->l[index_1]->cmnds[index_2][i + 1], O_RDONLY);
			if (fd == -1)
				return (-1);
			check = i + 1;
			close_pipe(data, &fd);
		}
	}
	return (check);
}

int	check_cmnd_as_dir(t_pipex *data, int index, int i)
{
	char	*buf_1;
	char	*buf_2;
	int		j;

	j = 0;
	buf_1 = NULL;
	buf_2 = NULL;
	while (data->l[index]->ops[i][0] && data->l[index]->ops[i][0][j])
		j++;
	if (is_mini_2(data, index, i))
		return (1);
	else if (j > 1 && data->l[index]->ops[i][0][j - 1] == '/'
		&& one_of_those_3(data->l[index]->ops[i][0]))
	{
		buf_1 = ft_strdup_2(data, data->l[index]->ops[i][0]);
		buf_2 = find_path(data, buf_1);
		if (buf_2)
			return (free_str(&buf_1), free_str(&buf_2), 1);
		return (free_str(&buf_1), free_str(&buf_2), 0);
	}
	return (0);
}

int	check_key(t_pipex *data, char *cur)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	k = 0;
	while (cur[k] && is_char(cur[k]))
		k++;
	while (data->cur_env[++i])
	{
		j = 0;
		while (data->cur_env[i][j] && data->cur_env[i][j] != '=')
			j++;
		if (!ft_strncmp(data->cur_env[i], cur, bigger_one_2(j, k)))
			return (j);
	}
	return (k);
}
