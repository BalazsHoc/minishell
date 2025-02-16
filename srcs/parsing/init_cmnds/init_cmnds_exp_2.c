/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmnds_exp_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:54:28 by bhocsak           #+#    #+#             */
/*   Updated: 2025/02/02 14:54:30 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	ex_1_4(t_pipex *data, int i)
{
	if (!data->line[i] || is_space(data->line[i]) || data->line[i] == '\n'
		|| is_real_pipe(data->line, i)
		|| is_red_clean(data->line, i)
		|| (data->line[i + 1] && is_space(data->line[i])
			&& is_quote(data->line[i + 1])))
		return (1);
	return (0);
}

int	ex_1_5(t_pipex *data, int i, int open)
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

int	ex_1_6(t_pipex *data, int i, int open)
{
	if (open || (data->line[i] != '$'
			|| (data->line[i] == '$'
				&& is_delim_front(data->line, i + 1))))
		return (1);
	return (0);
}
