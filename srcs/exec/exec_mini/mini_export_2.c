/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:33:30 by bhocsak           #+#    #+#             */
/*   Updated: 2025/02/02 14:33:45 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	u_ex_util_3(t_pipex *data, char *str)
{
	char	*new;

	new = NULL;
	data->buf_str = data->buf_array[is_there_2(data, str)];
	if (is_shlvl(str))
		new = ft_strdup(data, "SHLVL=\"1\"");
	else if (!has_equal(str))
		return ;
	else
		new = malloc_cpy_export(data, str, 0, -1);
	data->buf_array[is_there_2(data, str)] = new;
	free_str(&data->buf_str);
}

int	u_ex_util_2(t_pipex *data, int index_1, int index_2, int j)
{
	if (ft_strncmp(data->l[index_1]->ops[index_2][j], "_=", 2)
		&& is_there_2(data, data->l[index_1]->ops[index_2][j]) != -1
		&& is_it_last(data, index_1, index_2, j))
		return (1);
	return (0);
}

int	u_ex_util_1(t_pipex *d, int i_1, int i_2, int j)
{
	if (*d->l[i_1]->ops[i_2][j] && is_there_2(
			d, d->l[i_1]->ops[i_2][j]) == -1
			&& ft_strncmp(d->l[i_1]->ops[i_2][j],
				"_=", 2) && !is_shlvl(d->l[i_1]->ops[i_2][j])
				&& is_it_last(d, i_1, i_2, j))
		return (1);
	return (0);
}

void	update_export(t_pipex *d, int i_1, int i_2, int count)
{
	int	j;

	d->buf_str = NULL;
	d->buf_int = malloc_for_list(d, count);
	j = d->buf_int;
	while (--d->buf_int >= 0)
		d->buf_array[d->buf_int] = ft_strdup(d, d->export[d->buf_int]);
	d->buf_int = j;
	j = -1;
	while (d->l[i_1]->ops[i_2][1 + ++j])
	{
		if (!isv(d, i_1, i_2, 1 + j))
			continue ;
		if (u_ex_util_1(d, i_1, i_2, 1 + j) && count--)
			d->buf_array[d->buf_int++] = malloc_cpy_export(d,
					d->l[i_1]->ops[i_2][1 + j], 0, -1);
		else if (u_ex_util_2(d, i_1, i_2, 1 + j)
			|| is_shlvl(d->l[i_1]->ops[i_2][1 + j]))
			u_ex_util_3(d, d->l[i_1]->ops[i_2][1 + j]);
	}
	free_list(d->export);
	d->export = d->buf_array;
}
