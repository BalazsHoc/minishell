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

void	check_reds_util_1(t_pipex *data)
{
	write(2, "bash: syntax error near unexpected token `newline'\n", 52);
	data->last_exit_status = 2;
}

void	check_reds_util_2(t_pipex *data)
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

int	check_reds(t_pipex *data, int index_1, int i, int j)
{
	while (data->l[index_1]->cmnds[++i])
	{
		j = -1;
		while (data->l[index_1]->cmnds[i][++j])
		{
			if (is_red_basic(data, index_1, i, j) && data->l[
					index_1]->red_cmnd[i][j] == 2)
				return (write(2, "bash: ambigiuous redirect\n", 27),
					data->last_exit_status = 1, 0);
			else if (is_red(data, index_1, i, j) && !data->l[
					index_1]->cmnds[i][j + 1] && !data->l[
							index_1]->red_cmnd[i][j])
			{
				if (!data->l[index_1]->cmnds[i + 1])
					return (check_reds_util_1(data),
						data->l[index_1]->ex = i, 0);
				return (check_reds_util_2(data), data->l[index_1]->ex = i, 0);
			}
			else if (is_red(data, index_1, i, j)
				&& is_red(data, index_1, i, j + 1))
				return (check_reds_util_3(data, index_1, i, j),
					data->l[index_1]->ex = i, 0);
		}
	}
	return (1);
}
