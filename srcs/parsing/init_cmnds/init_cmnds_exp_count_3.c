/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmnds_exp_count_3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:00:30 by bhocsak           #+#    #+#             */
/*   Updated: 2025/02/23 17:00:32 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	ft_strncpy_4(char **buf, char *elem, int size)
{
	int		i;
	char	*cur;

	i = -1;
	cur = *buf;
	while (++i < size)
	{
		if (elem[i] != ' ')
			cur[i] = elem[i];
		else
			cur[i] = '\n';
	}
}
