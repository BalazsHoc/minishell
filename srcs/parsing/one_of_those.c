/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_of_those.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:52:19 by bhocsak           #+#    #+#             */
/*   Updated: 2025/02/02 14:52:21 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	one_of_those_2(t_pipex *data, int index_1, int index_2, int i)
{
	if (data->l[index_1]->ops[index_2][0][i + 1]
		&& !one_of_those_2(data, index_1, index_2, i + 1))
		return (0);
	else if (!data->l[index_1]->ops[index_2][0][i]
		|| data->l[index_1]->ops[index_2][0][i] == '.'
		|| data->l[index_1]->ops[index_2][0][i] == '/')
		return (1);
	else
		return (0);
}

int	one_of_those_3(char *str)
{
	if (!ft_strncmp(str, "/usr", 4)
		|| (!ft_strncmp(str, "/snap", 5))
		|| (!ft_strncmp(str, "/bin", 4))
		|| (!ft_strncmp(str, "/sbin", 5)))
		return (1);
	return (0);
}

int	one_of_those(t_pipex *data, int index_1, int index_2)
{
	if (!ft_strncmp(data->l[index_1]->ops[index_2][0], "/", 2)
		|| !ft_strncmp(data->l[index_1]->ops[index_2][0], ".", 2)
		|| (!ft_strncmp(data->l[index_1]->ops[index_2][0], "/usr", 4)
		&& one_of_those_2(data, index_1, index_2, 4))
		|| (!ft_strncmp(data->l[index_1]->ops[index_2][0], "/bin", 4)
		&& (one_of_those_2(data, index_1, index_2, 4)))
		|| (!ft_strncmp(data->l[index_1]->ops[index_2][0], "/sbin", 5)
		&& one_of_those_2(data, index_1, index_2, 5))
		|| (!ft_strncmp(data->l[index_1]->ops[index_2][0], "/snap", 5)
		&& one_of_those_2(data, index_1, index_2, 5)))
		return (1);
	return (0);
}
