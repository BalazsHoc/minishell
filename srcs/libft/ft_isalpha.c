/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:28:06 by bhocsak           #+#    #+#             */
/*   Updated: 2024/04/11 17:30:03 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}
/*
#include <stdio.h>
int main()
{
    char test_char1 = 'A';
    char test_char2 = '9';

    printf("Testing character '%c': ", test_char1);
    if (ft_isalpha(test_char1))
        printf("'%c' is an alphabetic character.\n", test_char1);
    else
        printf("'%c' is not an alphabetic character.\n", test_char1);

    printf("Testing character '%c': ", test_char2);
    if (ft_isalpha(test_char2))
        printf("'%c' is an alphabetic character.\n", test_char2);
    else
        printf("'%c' is not an alphabetic character.\n", test_char2);

    return 0;
}*/
