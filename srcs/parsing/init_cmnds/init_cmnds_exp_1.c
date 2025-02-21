/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmnds_exp_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:54:20 by bhocsak           #+#    #+#             */
/*   Updated: 2025/02/02 14:54:21 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	ex_1_0(t_pipex *data, char **elem, int open, int *i)
{
	if (i && open != 1)
	{
		*elem = get_pid(data);
		data->buf_int = open;
		ft_strncpy(data->buf_str, *elem, ft_strlen_2(*elem));
		*i += 2;
	}
}

void	ex_1_1(t_pipex *data, char **elem, int open, int *i)
{
	if (errno != 130)
		*elem = ft_itoa(data->last_exit_status, data);
	else
		*elem = ft_strdup(data, "130");
	data->buf_int = open;
	ft_strncpy(data->buf_str, *elem, ft_strlen_2(*elem));
	*i += 2;
}

void	ex_1_2(t_pipex *data, char **elem, int open, int *i)
{
	*elem = get_val(data, data->line + *i + 1);
	if (check_key(data, data->line + *i + 1))
		*i += check_key(data, data->line + *i + 1) + 1;
	else
		*i += count_chars_2(data, *i);
	data->buf_int = open;
	ft_strncpy(data->buf_str, *elem, ft_strlen_2(*elem));
}

int	ex_1_3(t_pipex *data, char **elem, int i, int open)
{
	if (free_this(&*elem) && open == 2
		&& is_q_2(data->line[i]) && (!data->line[i + 1]
			|| is_space(data->line[i + 1])))
		return (1);
	return (0);
}

int	expand_it_1(t_pipex *d, int i, int open, char **s)
{
	char	*elem;

	elem = NULL;
	*s = ft_calloc(sizeof(char), (count_ex(d, i, open, 0) + 1), d);
	d->buf_str = *s;
	while (d->line[i])
	{
		if (open != 1 && d->line[i] == '$' && d->line[i + 1] == '$')
			ex_1_0(d, &elem, open, &i);
		else if (open != 1 && d->line[i] == '$' && (d->line[i + 1] == '?'))
			ex_1_1(d, &elem, open, &i);
		else if (open != 1 && d->line[i] == '$' && d->line[i + 1] != '?')
			ex_1_2(d, &elem, open, &i);
		if (elem && ft_strlen_2(elem) >= 0)
			d->buf_str = d->buf_str + ft_strlen_2(elem);
		if (ex_1_3(d, &elem, i, open)
			|| (handle_open(d, i, &open) && !open && ex_1_4(d, i)))
			break ;
		if (ex_1_5(d, i, open))
			*(d->buf_str)++ = d->line[i];
		if (ex_1_6(d, i, open))
			i++;
	}
	// printf("NEW: |%s|\n", *s);
	d->buf_str = NULL;
	return (elem = *s, 1);
}
