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

int	expand_2_util_1(t_pipex *d, int index_1, int index_2, int index_3)
{
	if (!d->l[index_1]->cmnds[index_2][index_3] && index_3 > 0 && ft_strncmp(
			d->l[index_1]->cmnds[index_2][index_3 - 1], "<<", 3)
				&& is_red(d, index_1, index_2, index_3 - 1))
		return (d->l[index_1]->red_cmnd[index_2][index_3 - 1] = 2, -1);
	if (!count_elem_spaces(d, d->l[index_1]->cmnds[index_2][index_3]))
		return (1);
	if (index_3 && is_red(d, index_1, index_2, index_3 - 1)
		&& ft_strncmp(d->l[index_1]->cmnds[index_2][index_3 - 1], "<<", 3))
		d->l[index_1]->red_cmnd[index_2][index_3 - 1] = 2;
	return (0);
}

int	expand_2_util_2(t_pipex *d, int i, char *buf)
{
	if ((buf[i + 1] == '\n' || !buf[i + 1])
		&& buf[i] != '\n' && ++d->buf_int != INT_MIN)
		return (1);
	return (0);
}

int	tspace(t_pipex *data, int i_1, int i_2, int i_3)
{
	char	*new;
	char	*str;
	int		i;

	str = data->l[i_1]->cmnds[i_2][i_3];
	new = ft_calloc(ft_strlen(str) + 1, 1, data);
	i = -1;
	while (str[++i])
	{
		if (str[i] != '\n')
			new[i] = str[i];
		else
			new[i] = ' ';
	}
	free_str(&str);
	data->l[i_1]->cmnds[i_2][i_3] = new;
	return (1);
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
	if (expand_2_util_1(d, i_1, i_2, i_3) == -1
		|| (expand_2_util_1(d, i_1, i_2, i_3) > 0 && tspace(d, i_1, i_2, i_3)))
		return (0);
	buf = d->l[i_1]->cmnds[i_2][i_3];
	while ((buf[++i] && buf[i] != '\n' && ++j != INT_MIN) || buf[i])
	{
		if (expand_2_util_2(d, i, buf))
		{
			d->buf_str = ft_calloc(sizeof(char), (++j + 1), d);
			k = i;
			while (--j >= 0)
				d->buf_str[j] = buf[(k--)];
			j = -1;
			d->l[i_1]->cmnds[i_2][i_3 + d->buf_int] = d->buf_str;
		}
	}
	return (free_str(&buf), d->buf_int);
}
