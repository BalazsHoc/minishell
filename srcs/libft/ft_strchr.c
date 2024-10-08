/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:16:29 by bhocsak           #+#    #+#             */
/*   Updated: 2024/04/04 14:40:46 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while ((char)c != *s)
	{
		if (!*s)
			return (0);
		s++;
	}
	return ((char *)s);
}
/*
#include <stdio.h>

int main()
{
	const char *str = "Hello, world!";
	int search_char = 'd';
	char *result = ft_strchr(str, search_char);

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
