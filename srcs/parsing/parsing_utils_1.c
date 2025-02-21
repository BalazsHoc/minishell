/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_is_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:52:57 by bhocsak           #+#    #+#             */
/*   Updated: 2025/02/02 14:52:59 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	is_quote(char c)
{
	if (c == 39 || c == 34)
		return (1);
	return (0);
}

int	is_quote_one(char c)
{
	if (c == 39)
		return (1);
	return (0);
}

int	is_q_2(char c)
{
	if (c == 34)
		return (1);
	return (0);
}

int	is_or(char *cur)
{
	if (cur[0] == '|' && cur[-1] == '|')
		return (1);
	if (cur[0] == '|' && cur[+1] == '|')
		return (1);
	return (0);
}
