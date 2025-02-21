/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmnds_exp_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:54:38 by bhocsak           #+#    #+#             */
/*   Updated: 2025/02/02 14:54:39 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	expand_it_2_utils_1(t_pipex *d, int index_1, int index_2, int index_3)
{
	if (d->count_elem <= index_3
		+ count_elem_spaces(d, d->l[index_1]->cmnds[index_2][index_3])
		|| !count_elem_spaces(d, d->l[index_1]->cmnds[index_2][index_3]))
		return (1);
	return (0);
}

int	expand_it_2_utils_2(t_pipex *d, int i)
{
	if ((is_space(d->buf_str[i + 1]) || !d->buf_str[i + 1])
		&& !is_space(d->buf_str[i]) && ++d->buf_int != INT_MIN)
		return (1);
	return (0);
}

int	expand_it_2(t_pipex *d, int i_1, int i_2, int i_3)
{
	int		i;
	int		j;
	int		k;
	char	*buf;

	i = -1;
	j = -1;
	d->buf_int = -1;
	if (expand_it_2_utils_1(d, i_1, i_2, i_3))
		return (0);
	d->buf_str = d->l[i_1]->cmnds[i_2][i_3];
	while ((d->buf_str[++i] && !is_space(d->buf_str[i]) && ++j != INT_MIN)
		|| d->buf_str[i])
	{
		if (expand_it_2_utils_2(d, i))
		{
			buf = ft_calloc(sizeof(char), (++j + 1), d);
			k = i;
			while (--j >= 0)
				buf[j] = d->buf_str[(k--)];
			j = -1;
			d->l[i_1]->cmnds[i_2][i_3 + d->buf_int] = buf;
		}
	}
	return (free_str(&d->buf_str), d->buf_int);
}
