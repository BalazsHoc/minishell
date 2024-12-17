/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:15:37 by bhocsak           #+#    #+#             */
/*   Updated: 2024/10/08 13:15:39 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

char	*gnl_strcpy(char *buf, t_pipex *data)
{
	char	*copied;
	int		len;
	int		i;

	len = 0;
	i = 0;
	if (!buf)
		return (NULL); // ctrl C -> !buf
	while (buf[len] && buf[len] != '\n')
		len++;
	if (buf[len] && buf[len] == '\n')
		len++;
	if (len == 0) // ctrl D
		return (NULL);
	copied = (char *)gnl_calloc((len + 1), sizeof(char));
	if (!copied)
		return (gnl_free(&buf), error_code(data), NULL);
	while (i < len && buf[i] != '\0')
	{
		copied[i] = buf[i];
		i++;
	}
	copied[len] = '\0';
	return (copied);
}

char	*gnl_fromnl(char *buf)
{
	int		i;
	int		start;
	int		end;
	char	*rest;

	i = 0;
	start = 0;
	while (buf[start] && buf[start] != '\n')
		start++;
	if (buf[start] && buf[start] == '\n')
		start++;
	end = gnl_strlen(buf);
	if (start == end || end == 0)
		return (gnl_free(&buf), NULL);
	rest = (char *)gnl_calloc((end - start + 1), sizeof(char));
	if (!rest)
		return (gnl_free(&buf), NULL);
	while (start <= end)
		rest[i++] = buf[start++];
	rest[i] = '\0';
	return (gnl_free(&buf), rest);
}
