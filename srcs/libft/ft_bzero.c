/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:27:41 by bhocsak           #+#    #+#             */
/*   Updated: 2024/04/24 11:04:59 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
/*
int main()
{
    char buffer[10];

    // Zero out the buffer
    ft_bzero(buffer, sizeof(buffer));

    // Printing the buffer to verify it's zeroed out
    printf("Buffer after zeroing out:\n");
    for (size_t i = 0; i < sizeof(buffer); ++i)
	{
        printf("%d ", buffer[i]);
    }
    printf("\n");

    return 0;
}*/
