/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmnds_utils_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:55:16 by bhocsak           #+#    #+#             */
/*   Updated: 2025/02/02 14:55:18 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	if_1(t_pipex *data, int *j)
{
	if (*j > 0 && !data->line[*j])
		return (0);
	if (data->line[++*j] && ((*j > 0 && !data->open
				&& is_real_pipe(data->line, *j)
				&& ++data->k <= 0) || (data->line[*j] != '\n' && data->k <= 0)))
		return (1);
	return (0);
}

int	if_2(t_pipex *data, int j)
{
	if (!data->line[j])
		return (0);
	if (!data->open && data->k == 0 && check_for_empty(data, j)
		&& is_quote(data->line[j])
		&& is_quote(data->line[j + 1]) && ++data->i_2 != INT_MIN)
		return (1);
	return (0);
}

int	if_3(t_pipex *data, int j, int i_1, int i)
{
	if (!data->line[j])
		return (0);
	if (data->k == 0 && d_in(data, j, data->open) != -1
		&& !count_ex(data, j, data->open, 0)
		&& is_red_basic(data, i_1, i, data->i_2))
		return (1);
	return (0);
}

int	if_4(t_pipex *data, int j)
{
	if (data->k == 0 && handle_open(data, j, &data->open) && data->line[j]
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

int	if_5(t_pipex *data, int i, int i_1)
{
	if (!data->line[i])
		return (0);
	if (data->i_2 == -1
		|| (data->i_2 >= 0
			&& ft_strncmp(data->l[i_1]->cmnds[i][data->i_2], "<<", 3)))
		return (1);
	return (0);
}
