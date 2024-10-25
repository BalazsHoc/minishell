/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: i2024/04/09 12:30:45 by bhocsak           #+#    #+#            */
/*   Updated: 2024/04/23 12:33:53 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*buffer;

	if (!nmemb || !size)
		return (malloc(0));
	if (size > SIZE_MAX / nmemb)
		return (0);
	buffer = (void *)malloc(size * nmemb);
	if (!buffer)
		return (0);
	ft_bzero(buffer, size * nmemb);
	return (buffer);
}
