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

int check_reds(t_pipex *data)
{
    int i;
    int j;

    i = -1;
    while (data->cmnds[++i])
    {
        j = -1;
        while (data->cmnds[i][++j])
        {
            if (is_red(data, i, j) && !data->cmnds[i][j + 1])
            {
                if (!data->cmnds[i + 1])
                    return (printf("bash: syntax error near unexpected token `newline' \n"), exit_child(2, NULL, data), 0);
                return (printf("bash: syntax error near unexpected token `|'\n"), exit_child(2, NULL, data), 0);
            }
            else if (is_red(data, i, j) && is_red(data, i, j + 1))
                    return (printf("BASH: syntax error near unexpected token `%s' \n", data->cmnds[i][j + 1]), exit_child(2, NULL, data), 0);
			else if (data->cmnds[i][j + 1] && printf("break\n"))
				break;
        }
    }
	// printf("check_reds: return 1\n");
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
		if (i == 0 && line[i] == '|' && (!line[i + 1] || line[i + 1] != '|'))
			return (0);
		else if (!is_real_pipe(line, i) && ++word)
			count = 0;
		else
			count++;
		if (count >= 2)
			return (0);
	}
	return (1);
}

