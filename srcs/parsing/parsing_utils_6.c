/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_6.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:39:31 by bhocsak           #+#    #+#             */
/*   Updated: 2025/02/24 17:39:32 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	check_ambigious(t_pipex *d, int i_1)
{
	int	i;
	int	j;

	i = -1;
	while (d->l[i_1]->cmnds[++i])
	{
		j = -1;
		while (d->l[i_1]->cmnds[i][++j])
		{
			if (is_red_basic(d, i_1, i, j) && d->l[
					i_1]->red_cmnd[i][j] == 2)
			{
				write(2, "bash: ambigiuous redirect\n", 27);
				d->l[i_1]->exit_codes[i] = 1;
				break ;
			}
		}
	}
}
