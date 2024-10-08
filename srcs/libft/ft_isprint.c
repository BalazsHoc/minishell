/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 09:46:59 by bhocsak           #+#    #+#             */
/*   Updated: 2024/04/04 14:42:44 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}
/*
#include <stdio.h>
int main()
{
    int test_char1 = 'A';
    int test_char2 = '\t'; // Tab character

    printf("Testing character '%c': ", test_char1);
    if (ft_isprint(test_char1))
        printf("'%c' is a printable character.\n", test_char1);
    else
        printf("'%c' is not a printable character.\n", test_char1);

    printf("Testing character '\\t': ");
    if (ft_isprint(test_char2))
        printf("'%c' is a printable character.\n", test_char2);
    else
        printf("'%c' is not a printable character.\n", test_char2);

    return (0);
}*/
