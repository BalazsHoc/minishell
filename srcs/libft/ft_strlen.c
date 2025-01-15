/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:10:36 by bhocsak           #+#    #+#             */
/*   Updated: 2024/04/12 10:54:56 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (!str || !*str)
		return (0);
	while (str[i])
	{
		count++;
		if (!str[i + 1])
			break;
		i++;
	}
	return (count);
}
