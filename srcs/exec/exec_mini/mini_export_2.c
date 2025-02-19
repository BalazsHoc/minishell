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
		if (!track && str[i] == '=' && str[i + 1])
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
	if (!str[i])
		new = ft_strdup(data, str);
	else
		new = malloc_cpy_export(data, str, 0, -1);
	data->buf_array[is_there_2(data, str)] = new;
	free_str(&data->buf_str);
}

void	update_export(t_pipex *data, int index_1, int index_2, int count)
{
	int	i;
	int	j;

	i = 0;
	data->buf_str = NULL;
	while (data->export[i])
		i++;
	data->buf_array = ft_calloc(sizeof(char *), count + i + 1, data);
	count = i;
	while (--i >= 0)
		data->buf_array[i] = ft_strdup(data, data->export[i]);
	j = -1;
	while (data->l[index_1]->ops[index_2][1 + ++j])
	{
		if (u_ex_util_1(data, index_1, index_2, j))
			u_ex_util_2(data, data->l[index_1]->ops[index_2][1 + j]);
		else if ((ft_strlen(data->l[index_1]->ops[index_2][1 + j])
			|| ft_strncmp(data->l[index_1]->ops[index_2][1 + j], "_=", 2))
				&& is_it_last(data, index_1, index_2, 1 + j))
			data->buf_array[count++]
				= malloc_cpy_export(data,
					data->l[index_1]->ops[index_2][1 + j], 0, -1);
	}
	free_list(data->export);
	data->export = data->buf_array;
}
