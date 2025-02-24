/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjuarez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 20:47:10 by cjuarez           #+#    #+#             */
/*   Updated: 2025/02/24 20:47:11 by cjuarez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	quotes_after(t_pipex *d, int i_1, int i_2)
{
	int	i;
	int	k;
	int	check;

	i = -1;
	check = 0;
	while (d->line[d->l[i_1]->pos[i_2][0] + ++i])
	{
		k = 0;
		while (d->line[d->l[i_1]->pos[i_2][0] + i + k]
			&& !is_space(d->line[d->l[i_1]->pos[i_2][0] + i + k]))
			k++;
		while (k && d->line[d->l[i_1]->pos[i_2][0] + i + k + check]
			&& is_space(d->line[d->l[i_1]->pos[i_2][0] + i + k + check]))
			check++;
		if (check && d->line[d->l[i_1]->pos[i_2][0] + i + k + check + 1]
			&& d->line[d->l[i_1]->pos[i_2][0] + i + k + check]
			&& (d->line[d->l[i_1]->pos[i_2][0] + i + k + check] == 34
			|| d->line[d->l[i_1]->pos[i_2][0] + i + k + check] == 39)
			&& (d->line[d->l[i_1]->pos[i_2][0] + i + k + check + 1] == 34
			|| d->line[d->l[i_1]->pos[i_2][0] + i + k + check + 1] == 39))
			return (1);
	}
	return (0);
}
