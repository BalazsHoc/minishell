/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmnds_exp_count_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:55:00 by bhocsak           #+#    #+#             */
/*   Updated: 2025/02/02 14:55:02 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	count_elem_spaces(t_pipex *data, char *elem)
{
	int	i;
	int	count;

	count = 0;
	if (!elem || !*elem)
		return (0);
	i = 0;
	while (elem[i] && elem[i] == ' ')
		i++;
	i = -1;
	data->count_elem++;
	while (elem[++i])
	{
		if (elem[i] == '\n' && (i > 0 && elem[i + 1]))
			data->count_elem++;
		if (elem[i] == '\n')
			count++;
	}
	return (count);
}

void	c_e_3(t_pipex *data, char **elem, int *i)
{
	data->buf_str = get_val(data, data->line + *i + 1);
	*elem = ft_calloc(sizeof(char), ft_strlen_2(data->buf_str) + 1, data);
	ft_strncpy_4(elem, data->buf_str, ft_strlen_2(data->buf_str));
	free_str(&data->buf_str);
	if (check_key(data, data->line + *i + 1))
		*i += check_key(data, data->line + *i + 1) + 1;
	else
		*i += count_chars_2(data, *i);
}

void	c_e_4(char **elem, int *count)
{
	if (!*elem)
		return ;
	*count += ft_strlen_2(*elem);
	free_str(&*elem);
}

int	c_e_5(t_pipex *data, int i, int open)
{
	if (!open && (!data->line[i] || is_space(data->line[i])
			|| data->line[i] == '\n'
			|| is_real_pipe(data->line, i)
			|| is_red_clean(data->line, i)
			|| (data->line[i + 1] && is_space(data->line[i])
				&& is_quote(data->line[i + 1]))
			|| ((data->line[i + 1] && (is_delim_front(data->line, i + 1)))
				&& (data->line[i + 1] && (!data->line[i + 2]
						|| is_space(data->line[i + 2])
						|| data->line[i + 2] == '\n')
					&& is_quote(data->line[i + 1])))))
		return (1);
	return (0);
}

int	c_e_6(t_pipex *data, int i, int open)
{
	if (data->line[i] && (((data->line[i] != '$' || (data->line[i] == '$'
						&& is_delim_front(data->line, i + 1)))
				&& !open) || open)
		&& ((!is_quote(data->line[i]))
			|| ((open == 1 && is_q_2(data->line[i]))
				|| (open == 2 && is_quote_one(data->line[i])))))
		return (1);
	return (0);
}
