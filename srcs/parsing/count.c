/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:50:24 by bhocsak           #+#    #+#             */
/*   Updated: 2025/02/02 14:50:25 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_cmnds(char *line, int limit)
{
	int	count;
	int	i;
	int	open;

	count = 1;
	i = -1;
	open = 0;
	if (!line || !*line)
		return (0);
	while (line && ++i < limit && line[i] && line[i] != '\n')
	{
		if (is_quote_one(line[i]) && !open)
			open = 1;
		else if (is_q_2(line[i]) && !open)
			open = 2;
		else if (((is_quote_one(line[i]) && open == 1)
				|| (is_q_2(line[i]) && open == 2)))
			open = 0;
		if (line[i] == '|' && is_real_pipe(line, i) && !open)
			count++;
		if (!line[i])
			break ;
	}
	return (count);
}

int	count_elem(t_pipex *d, int i_1, int i, int j)
{
	int	k;

	k = -i;
	d->open = 0;
	d->count_elem = 0;
	while (d->line[++j] && j < d->l[i_1]->limit &&  d->line[j] != '\n' && i >= 0)
	{
		if (k != 0)
			handle_open(d, j, &d->open);
		if (k == 0)
		{
			if (d->line[j] == '|' && is_real_pipe(d->line, j) && !d->open)
				break ;
			if (elem_spaces(d, j) || (!d->open && check_for_empty(d, j) 
				&& is_quote(d->line[j + 1]) && is_quote(d->line[j])))
				d->count_elem++;
			if (if_count_elem_1(d, j))
				d->count_elem++;
		}
		else if (!d->open && is_real_pipe(d->line, j)
			&& d->line[j] == '|' && --i != INT_MIN)
			k++;
	}
	return (d->count_elem);
}

int	count_chars(t_pipex *data, int i, int open, int count)
{
	while (data->line[i])
	{
		if (i > 0 && !open && is_quote(data->line[i])
			&& is_d_b(data->line, i - 1, open))
			break ;
		else if (handle_open(data, i, &open))
		{
			if (count > 0 && is_quote_one(data->line[i])
				&& open == 1 && ((data->line[i + 1]
						&& is_delim_front(data->line, i + 1))
					|| !data->line[i + 1]))
				break ;
			else if (count_chars_utils_1(data, i, open, count))
				break ;
			else if (count_chars_utils_2(data, i, open, count))
				break ;
			if (data->line[i] && ((!is_quote(data->line[i]))
					|| ((open == 1 && is_q_2(data->line[i]))
						|| (open == 2 && is_quote_one(data->line[i])))))
				count++;
		}
		i++;
	}
	return (count);
}

int	count_chars_2(t_pipex *data, int i)
{
	int	count;

	count = 0;
	while (data->line[i])
	{
		if (!data->line[i] || is_space(data->line[i]) || data->line[i] == '\n'
			|| is_real_pipe(data->line, i)
			|| is_red_clean(data->line, i)
			|| data->line[i] == '/'
			|| (data->line[i] == '$' && count > 1)
			|| is_quote(data->line[i])
			|| (data->line[i] != '$' && !is_char(data->line[i])))
			break ;
		count++;
		i++;
	}
	return (count);
}
