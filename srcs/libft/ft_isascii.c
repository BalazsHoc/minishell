/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 09:39:35 by bhocsak           #+#    #+#             */
/*   Updated: 2024/04/04 14:41:55 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}
/*
#include <stdio.h>
int main()
{
    int test_char1 = 'A';
    int test_char2 = 128;

    printf("Testing character with ASCII value %d: ", test_char1);
    if (ft_isascii(test_char1))
        printf("Character is a valid ASCII character.\n");
    else
        printf("Character is not a valid ASCII character.\n");
    printf("Testing character with ASCII value %d: ", test_char2);
    if (ft_isascii(test_char2))
        printf("Character is a valid ASCII character.\n");
    else
        printf("Character is not a valid ASCII character.\n");
    return (0);
}*/
