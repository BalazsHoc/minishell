/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:12:17 by bhocsak           #+#    #+#             */
/*   Updated: 2024/10/11 16:12:19 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_real_pipe(char *line, int index)
{
	if (index == 0)
		return (0);
	else if (!line[index])
		return (0);
	if (line[index] == '|')
	{
		if ((index > 0 && line[index - 1] == '|')
			|| (index > 1 && line[index - 1] == '>'
				&& line[index - 2] != '>')
			|| (line[index + 1] && line[index + 1] == '|'))
			return (0);
		return (1);
	}
	return (0);
}

int s(t_pipex *data, int i_1, int i, int j)
{
	return (data->l[i_1]->pos[i][j]);
}

void	c(t_pipex *data)
{
	write(2, "bash: syntax error near unexpected token `newline'\n", 52);
	data->last_exit_status = 2;
}

void	c_2(t_pipex *data)
{
	write(2, "bash: syntax error near unexpected token `|'\n", 46);
	data->last_exit_status = 2;
}

void	check_reds_util_3(t_pipex *data, int index_1, int i, int j)
{
	write(2, "bash: syntax error near unexpected token `", 43);
	write(2, data->l[index_1]->cmnds[i][j + 1],
		ft_strlen(data->l[index_1]->cmnds[i][j + 1]));
	write(2, "'\n", 2);
	data->last_exit_status = 2;
}

int	check_reds(t_pipex *d, int i_1, int i, int syn_c)
{
	while (d->l[i_1]->cmnds[++i])
	{
		d->buf_int = -1;
		// printf("THAT1: %d\n", d->l[i_1]->pos[i][d->buf_int + 1]);
		while (d->l[i_1]->cmnds[i][++d->buf_int]
			&& d->l[i_1]->pos[i][d->buf_int] < syn_c)
		{
			if (is_red_basic(d, i_1, i, d->buf_int) && d->l[
					i_1]->red_cmnd[i][d->buf_int] == 2)
				return (write(2, "bash: ambigiuous redirect\n", 27),
					d->last_exit_status = 1, s(d, i_1, i, d->buf_int));
			else if (is_red(d, i_1, i, d->buf_int) && !d->l[
					i_1]->cmnds[i][d->buf_int + 1] && !d->l[
							i_1]->red_cmnd[i][d->buf_int])
			{
				if (!d->l[i_1]->cmnds[i + 1])
					return (c(d), d->l[i_1]->ex = i, s(d, i_1, i, d->buf_int));
				return (c_2(d), d->l[i_1]->ex = i, s(d, i_1, i, d->buf_int));
			}
			else if (is_red(d, i_1, i, d->buf_int)
				&& is_red(d, i_1, i, d->buf_int + 1))
				return (check_reds_util_3(d, i_1, i, d->buf_int),
					d->l[i_1]->ex = i, s(d, i_1, i, d->buf_int));
		}
	}
	return (-1);
}
