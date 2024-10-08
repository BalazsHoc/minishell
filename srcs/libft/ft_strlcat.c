/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 11:03:26 by bhocsak           #+#    #+#             */
/*   Updated: 2024/04/12 11:06:59 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	s_i;
	size_t	i;
	size_t	result;

	s_i = 0;
	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	else if (size < ft_strlen(dest))
		result = ft_strlen(src) + size;
	else
		result = ft_strlen(src) + ft_strlen(dest);
	while (dest[i])
		i++;
	while (src[s_i] != '\0' && i + 1 < size)
	{
		dest[i] = src[s_i];
		i++;
		s_i++;
	}
	dest[i] = '\0';
	return (result);
}
/*
#include <stdio.h>

int main()
{
    char dest[20] = "Hello";
    const char *src = " World!";
    size_t result;
    
    // Call ft_strlcat to concatenate src to dest
    result = ft_strlcat(dest, src, 3);
    
    // Printing the concatenated string and the total length
    printf("Concatenated string: %s\n", dest);
    printf("Total length: %zu\n", result);

    return (0);
}*/
