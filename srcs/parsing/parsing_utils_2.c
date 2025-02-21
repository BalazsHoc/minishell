/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_is_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:53:12 by bhocsak           #+#    #+#             */
/*   Updated: 2025/02/02 14:53:13 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_red_in(char *str, int index)
{
	if (!ft_strncmp(str + index, "<", 1) || !ft_strncmp(str + index, "<<", 2))
		return (1);
	return (0);
}

int	is_red_out(char *str, int index)
{
	if (!ft_strncmp(str + index, ">", 1) || !ft_strncmp(str + index, ">>", 2))
		return (1);
	return (0);
}

int	is_red(t_pipex *data, int index_1, int index_2, int index_3)
{
	if (index_2 < 0 || !data->l[index_1]->cmnds[index_2]
		|| !data->l[index_1]->cmnds[index_2][index_3])
		return (0);
	if ((!ft_strncmp(data->l[index_1]->cmnds[index_2][index_3], "<<", 3)
		|| !ft_strncmp(data->l[index_1]->cmnds[index_2][index_3], ">", 2)
		|| !ft_strncmp(data->l[index_1]->cmnds[index_2][index_3], "<", 2)
		|| !ft_strncmp(data->l[index_1]->cmnds[index_2][index_3], ">>", 3))
		&& data->l[index_1]->red_cmnd[index_2][index_3] == 0)
		return (1);
	return (0);
}

int	is_red_basic(t_pipex *data, int index_1, int index_2, int index_3)
{
	if (index_3 < 0 || !data->l[index_1] || !data->l[index_1]->cmnds[index_2]
		|| !data->l[index_1]->cmnds[index_2][index_3])
		return (0);
	if ((!ft_strncmp(data->l[index_1]->cmnds[index_2][index_3], "<<", 3)
		|| !ft_strncmp(data->l[index_1]->cmnds[index_2][index_3], ">", 2)
		|| !ft_strncmp(data->l[index_1]->cmnds[index_2][index_3], "<", 2)
		|| !ft_strncmp(data->l[index_1]->cmnds[index_2][index_3], ">>", 3)))
		return (1);
	return (0);
}

int	is_red_1(char c)
{
	if (c == '>' || c == '<')
		return (1);
	return (0);
}
