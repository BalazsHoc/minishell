/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmnds_utils_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:55:32 by bhocsak           #+#    #+#             */
/*   Updated: 2025/02/02 14:55:34 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	check_for_empty(t_pipex *data, int i)
{
	if (!data->line[i] || !(is_space(data->line[i]) || (is_quote(data->line[i])
				&& (i == 0 || (i > 0 && (is_space(data->line[i - 1])
							|| is_real_pipe(data->line, i - 1)))))))
		return (0);
	while (data->line[i] && is_space(data->line[i]))
		i++;
	if (data->line[i] && is_quote_one(data->line[i])
		&& data->line[i + 1] && is_quote_one(data->line[i + 1])
		&& ((data->line[i + 2] && (is_delim_front(data->line, i + 2)
					|| is_space(data->line[i + 2])
					|| is_real_pipe(data->line, i + 2)
					|| data->line[i + 2] == '\n'))
			|| (!data->line[i + 2])))
		return (i += 2, check_for_empty(data, i) + 1);
	else if (data->line[i] && is_q_2(data->line[i])
		&& data->line[i + 1] && is_q_2(data->line[i + 1])
		&& ((data->line[i + 2] && (is_delim_front(data->line, i + 2)
					|| is_space(data->line[i + 2])
					|| is_real_pipe(data->line, i + 2)
					|| data->line[i + 2] == '\n'))
			|| (!data->line[i + 2])))
		return (i += 2, check_for_empty(data, i) + 1);
	else
		return (0);
}

int	is_d_b(char *line, int i, int open)
{
	if (i < 0 || !line[i])
		return (1);
	while (i >= 0 && is_quote(line[i]))
	{
		if ((open == 1 && is_q_2(line[i]))
			|| (open == 2 && is_quote_one(line[i])))
			return (0);
		if (is_quote_one(line[i]) && !open)
			open = 1;
		else if (is_q_2(line[i]) && !open)
			open = 2;
		else if (((is_quote_one(line[i]) && open == 1)
				|| (is_q_2(line[i]) && open == 2)))
			open = 0;
		i--;
	}
	if (!open && (i < 0 || is_space(line[i]) || is_red_1(line[i])
			|| is_real_pipe(line, i)))
		return (1);
	return (0);
}

int	is_delim_front(char *line, int i)
{
	int	open;

	open = 0;
	while (line[i] && is_quote(line[i]))
	{
		if ((open == 1 && is_q_2(line[i])) || (open == 2
				&& is_quote_one(line[i])))
			return (0);
		if (is_quote_one(line[i]) && !open)
			open = 1;
		else if (is_q_2(line[i]) && !open)
			open = 2;
		else if (((is_quote_one(line[i]) && open == 1)
				|| (is_q_2(line[i]) && open == 2)))
			open = 0;
		i++;
	}
	if (!open && (!line[i] || line[i] == '\n' || is_space(line[i])
			|| is_red_clean(line, i) || is_real_pipe(line, i)))
		return (1);
	return (0);
}

int	d_in_if_1(t_pipex *data, int j, int *open)
{
	if (handle_open(data, j, open) && (!*open && (
				(is_d_b(data->line, j, *open))
				|| (is_delim_front(data->line, j + 1))
				|| (is_real_pipe(data->line, j + 1))
				|| ((is_red_1(data->line[j]))
					&& !is_red_1(data->line[j + 1]))
				|| ((is_red_1(data->line[j + 1]))
					&& !is_space(data->line[j]) && !is_red_1(data->line[j]))
				|| ((is_space(data->line[j]) && is_quote(data->line[j + 1])))
				|| ((is_space(data->line[j]) && data->line[j + 1]
						&& data->line[j + 2]
						&& (is_space(data->line[j + 2])
							|| data->line[j + 2] == '\n')
						&& is_quote(data->line[j + 1]))))))
		return (1);
	return (0);
}

int	d_in(t_pipex *data, int j, int open)
{
	int	check;

	check = 0;
	while (data->line[j])
	{
		if (open == 1 && is_quote_one(data->line[j])
			&& is_delim_front(data->line, j + 1))
			break ;
		if (open == 2 && is_q_2(data->line[j])
			&& is_delim_front(data->line, j + 1))
			break ;
		if (j > 0 && is_d_b(data->line, j - 1, open))
			check = 1;
		if (d_in_if_1(data, j, &open))
			break ;
		if (open != 1 && data->line[j] == '$' && data->line[j + 1]
					&& (is_d_b(data->line, j - 1, open) || (check // this one not sure
					&& !is_d_b(data->line, j - 1, open)))			// this one also not sure
			&& (is_char(data->line[j + 1]) || data->line[j + 1] == '?'
				|| data->line[j + 1] == '$') && (!is_space(data->line[j + 1])
				&& !(open == 2 && is_q_2(data->line[j + 1]))))
			return (j);
		j++;
	}
	return (-1);
}
