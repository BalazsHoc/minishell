/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_of_those.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:52:19 by bhocsak           #+#    #+#             */
/*   Updated: 2025/02/02 14:52:21 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	one_of_those_2(char *str, int count)
{
	if (!str || !*str)
		return (0);
	if (str[0] == '.')
		count++;
	if (*str && (*(str + 1) && !one_of_those_2(str + 1, count)))
		return (0);
	else if (count <= 2 && (!str[0]
			|| str[0] == '.'
			|| str[0] == '/'))
		return (1);
	else
		return (0);
}

int	one_of_those_3(char *str)
{
	if (!ft_strncmp(str, "/usr", 4)
		|| (!ft_strncmp(str, "/snap", 5))
		|| (!ft_strncmp(str, "/bin", 4))
		|| (!ft_strncmp(str, "/sbin", 5)))
		return (1);
	return (0);
}

int	one_of_those(char *str)
{
	if (!ft_strncmp(str, "/", 2)
		|| !ft_strncmp(str, ".", 2)
		|| (!ft_strncmp(str, "/usr", 4)
			&& one_of_those_2(str + 4, 0))
		|| (!ft_strncmp(str, "/bin", 4)
			&& (one_of_those_2(str + 4, 0)))
		|| (!ft_strncmp(str, "/sbin", 5)
			&& one_of_those_2(str + 5, 0))
		|| (!ft_strncmp(str, "/snap", 5)
			&& one_of_those_2(str + 5, 0)))
		return (1);
	return (0);
}
