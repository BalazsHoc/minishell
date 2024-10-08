/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 08:40:00 by bhocsak           #+#    #+#             */
/*   Updated: 2024/07/28 13:25:19 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	gnl_free(char **ptr)
{
	if (ptr != NULL && *ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

int	gnl_strlen(char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (len);
	while (str[len])
		len++;
	return (len);
}

int	gnl_newline(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*gnl_strcpy(char *str)
{
	char	*copied;
	int		len;
	int		i;

	len = 0;
	i = 0;
	if (!str)
		return (NULL);
	while (str[len] && str[len] != '\n')
		len++;
	if (str[len] && str[len] == '\n')
		len++;
	if (len == 0)
		return (NULL);
	copied = (char *)gnl_calloc((len + 1), sizeof(char));
	if (!copied)
		return (NULL);
	while (i < len && str[i] != '\0')
	{
		copied[i] = str[i];
		i++;
	}
	copied[len] = '\0';
	return (copied);
}

char	*gnl_fromnl(char *str)
{
	int		i;
	int		start;
	int		end;
	char	*rest;

	i = 0;
	start = 0;
	while (str[start] && str[start] != '\n')
		start++;
	if (str[start] && str[start] == '\n')
		start++;
	end = gnl_strlen(str);
	if (start == end || end == 0)
		return (gnl_free(&str), NULL);
	rest = (char *)gnl_calloc((end - start + 1), sizeof(char));
	if (!rest)
		return (gnl_free(&str), NULL);
	while (start <= end)
		rest[i++] = str[start++];
	rest[i] = '\0';
	return (gnl_free(&str), rest);
}
