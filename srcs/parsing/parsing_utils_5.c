/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:59:45 by bhocsak           #+#    #+#             */
/*   Updated: 2025/02/23 16:59:48 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	syn_red_check_ini(t_pipex *d, int i, int syn_check, int red_check)
{
	int	check;

	syn_check = syntax_check(d, d->here_2_old, 0);
	init_line(d, i, syn_check);
	if (syn_check != -1 && d->l[i]->cmnds[0][0] && d->l[i]->cmnds[0][0])
		red_check = check_reds(d, i, -1, syn_check);
	else if (syn_check != 0 && d->l[i]->cmnds[0][0] && d->l[i]->cmnds[0][0][0])
		red_check = check_reds(d, i, -1, INT_MAX - 1);
	check = -1;
	if (syn_check != -1 && ((red_check != -1 && syn_check < red_check)
			|| red_check == -1))
	{
		write(2, "bash: syntax error near unexpected token `|'\n", 46);
		d->last_exit_status = 2;
		check = syn_check;
	}
	else if (red_check != -1)
		check = red_check;
	if (check != -1)
	{
		signal_change(NULL, 1);
		do_nonesense_here_doc(d, check, NULL, NULL);
		d->here_2 = d->here_2_old;
	}
	return (check);
}

int	re_calc_limit(t_pipex *data, int limit)
{
	int	i;
	int	check;

	i = data->here_2_old;
	check = 0;
	if (limit == -1)
		return (INT_MAX);
	while (data->line[++i] && i < limit)
	{
		if (is_real_pipe(data->line, i))
			check = i;
	}
	if (check && check < limit)
		return (check);
	return (limit);
}

int	elem_spaces_util_1(t_pipex *data, int j, int open)
{
	if (handle_open(data, j, &open) && data->line[j]
		&& ((j == 0 && !is_quote(data->line[j])) || (j > 0 && (
					(is_red_clean(data->line, j) && !open)
					|| (!open && j > 1 && is_d_b(data->line, j - 1, 0)
						&& !is_d_b(data->line, j, 0))
					|| (((j > 1 && is_d_b(data->line, j - 2, 0)) || j < 2)
						&& ((open == 1 && is_quote_one(data->line[j - 1])
								&& !is_quote_one(data->line[j]))
							|| (open == 2 && is_q_2(data->line[j - 1])
								&& !is_q_2(data->line[j]))))
					|| (!open && !is_real_pipe(data->line, j)
						&& !is_real_pipe(data->line, j)
						&& !is_quote(data->line[j]) && !is_space(data->line[j])
						&& is_d_b(data->line, j - 1, 0)
						&& !is_red_1(data->line[j]))
					|| (is_red_1(data->line[j - 1]) && !is_red_1(data->line[j])
						&& !is_space(data->line[j]) && data->line[j] != '|'
						&& !open)
					|| (!open && is_real_pipe(data->line, j - 1)
						&& !is_space(data->line[j])))))
		&& ((d_in(data, j, open) >= 0
				&& count_ex(data, j, open, 0))
			|| d_in(data, j, open) == -1))
		return (1);
	return (0);
}

int	elem_spaces(t_pipex *data, int i)
{
	char	*elem;
	int		check;

	check = i;
	while (data->count_elem && check
		&& (is_space(data->line[check]) || is_quote(data->line[check])))
		check--;
	if (check > 1 && data->line[check] == '<' && data->line[check - 1] == '<')
		check = 0;
	else
		check = 1;
	elem = NULL;
	if (elem_spaces_util_1(data, i, data->open) && d_in(data, i, 0) >= 0
		&& (!data->count_elem || (data->count_elem && check)))
	{
		expand_it_1(data, i, data->open, &elem);
		check = count_elem_spaces(data, elem);
		return (free_str(&elem), check);
	}
	free_str(&elem);
	return (0);
}
