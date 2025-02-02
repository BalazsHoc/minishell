/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmnds_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:55:23 by bhocsak           #+#    #+#             */
/*   Updated: 2025/02/02 14:55:25 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	check_for_quotes(char *str)
{
	int	i;

	i = -1;
	while (str[++i] && !is_delim_front(str, i))
	{
		if (str[i] == 39 || str[i] == 34)
			return (1);
	}
	if (str[i] == 39 || str[i] == 34)
		return (1);
	return (0);
}

int	if_6(t_pipex *data, int j, int open)
{
	if (open || d_in(data, j, open) >= 0)
		return (1);
	return (0);
}

int	if_7(t_pipex *data, int index_1, int index_2, int i)
{
	if (is_red_basic(data, index_1, i, index_2))
		return (1);
	return (0);
}

int	if_8(t_pipex *data, int index_1, int i)
{
	if (data->i_2 > 0
		&& !ft_strncmp(data->l[index_1]->cmnds[i][data->i_2 - 1], "<<", 3))
		return (1);
	return (0);
}

int	if_9(t_pipex *data, int j)
{
	if ((data->open || check_for_quotes(data->line + j)))
		return (1);
	return (0);
}
