/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:02:57 by bhocsak           #+#    #+#             */
/*   Updated: 2024/04/04 15:02:23 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		c += 32;
	return (c);
}
/*
#include <stdio.h>

int main()
{
    char test_char1 = 'A';
    char test_char2 = 'z';

    printf("Testing character '%c': '%c'\n", test_char1, ft_tolower(test_char1));
    printf("Testing character '%c': '%c'\n", test_char2, ft_tolower(test_char2));

    return (0);
}*/
