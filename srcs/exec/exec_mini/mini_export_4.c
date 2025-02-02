/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:34:15 by bhocsak           #+#    #+#             */
/*   Updated: 2025/02/02 14:34:17 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	env_count(t_pipex *data)
{
	int	i;

	i = 0;
	while (data->cur_env[i])
		i++;
	return (i);
}

int	already_there(t_pipex *data, char *str)
{
	int	i;
	int	j;

	j = 0;
	i = -1;
	while (str[j] && str[j] != '=')
		j++;
	while (data->cur_env[++i])
	{
		if (!ft_strncmp(str, data->cur_env[i], j + 1)
			&& data->cur_env[i][j] == '=')
			return (i);
	}
	return (-1);
}

int	is_there_2(t_pipex *data, char *str)
{
	int	i;
	int	j;
	int	check;

	j = 0;
	i = -1;
	while (str[j] && str[j] != '=')
		j++;
	while (data->export[++i])
	{
		check = 0;
		while (data->export[i][check])
			check++;
		if (!ft_strncmp(str, data->export[i], j + 1)
			|| (str[j] == '=' && !ft_strncmp(str, data->export[i], j - 1)
				&& j <= check && data->export[i][j] == 0))
			return (i);
	}
	return (-1);
}

int	is_it_last(t_pipex *data, int index_1, int index_2, int i)
{
	int	j;
	int	count;
	int	check;

	count = 0;
	while (data->l[index_1]->ops[index_2][i][count]
		&& data->l[index_1]->ops[index_2][i][count] != '=')
		count++;
	j = -1;
	check = 0;
	while (data->l[index_1]->ops[index_2][++j])
	{
		if (!ft_strncmp(data->l[index_1]->ops[index_2][j],
			data->l[index_1]->ops[index_2][i], count + 1))
			check = j;
	}
	if (check == i)
		return (1);
	return (0);
}

int	has_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
		return (1);
	return (0);
}
