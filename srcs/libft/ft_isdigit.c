/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:08:10 by bhocsak           #+#    #+#             */
/*   Updated: 2024/04/11 15:05:39 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
/*
#include <stdio.h>
int main()
{
    int test_char1 = '5';
    int test_char2 = 'A';

    printf("Testing character '%c': ", test_char1);
    if (ft_isdigit(test_char1))
        printf("'%c' is a digit.\n", test_char1);
    else
        printf("'%c' is not a digit.\n", test_char1);

    printf("Testing character '%c': ", test_char2);
    if (ft_isdigit(test_char2))
        printf("'%c' is a digit.\n", test_char2);
    else
        printf("'%c' is not a digit.\n", test_char2);

    return (0);
}*/
