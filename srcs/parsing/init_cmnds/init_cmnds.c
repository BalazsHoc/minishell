/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmnds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:54:01 by bhocsak           #+#    #+#             */
/*   Updated: 2025/02/02 14:54:02 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	ft_strncpy_2(char *dest, char *src, int size, t_pipex *data)
{
	int	i;
	int	j;
	int	open;

	i = 0;
	j = 0;
	open = data->buf_int;
	if (!src || !*src)
		return ;
	while (j < size)
	{
		if (src[i] && is_quote_one(src[i]) && !open)
			open = 1;
		else if (is_q_2(src[i]) && !open)
			open = 2;
		else if ((is_quote_one(src[i]) && open == 1)
			|| (is_q_2(src[i]) && open == 2))
			open = 0;
		if (src[i] && ((!is_quote(src[i])) || ((open == 1 && is_q_2(src[i]))
					|| (open == 2 && is_quote_one(src[i])))))
			dest[j++] = src[i];
		i++;
	}
	data->buf_int = 0;
}

void	ft_strncpy(char *dest, char *src, int size)
{
	int	i;

	i = -1;
	if (!src || !*src)
		return ;
	while (++i < size)
		dest[i] = src[i];
}

int	ft_strlen_2(char *s)
{
	size_t	i;
	int		count;

	i = 0;
	count = 0;
	if (!s || !*s)
		return (0);
	while (s[i])
	{
		if (!(((i == 0 || !s[i + 1]) || ft_strlen(s) == 1)
				&& s[i] == 34 && s[i] == 39))
			count++;
		if (!s[i + 1])
			break ;
		i++;
	}
	return (count);
}

char	*malloc_str(size_t size, t_pipex *data)
{
	char	*new;

	new = ft_calloc(sizeof(char), (size + 1), data);
	new[size] = 0;
	return (new);
}

void	fill_cmnds(t_pipex *d, int i_1, int i, int j)
{
	d->k = -i;
	d->open = 0;
	d->i_2 = -1;
	while (if_1(d, &j) && j < d->l[i_1]->limit)
	{
		if (d->k < 0)
			handle_open(d, j, &d->open);
		if (if_2(d, j) && set_pos(&d->l[i_1]->pos[i][d->i_2], j))
			fill_for_empty(d, i_1, i, d->i_2);
		if (check_home(d, &j, i_1, i) && if_3(d, j, i_1, i))
			d->l[i_1]->red_cmnd[i][d->i_2] = 2;
		if (d->line[j] && if_4(d, j))
		{
			if (d_in(d, j, d->open) >= 0 && if_5(d, i, i_1)
				&& expand_it_1(d, j, d->open, &d->l[i_1]->cmnds[i][++d->i_2]))
				d->i_2 += expand_it_2(d, i_1, i, d->i_2);
			else
				d->l[i_1]->cmnds[i][++d->i_2] = fill_normal(d, j, d->open);
			d->l[i_1]->pos[i][d->i_2] = j;
			if ((if_6(d, j, d->open) && if_7(d, i_1, d->i_2, i))
				|| (if_8(d, i_1, i) && if_9(d, j)))
				d->l[i_1]->red_cmnd[i][d->i_2] = 1;
		}
	}
}
