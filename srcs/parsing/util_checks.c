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
	else if (!line[index] || !line[index + 1])
		return (0);
	// printf("PIPE?: %s\n", line + index);
	if (line[index] == '|')
	{
		if (line[index - 1] == '|'
		|| line[index - 1] == '>'
		|| line[index + 1] == '|')
			return (0);
		// return (printf("YESSS REAL PIPE\n"), 1);
		return (1);
	}
	return (0);
	// return (printf("NOO REAL PIPE\n"), 0);
}

// int special_case(t_pipex *data, int index_1, int i, int j)
// {
// 	if (!ft_strncmp(data->lines[index_1]->cmnds[i][j], "<", 2)
// 		&& !ft_strncmp(data->lines[index_1]->cmnds[i][j + 1], ">>", 3))
// 		return (1);
// 	return (0);
// }

int check_reds(t_pipex *data, int index_1)
{
    int i;
    int j;

    i = -1;
    while (data->lines[index_1]->cmnds[++i])
    {
        j = -1;
        while (data->lines[index_1]->cmnds[i][++j])
        {
			// printf("PENIS 2 %d |  %s\n", data->lines[index_1]->red_cmnd[i][j], data->lines[index_1]->cmnds[i][j]);
			if (is_red(data, index_1, i, j) && !data->lines[index_1]->cmnds[i][j + 1] && !data->lines[index_1]->red_cmnd[i][j]) // if nothing comes after the red;
			{
				if (!data->lines[index_1]->cmnds[i + 1]) // and nothing comes after the pipe [ so no pipe ]
					return (write(2, "-bash: syntax error near unexpected token `newline'\n", 53), exit_child(data, index_1, i, 2), 0);
				return (write(2, "-bash: syntax error near unexpected token `|'\n", 47), exit_child(data, index_1, i, 2), 0);
			}
			else if (is_red(data, index_1, i, j) && is_red(data, index_1, i, j + 1))
				return (printf("-bash: syntax error near unexpected token `%s'\n", data->lines[index_1]->cmnds[i][j + 1]), exit_child(data, index_1, i, 2), 0);
        }
    }
	// printf("FINISH CHECK REDS\n");
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

int syntax_check(char *line, int i, int count)
{
	int word;

	word = 0;
	while (line[++i])
	{
		if (i == 0 && line[0] == '|' && (!line[i + 1] || line[i + 1] != '|'))
			return (0);
		else if (!is_real_pipe(line, i) && line[i] != '|' && ++word)
			count = 0;
		else
			count++;
		if (count >= 2)
			return (0);
	}
	return (1);
}

