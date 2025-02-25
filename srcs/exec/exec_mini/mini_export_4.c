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
		while (data->export[i][check] && data->export[i][check] != '=')
			check++;
		if (!ft_strncmp(str, data->export[i], bigger_one_2(j, check)))
			return (i);
	}
	return (-1);
}

int	is_it_last(t_pipex *d, int i_1, int i_2, int i)
{
	int	j;
	int k;

	k = count_till_equal(d, i_1, i_2, i);
	j = -1;
	while (d->l[i_1]->ops[i_2][++j])
	{
		if (isv(d, i_1, i_2, j) && ((j > i
			&& has_equal(d->l[i_1]->ops[i_2][i])
			&& !ft_strncmp(d->l[i_1]->ops[i_2][j],
			d->l[i_1]->ops[i_2][i], k + 1))
		|| (!has_equal(d->l[i_1]->ops[i_2][i]) &&
			(
				(has_equal(d->l[i_1]->ops[i_2][j]) && j != i && !ft_strncmp(d->l[i_1]->ops[i_2][j], d->l[i_1]->ops[i_2][i], k) && d->l[i_1]->ops[i_2][j][k] == '=')
				|| (!has_equal(d->l[i_1]->ops[i_2][j]) && j > i && !ft_strncmp(d->l[i_1]->ops[i_2][j], d->l[i_1]->ops[i_2][i], bigger_one_2(k, ft_strlen(d->l[i_1]->ops[i_2][j]))))
			))
		|| ((!ft_strncmp(d->l[i_1]->ops[i_2][j],
			d->l[i_1]->ops[i_2][i], k + 1) 
			&& !has_equal(d->l[i_1]->ops[i_2][j])
			&& !has_equal(d->l[i_1]->ops[i_2][i]) && j > i))))
			return (0);
	}
	// printf("CORRECT: %s\n", d->l[i_1]->ops[i_2][i]);
	return (1);
}

int	has_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
		return (i + 1);
	return (0);
}
