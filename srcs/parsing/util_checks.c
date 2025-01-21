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
		|| (index > 1 && line[index - 1] == '>' && line[index - 2] != '>')
		|| (line[index + 1] && line[index + 1] == '|'))
			return (0);
		return (1);
	}
	return (0);
}

int check_reds(t_pipex *data, int index_1, int i, int j)
{
    while (data->lines[index_1]->cmnds[++i])
    {
        j = -1;
        while (data->lines[index_1]->cmnds[i][++j])
        {
			if (is_red_basic(data, index_1, i, j) && data->lines[index_1]->red_cmnd[i][j] == 2)
				return (write(2, "bash: ambigiuous redirect\n", 27), data->last_exit_status = 1, 0);
			else if (is_red(data, index_1, i, j) && !data->lines[index_1]->cmnds[i][j + 1] && !data->lines[index_1]->red_cmnd[i][j])
			{
				if (!data->lines[index_1]->cmnds[i + 1])
					return (write(2, "bash: syntax error near unexpected token `newline'\n", 52), data->last_exit_status = 2, 0);
				return (write(2, "bash: syntax error near unexpected token `|'\n", 46), data->last_exit_status = 2, 0);
			}
			else if (is_red(data, index_1, i, j) && is_red(data, index_1, i, j + 1))
				return (write(2, "bash: syntax error near unexpected token `", 43), 
					write(2, data->lines[index_1]->cmnds[i][j + 1], ft_strlen(data->lines[index_1]->cmnds[i][j + 1])), write(2, "'\n", 2), data->last_exit_status = 2, 0);
        }
    }
    return (1);
}

int check_open(char *line)
{
	int open;
	int i;

	i = -1;
	open = 0;
	while (line[++i])
	{
		if (is_quote_one(line[i]) && !open)
			open = 1;
		else if (is_quote_two(line[i]) && !open)
			open = 2;
		else if (((is_quote_one(line[i]) && open == 1) || (is_quote_two(line[i]) && open == 2)))
			open = 0;
	}
	return (open);
}

int syntax_check(t_pipex *data, int i, int count)
{
	int word;
	int open;

	word = 0;
	open = 0;
	while (data->line[++i])
	{
		handle_open(data, i, &open);
		if (!open && (i == 0 && data->line[0] == '|' && (!data->line[i + 1] || data->line[i + 1] != '|')))
			return (0);
		else if (!open && (!is_real_pipe(data->line, i) && data->line[i] != '|' && ++word))
			count = 0;
		else if (!open)
			count++;
		if (count >= 2)
			return (0);
	}
	return (1);
}

