/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:54:26 by bhocsak           #+#    #+#             */
/*   Updated: 2024/04/18 17:25:40 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_digit_count(long int n)
{
	size_t	digits;

	if (n < 0)
	{
		digits = 1;
		n *= -1;
	}
	else
		digits = 0;
	if (n == 0)
		digits = 1;
	while (n > 0)
	{
		n = n / 10;
		digits++;
	}
	return (digits);
}

char	*ft_itoa(int n)
{
	char		*result;
	size_t		digits;
	long int	num;

	num = n;
	digits = ft_digit_count(num);
	if (n < 0)
		num *= -1;
	result = malloc(sizeof(char) * (digits + 1));
	if (!result)
		return (0);
	*(result + digits) = '\0';
	while (digits--)
	{
		*(result + digits) = (num % 10) + 48;
		num = num / 10;
	}
	if (n < 0)
		*(result + 0) = '-';
	return (result);
}
/*
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int main() {
    int number;
    printf("Enter an integer: ");
    scanf("%d", &number);

    char *result = ft_itoa(number);

    if (result) {
        printf("Result: %s\n", result);
        free(result); // Don't forget to free the allocated memory
    } else {
        printf("Memory allocation failed.\n");
    }

    return 0;
}*/
