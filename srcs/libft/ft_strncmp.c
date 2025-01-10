/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:02:25 by bhocsak           #+#    #+#             */
/*   Updated: 2024/04/12 09:19:08 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	if (!s1 || !s2 || !*s1 || !*s2)
		return (-1);
	// printf("S1: %s$ | S2: %s$\n", s1, s2);
	while (i < n)
	{
		if (!s1[i])
		{
			if (s2[i])
				return (-1);
		}
		else if (!s2[i])
			return (-1);
		// printf("I: %s$ | N: %ld$\n", s1 + i, n);
		else if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	// return (printf("THE SAME\n"), 0);
	return (0);
}

int ft_strcmp_2(char *s1, char *s2)
{
	int i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1 && s2 && (s1[i] == s2[i] || (s1[i] == '\n' && s2[i] == 0)))
	{
		if (s1[i] == '\n' && s2[i] == 0)
			return (1);
		i++;
	}
	return (0);
}
