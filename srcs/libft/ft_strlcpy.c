/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:23:23 by bhocsak           #+#    #+#             */
/*   Updated: 2024/04/12 11:59:45 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (src[i] != '\0' && i < (size - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}
/*
#include <stdio.h>

int main()
{
    char destination[10]; // Destination buffer
    const char *source = "my"; // Source string

    // Call ft_strlcpy to copy src to dst
    size_t src_length = ft_strlcpy(destination, source, sizeof(destination));

    // Printing the copied string and its length
    printf("Copied string: %s\n", destination);
    printf("Length of source string: %zu\n", src_length);

    return (0);
}*/
