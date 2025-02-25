/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_is_4.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:18:47 by bhocsak           #+#    #+#             */
/*   Updated: 2025/02/11 15:18:48 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_paths_3(t_pipex *d, int i, int j, int k)
{
	while (d->l[i]->paths[++j])
	{
		if (!d->l[i]->binary[j]
			&& d->l[i]->paths[j][0] == '.' && d->l[i]->paths[j][1] == '/')
		{
			d->buf_str = d->l[i]->paths[j];
			d->l[i]->paths[j] = ft_strdup(d, "/bin/bash");
			free_str(&d->buf_str);
			d->buf_int = 0;
			while (d->l[i]->ops[j][d->buf_int])
				d->buf_int++;
			d->buf_array = ft_calloc(sizeof(char *), d->buf_int + 1 + 1, d);
			k = -1;
			while (++k < d->buf_int + 1)
			{
				if (k == 0)
					d->buf_array[k] = ft_strdup(d, "/bin/bash");
				else
					d->buf_array[k] = ft_strdup(d, d->l[i]->ops[j][k - 1]);
			}
			free_list(d->l[i]->ops[j]);
			d->l[i]->ops[j] = d->buf_array;
		}
	}
}

void	update_op_path(t_pipex *data, int i, int j, int k)
{
	int		l;
	char	**arr;

	free_str(&data->l[i]->paths[j]);
	data->l[i]->paths[j] = ft_strdup(data, data->l[i]->ops[j][k]);
	l = 0;
	while (data->l[i]->ops[j][l])
		l++;
	arr = ft_calloc(sizeof(char *), l - k + 1, data);
	l = -1;
	while (data->l[i]->ops[j][k + ++l])
		arr[l] = data->l[i]->ops[j][k + l];
	free_str(data->l[i]->ops[j]);
	data->l[i]->ops[j] = arr;
}

void	init_paths_2(t_pipex *data, int i)
{
	int	j;
	int	k;

	j = -1;
	while (data->l[i]->ops[++j])
	{
		k = -1;
		while (data->l[i]->ops[j][++k])
		{
			if (!access(data->l[i]->ops[j][k], X_OK)
				&& !one_of_those(data->l[i]->ops[j][k])
				&& (!ft_strncmp(data->l[i]->ops[j][0], "env", 4)
				|| !ft_strncmp(data->l[i]->ops[j][0], "/bin/env", 9)
				|| !ft_strncmp(data->l[i]->ops[j][0], "/usr/bin/env", 13))
				&& (!ft_strncmp(data->l[i]->ops[j][k], "../", 3)
					|| !ft_strncmp(data->l[i]->ops[j][k], "./", 2)))
				return (update_op_path(data, i, j, k));
			else
				errno = data->last_exit_status;
		}
	}
}

void	init_rest(t_pipex *data, int i)
{
	init_ops(data, i);
	init_paths(data, i, -1);
	init_paths_3(data, i, -1, -1);
	init_paths_2(data, i);
	check_ambigious(data, i);
	check_folder(data, i, -1, -1);
	start_exec(data, i, -1, 0);
}

int	set_err_old(t_pipex *data)
{
	data->here_2_old = count_nl(data, data->here_2_old);
	return (1);
}
