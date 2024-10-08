/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:22:16 by bhocsak           #+#    #+#             */
/*   Updated: 2024/04/04 15:41:43 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i--;
	}
	return (0);
}
/*
#include <stdio.h>

int main()
{
	const char *str = "Heldo, world!";
	int search_char = 'd';
	char *result = ft_strrchr(str, search_char);

	if (result != NULL)
	{
		printf("Character '%c' found at index %ld\n", search_char, result - str);
	}
	else
	{
		printf("Character '%c' not found\n", search_char);
	}

    return (0);
}*/
