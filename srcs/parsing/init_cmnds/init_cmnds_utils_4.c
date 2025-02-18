/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmnds_utils_4.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:55:42 by bhocsak           #+#    #+#             */
/*   Updated: 2025/02/02 14:55:43 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	handle_open(t_pipex *data, int j, int *open)
{
	if (!data->line[j])
		return (1);
	if (is_quote_one(data->line[j]) && !*open)
	{
		*open = 1;
		return (0);
	}
	else if (is_q_2(data->line[j]) && !*open)
	{
		*open = 2;
		return (0);
	}
	else if (((is_quote_one(data->line[j]) && *open == 1)
			|| (is_q_2(data->line[j]) && *open == 2)))
	{
		*open = 0;
		return (0);
	}
	return (1);
}

char	*fill_normal(t_pipex *data, int index, int open)
{
	char	*new;
	int		char_count;

	char_count = count_chars(data, index, open, 0);
	new = ft_calloc(sizeof(char), (char_count + 1), data);
	data->buf_int = open;
	ft_strncpy_2(new, data->line + index, char_count, data);
	return (new);
}

void	fill_for_empty(t_pipex *data, int i_1, int index_2, int index_3)
{
	char	*str;

	if (index_3 == 0)
	{
		str = ft_calloc(sizeof(char), (3), data);
		if (!str)
			return (perror("malloc fail\n"), er_c(data));
		str[0] = 39;
		str[1] = 39;
	}
	else
		str = ft_calloc(sizeof(char), (1), data);
	data->l[i_1]->cmnds[index_2][index_3] = str;
}

int	flag_empty(int *this, int pos)
{
	if (pos == 0)
		*this = 1;
	return (1);
}

int	set_pos(int *to_set, int pos)
{
	*to_set = pos;
	return (1);
}
