/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 09:44:11 by bhocsak           #+#    #+#             */
/*   Updated: 2024/04/09 11:20:54 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (i + j < len && big[i] != '\0')
	{
		if (big[i + j] == little[j])
		{
			j++;
			if (little[j] == '\0')
				return ((char *) big + i);
		}
		else
		{
			j = 0;
			i++;
		}
	}
	return (0);
}
/*
#include <stdio.h>

int main() {
    const char *big = "Hello, world ke";
    const char *little = "world";

    // Call the function with the provided strings
    char *result = ft_strnstr(big, little, 13);

    // Check if the result is not NULL
    if (result != NULL)
	{
        // Print the substring found
        printf("Substring found: %s\n", result);
    }
	else
	{
        printf("Substring not found.\n");
    }
    return 0;
}*/
