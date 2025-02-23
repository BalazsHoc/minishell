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
	if (!count_elem_spaces(d, d->l[index_1]->cmnds[index_2][index_3]))
		return (1);
	if (index_3 && is_red(d, index_1, index_2, index_3 - 1)
		&& ft_strncmp(d->l[index_1]->cmnds[index_2][index_3 - 1], "<<", 3))
		d->l[index_1]->red_cmnd[index_2][index_3 - 1] = 2;
	return (0);
}

int	expand_it_2_utils_2(t_pipex *d, int i)
{
	if ((d->buf_str[i + 1] == '\n' || !d->buf_str[i + 1])
		&& d->buf_str[i] != '\n' && ++d->buf_int != INT_MIN)
		return (1);
	return (0);
}

void	change_to_spaces(t_pipex *data, int i_1, int i_2, int i_3)
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
		return (change_to_spaces(d, i_1, i_2, i_3), 0);
	d->buf_str = d->l[i_1]->cmnds[i_2][i_3];
	while ((d->buf_str[++i] && d->buf_str[i] != '\n' && ++j != INT_MIN)
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
