/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:05:35 by bhocsak           #+#    #+#             */
/*   Updated: 2024/04/18 11:42:21 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if ((unsigned char )c == ((unsigned char *)s)[i])
			return (((unsigned char *)s) + i);
		i++;
	}
	return (0);
}
/*
#include <stdio.h>

int	main()
{
	char dom[10] = "HlloBello";
	int c = 101;
	size_t 	n = 7;

	char	*result = ft_memchr(dom, c, n);
	printf("result: %s\n", result);
}*/
