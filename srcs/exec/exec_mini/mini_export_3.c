/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:34:04 by bhocsak           #+#    #+#             */
/*   Updated: 2025/02/02 14:34:05 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	rand_it(t_pipex *data, int index_1, int index_2, int i)
{
	return ((int)((INT_MAX / data->l[index_1]->ops[index_2][i + 1][
		ft_strlen(data->l[index_1]->ops[index_2][i + 1]) - 1])
			% (env_count(data) + 1)));
}

int	rand_it_2(t_pipex *data, int index_1, int index_2, int i)
{
	return (((data->l[index_1]->ops[index_2][i + 1][0] / data->l[
			index_1]->ops[index_2][i + 1][ft_strlen(data->l[
			index_1]->ops[index_2][i + 1]) - 1]) - 1) % (env_count(data) + 1));
}

int	export_env_util_1(t_pipex *data, int index_1, int index_2, int i)
{
	if (ft_strncmp(data->l[index_1]->ops[index_2][1 + i], "_=", 2)
		&& already_there(data, data->l[index_1]->ops[index_2][i + 1]) != -1
			&& is_it_last(data, index_1, index_2, i + 1))
		return (1);
	return (0);
}

void	export_env_util_2(t_pipex *data, char *str)
{
	data->buf_str = data->cur_env[already_there(data, str)];
	data->cur_env[already_there(data, str)] = ft_strdup(data, str);
	free_str(&data->buf_str);
}

void	export_env(t_pipex *d, int i_1, int i_2, int count)
{
	int		i;
	int		rand;
	char	**buf;

	buf = ft_calloc(sizeof(char *), count + count_env(d->cur_env) + 1, d);
	rand = 0;
	i = -1;
	d->buf_str = NULL;
	while (d->l[i_1]->ops[i_2][++i + 1])
	{
		// printf("THIS: %s\n", d->l[i_1]->ops[i_2][i + 1]);
		if (!has_equal(d->l[i_1]->ops[i_2][i + 1]) || !isv(d, i_1, i_2, i + 1))
			continue ;
		// printf("THIS2: %s\n", d->l[i_1]->ops[i_2][i + 1]);
		if (rand != rand_it(d, i_1, i_2, i))
			rand = rand_it(d, i_1, i_2, i);
		else
			rand = rand_it_2(d, i_1, i_2, i);
		if (export_env_util_1(d, i_1, i_2, i))
			export_env_util_2(d, d->l[i_1]->ops[i_2][i + 1]);
		else if (ft_strncmp(d->l[i_1]->ops[i_2][1 + i], "_=", 2)
			&& is_it_last(d, i_1, i_2, i + 1) && count--)
			buf[rand] = ft_strdup(d, d->l[i_1]->ops[i_2][i + 1]);
	}
	set_rest(d, buf);
	free(d->cur_env);
	d->cur_env = buf;
}
