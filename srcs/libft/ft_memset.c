/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:46:36 by bhocsak           #+#    #+#             */
/*   Updated: 2024/04/18 12:15:05 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*str;

	i = 0;
	str = s;
	while (i < n)
	{
		str[i] = c;
		i++;
	}
	return (s);
}
/*
#include <stdio.h>
int main()
{
    char buffer[10];
    int value = 'X';

    // Fill the buffer with 'X' using ft_memset
    ft_memset(buffer, value, sizeof(buffer));

    // Printing the buffer to verify it's filled with 'X'
    printf("Buffer after memset:\n");
    for (size_t i = 0; i < sizeof(buffer); ++i) {
        printf("%c ", buffer[i]);
    }
    printf("\n");

    return 0;
}*/
