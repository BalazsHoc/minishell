/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:02:48 by bhocsak           #+#    #+#             */
/*   Updated: 2024/04/13 11:50:35 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*sub;

	i = 0;
	if (!(s))
		return (0);
	if ((start >= ft_strlen(s)) || (len == 0))
		return (ft_calloc(1, sizeof(char)));
	if (len > (ft_strlen(s) - start))
		len = ft_strlen(s) - start;
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (sub == 0)
		return (0);
	while (i < len)
	{
		sub[i] = s[start];
		i++;
		start++;
	}
	sub[i] = '\0';
	return (sub);
}
/*
#include <stdio.h>

int	main()
{
	char const s[] = "hallokellotello";
	unsigned int start = 5;
	size_t len = 5;

	char result = *ft_substr(s, start, len);

	if (result == 0)
		printf("malloc didn't succeded: %s\n", &result);
	else
		printf("everything is fine: %s\n", &result);
}*/
