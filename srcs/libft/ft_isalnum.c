/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:35:44 by bhocsak           #+#    #+#             */
/*   Updated: 2024/04/12 09:12:35 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}
/*
#include <stdio.h>
int main()
{
    char str1[] = "Hello123";
    char str2[] = "Hello!";

    if (ft_isalnum(str1))
        printf("'%s' contains only alphanumeric characters.\n", str1);
    else
        printf("'%s' contains non-alphanumeric characters.\n", str1);

    if (ft_isalnum(str2))
        printf("'%s' contains only alphanumeric characters.\n", str2);
    else
        printf("'%s' contains non-alphanumeric characters.\n", str2);

    return 0;
}*/
