/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:50:41 by bhocsak           #+#    #+#             */
/*   Updated: 2025/02/02 14:50:42 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	if_count_elem_1(t_pipex *data, int j)
{
	if (handle_open(data, j, &data->open) && data->line[j]
	&& ((j == 0 && !is_quote(data->line[j])) || (j > 0 && (
				(is_red_clean(data->line, j) && !data->open)
				|| (!data->open && j > 1 && is_d_b(data->line, j - 1, 0)
					&& !is_d_b(data->line, j, 0))
				|| (((j > 1 && is_d_b(data->line, j - 2, 0)) || j < 2)
					&& ((data->open == 1 && is_quote_one(data->line[j - 1])
							&& !is_quote_one(data->line[j]))
						|| (data->open == 2 && is_q_2(data->line[j - 1])
							&& !is_q_2(data->line[j]))))
				|| (!data->open && !is_real_pipe(data->line, j)
					&& !is_real_pipe(data->line, j)
					// && data->line[j] != '|'
					&& !is_quote(data->line[j]) && !is_space(data->line[j])
					&& is_d_b(data->line, j - 1, 0)
					&& !is_red_1(data->line[j]))
				|| (is_red_1(data->line[j - 1]) && !is_red_1(data->line[j])
					&& !is_space(data->line[j]) && data->line[j] != '|'
					&& !data->open)
				|| (!data->open && is_real_pipe(data->line, j - 1)
					&& !is_space(data->line[j])))))
	&& ((d_in(data, j, data->open) >= 0
			&& count_ex(data, j, data->open, 0))
		|| d_in(data, j, data->open) == -1))
		return (1);
	return (0);
}

int	count_chars_utils_2(t_pipex *data, int i, int open, int count)
{
	if (!open && count > 0
		&& (is_delim_front(data->line, i)
			|| (count > 0 && is_red_clean(data->line, i))
			|| (count > 0 && i > 0 && is_red_1(data->line[i - 1])
				&& !is_red_1(data->line[i]))
			|| (count > 0 && i > 0 && is_red_clean(data->line, i - count)
				&& ((is_red_in(data->line, i - count)
						&& is_red_out(data->line, i))
					|| (is_red_out(data->line, i - count)
						&& is_red_in(data->line, i)) || count == 2))))
		return (1);
	return (0);
}

int	count_chars_utils_1(t_pipex *data, int i, int open, int count)
{
	if (count > 0 && is_q_2(data->line[i]) && open == 2 && ((data->line[i + 1]
				&& is_delim_front(data->line, i + 1)) || !data->line[i + 1]))
		return (1);
	return (0);
}
