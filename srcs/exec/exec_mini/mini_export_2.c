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

char	*malloc_cpy_export_continue(char *new, char *str, int count)
{
	int	i;

	i = -1;
	while (str[++i] && (i == 0 || (str[i - 1] != '=')))
		new[i] = str[i];
	new[i--] = 34;
	count = 0;
	while (str[++i])
	{
		if (str[i] == 34)
			new[i + 1 + count++] = 92;
		new[i + 1 + count] = str[i];
	}
	new[i + 1 + count] = 34;
	return (new);
}

char	*malloc_cpy_export(t_pipex *data, char *str, int track, int i)
{
	char	*new;
	int		count;

	new = NULL;
	count = 0;
	while (str[++i])
	{
		count++;
		if (!track && str[i] == '=')
			track = 1;
		if (str[i] == 34)
			count++;
	}
	if (!track)
		return (ft_strdup(data, str));
	else if (track == 1)
		new = ft_calloc(sizeof(char), (count + 2 + 1), data);
	return (malloc_cpy_export_continue(new, str, count));
}

int	u_ex_util_1(t_pipex *data, int index_1, int index_2, int j)
{
	if (ft_strncmp(data->l[index_1]->ops[index_2][1 + j], "_=", 2)
		&& is_there_2(data, data->l[index_1]->ops[index_2][1 + j]) != -1
		&& is_it_last(data, index_1, index_2, 1 + j))
		return (1);
	return (0);
}

void	u_ex_util_2(t_pipex *data, char *str)
{
	int		i;
	char	*new;

	i = 0;
	new = NULL;
	data->buf_str = data->buf_array[is_there_2(data, str)];
	while (str[i] && str[i] != '=')
		i++;
	if (is_shlvl(str))
		new = ft_strdup(data, "SHLVL=\"1\"");
	else if (!str[i])
		new = ft_strdup(data, str);
	else
		new = malloc_cpy_export(data, str, 0, -1);
	data->buf_array[is_there_2(data, str)] = new;
	free_str(&data->buf_str);
}

void	update_export(t_pipex *d, int i_1, int i_2, int count)
{
	int	i;
	int	j;

	d->buf_str = NULL;
	i = malloc_for_list(d, count);
	j = i;
	while (--i >= 0)
		d->buf_array[i] = ft_strdup(d, d->export[i]);
	i = j;
	j = -1;
	while (d->l[i_1]->ops[i_2][1 + ++j])
	{
		if (!isv(d, i_1, i_2, 1 + j))
			continue ;
		if (u_ex_util_1(d, i_1, i_2, j)
			|| is_shlvl(d->l[i_1]->ops[i_2][1 + j]))
			u_ex_util_2(d, d->l[i_1]->ops[i_2][1 + j]);
		else if ((ft_strlen(d->l[i_1]->ops[i_2][1 + j])
			|| ft_strncmp(d->l[i_1]->ops[i_2][1 + j], "_=", 2))
				&& is_it_last(d, i_1, i_2, 1 + j) && count--)
			d->buf_array[i++] = malloc_cpy_export(d,
					d->l[i_1]->ops[i_2][1 + j], 0, -1);
	}
	free_list(d->export);
	d->export = d->buf_array;
}
