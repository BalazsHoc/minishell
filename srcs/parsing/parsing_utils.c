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

int	count_cmnds(char *line)
{
	int	count;
	int	i;

	count = 1;
	i = -1;
	while (line[++i])
	{
		if (real_pipe(line, i))
			count++;
	}
	return (count);
}

int	is_space(char c)
{
	if (c == ' ')
		return (1);
	return (0);
}

int	count_elem(char *line, int i, int count)
{
	int	j;
	int	k;

	j = -1;
	k = -i;
	while (line[++j] && i >= 0)
	{
		printf("J: %d | K: %d | I: %d\n", j, k, i);
		if (k == 0)
		{
			if (real_pipe(line, j))
				break ;
			if ((j == 0 && !is_space(line[j]))
				|| (is_space(line[j - 1]) && !is_space(line[j]))
				|| (is_red_clean(line, j))
				|| (is_red_clean(line, (j - 1)) && !is_space(line[j])))
				{
					if (is_red_clean(line, j) == 2)
						j++;
					count++;
				}
		}
		else if (real_pipe(line, j) && --i)
			k++;
	}
	printf("COUNT ELEM RETURN: %d\n", count);
	return (count);
}

int	count_chars(char *line)
{
	int	count;

	count = 0;
	printf("%s\n", line);
	while (line[count])
	{
		if (is_space(line[count]) || line[count] == '\n'
			|| line[count] == '|'
			|| (count > 0 && is_red_clean(line, count) == 1)
			|| (count > 0 && is_red_clean(line, count - 1) == 1 && !is_space(line[count])))
			break ;
		count++;
	}
	printf("COUNT CHARS RETURN: %d\n", count);
	return (count);
}

int syntax_check(char *line, int i, int count)
{
	int word;

	word = 0;
	while (line[++i])
	{
		// if (line[i] == '|' && i > 0 && line[i - 1] != '>' && ++count)
		// {
		// 	if (space)
		// 		return (0);
		// 	space = 0;
		// }
		// else if (count && line[i] == ' ')
		// 	space++;
		// else if (line[i] != '|')
		// {
		// 	count = 0;
		// 	space = 0;
		// }
		// if (count == 3)
		// 	return (0);
		if (i == 0 && line[i] == '|' && (!line[i + 1] || line[i + 1] != '|'))
			return (0);
		else if (!real_pipe(line, i) && ++word)
			count = 0;
		else
			count++;
		if (count >= 2)
			return (0);
	}
	return (1);
}

