/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libft_01.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:49:14 by bhocsak           #+#    #+#             */
/*   Updated: 2025/02/02 14:49:16 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strdup(t_pipex *data, const char *s)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	i = 0;
	j = 0;
	while (s[j] != '\0')
		j++;
	ptr = ft_calloc(sizeof(char), (j + 1), data);
	while (i < j)
	{
		ptr[i] = s[i];
		i++;
	}
	return (ptr);
}

char	*ft_strdup_2(t_pipex *data, const char *s)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	i = 0;
	j = 0;
	while (s[j] != '\0' && s[j] != '/')
		j++;
	ptr = ft_calloc(sizeof(char), (j + 1), data);
	while (i < j)
	{
		ptr[i] = s[i];
		i++;
	}
	return (ptr);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (!str || !*str)
		return (0);
	while (str[i])
	{
		count++;
		if (!str[i + 1])
			break ;
		i++;
	}
	return (count);
}

char	*ft_strtrim(char *s1, char const *set, t_pipex *data)
{
	size_t	end;
	int		i;

	if (!s1 || !*s1 || !set || !*set)
		return (0);
	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	end = ft_strlen(s1);
	while (end != 0 && ft_strchr(set, s1[end]))
		end--;
	return (ft_substr(s1, i, end + 1, data));
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = 0;
		i++;
	}
}
