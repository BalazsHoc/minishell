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

#include "../minishell.h"

int	count_cmnds(char *line)
{
	int	count;
	int	i;

	count = 1;
	i = 0;
	while (line[i])
	{
		if (line[i] == '|' && line[i + 1] == '|')
			i++;
		if (line[i] == '|' )
			count++;
		i++;
	}
	return (count);
}

int	is_space(char c)
{
	if (c == ' ')
		return (1);
	return (0);
}

int	count_elem(char *line, int i)
{
	int	count;
	int	j;
	int	k;

	count = 0;
	j = 0;
	k = -i;
	while (line[j] && i >= 0)
	{
		if (k == 0 && j > 0 && !is_space(line[j])
			&& is_space(line[j - 1]) && line[j] != '|')
			count++;
		else if (k == 0 && j == 0 && !is_space(line[j]))
			count++;
		if (line[j] == '|')
		{
			i--;
			k++;
		}
		j++;
	}
	return (count);
}

int	count_chars(char *line)
{
	int	count;

	count = 0;
	while (line[count])
	{
		if (is_space(line[count]) || line[count] == '\n')
			break ;
		count++;
	}
	return (count);
}
