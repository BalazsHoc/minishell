/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   none_sense_here_doc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:59:27 by bhocsak           #+#    #+#             */
/*   Updated: 2025/02/23 16:59:30 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	does_key_exist(char *line, int i)
{
	while (line[++i])
	{
		if (is_char(line[i]))
			return (i);
	}
	return (0);
}

char	*get_key(t_pipex *data, char *line, int i)
{
	int		j;
	char	*key;

	j = 0;
	while (line[i + j] && !is_delim_front(line, i + j))
		j++;
	key = ft_calloc(sizeof(char), j + 1, data);
	j = -1;
	while (line[i + ++j] && !is_delim_front(line, i + j))
		key[j] = line[i + j];
	return (key);
}

int	do_nonesense_find_key(t_pipex *d, char *key, int *i)
{
	int	j;
	int	k;
	int	check;

	j = -1;
	check = 0;
	while (d->line[*i + ++j])
	{
		k = 0;
		while (d->line[*i + j + k] && key[k] && d->line[*i + j + k] == key[k])
			k++;
		if (!key[k] && d->line[*i + j - 1] == '\n'
			&& (!d->line[*i + j + k] || d->line[*i + j + k] == '\n'))
		{
			check = *i + j + k;
			break ;
		}
	}
	while (check && d->line[check] && d->line[check] == '\n')
		check++;
	if (check)
		d->here_2_old = check;
	return (check);
}

void	do_nonesense_here_doc(t_pipex *d, int check, char *b, char *key)
{
	int		i;
	int		buf_here_2;

	i = d->here_2 - 1;
	buf_here_2 = 0;
	while (free_this(&b) && ++i < check && !g_signal)
	{
		if (!ft_strncmp(d->line + i, "<<", 2) && does_key_exist(d->line, i))
		{
			buf_here_2 = d->here_2_old;
			key = get_key(d, d->line, does_key_exist(d->line, i));
			if (d->here_2_old && (!do_nonesense_find_key(d, key, &buf_here_2)))
			{
				b = readline("> ");
				while (b && !g_signal && !ft_strcmp_2(b, key) && free_this(&b))
					b = readline("> ");
				if (!b)
					here_doc_err_msg(key);
			}
			if (free_this(&key) && g_signal)
				return (free_str(&b));
		}
	}
	if (d->here_2_old == buf_here_2)
		d->here_2_old = count_nl(d, d->here_2_old);
}
