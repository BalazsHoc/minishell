/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:10:36 by bhocsak           #+#    #+#             */
/*   Updated: 2024/04/12 10:54:56 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	length;

	length = 0;
	while (str[length] != '\0')
	{
		length++;
	}
	return (length);
}
/*
#include <stdio.h>

int main()
{
    const char *str = "Hello, faszom World!";

    // Call ft_strlen to get the length of the string
    int length = ft_strlen(str);

    // Printing the length of the string
    printf("Length of the string: %d\n", length);

    return (0);
}
*/
