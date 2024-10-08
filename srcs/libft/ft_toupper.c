/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 11:58:37 by bhocsak           #+#    #+#             */
/*   Updated: 2024/04/04 15:03:59 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		c -= 32;
	return (c);
}
/*
#include <stdio.h>

int main()
{
    char test_char1 = 'A';
    char test_char2 = 'z';

    printf("Testing character '%c': '%c'\n", test_char1, ft_toupper(test_char1));
    printf("Testing character '%c': '%c'\n", test_char2, ft_toupper(test_char2));

    return (0);
}*/
