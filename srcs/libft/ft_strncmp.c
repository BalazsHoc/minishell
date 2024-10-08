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
	while (i < n)
	{
		if (s1[i] && s1[i] == s2[i])
		{
			while (s1[i] && s1[i] == s2[i] && i < n)
				i++;
		}
		else
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	return (0);
}
/*
#include <stdio.h>

int main()
{
    const char *s1 = "Hlo";
    const char *s2 = "Hbell";
    size_t n = 1;  // Number of characters to compare
    
    int result = ft_strncmp(s1, s2, n);
    
    // Printing the result of string comparison
    if (result == 0)
        printf("Strings are equal.\n");
    else if (result < 0)
        printf("First string is less than second string.\n");
    else
        printf("First string is greater than second string.\n");

    return (0);
}*/
