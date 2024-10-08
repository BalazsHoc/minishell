/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:55:23 by bhocsak           #+#    #+#             */
/*   Updated: 2024/04/11 14:21:51 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dest == src || !n)
		return (dest);
	if (dest < src)
	{
		while (i < n)
		{
			*((char *)dest + i) = *((char *)src + i);
			i++;
		}
	}
	else
	{
		while (n > 0)
		{
			*((char *)dest + n - 1) = *((char *)src + n - 1);
			n--;
		}
	}
	return (dest);
}
/*
#include <stdio.h>

int main()
{
    char str1[20] = "Hello, World!";
    char str2[20] = "Hello, World!";

    // Using ft_memmove
    printf("Before ft_memmove: %s\n", str1);
    ft_memmove(str1 + 7, str1 + 1, 5); 
	// Move "World" to the position after "Hello"
    printf("After ft_memmove: %s\n", str1);

    // Using standard memmove for comparison
    printf("\nBefore memmove: %s\n", str2);
    memmove(str2 + 7, str2 + 1, 5); // Move "World" to the position after "Hello"
    printf("After memmove: %s\n", str2);

    return (0);
}*/
