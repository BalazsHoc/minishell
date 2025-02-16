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

void	ex_1_0(t_pipex *data, char **new)
{
	free_str(&*new);
	data->buf_str = NULL;
	*new = get_pid(data);
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
	// printf("VAL: %s\n", *elem);
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

int	expand_it_1(t_pipex *data, int i, int open, char **new)
{
	char	*elem;

	elem = NULL;
	*new = ft_calloc(sizeof(char), (count_ex(data, i, open, 0) + 1), data);
	data->buf_str = *new;
	// printf("START EXPANSION\n");
	while (data->line[i])
	{
		// printf("EXPANSION1: %s | OPEN: %d\n", data->line + i, open);
		if (open != 1 && data->line[i] == '$' && data->line[i + 1] == '$')
			return (ex_1_0(data, &*new), 1);
		if (open != 1 && data->line[i] == '$' && (data->line[i + 1] == '?'))
			ex_1_1(data, &elem, open, &i);
		else if (open != 1 && data->line[i] == '$' && data->line[i + 1] != '?')
			ex_1_2(data, &elem, open, &i);
		if (elem && ft_strlen_2(elem) >= 0)
			data->buf_str = data->buf_str + ft_strlen_2(elem);
		if (ex_1_3(data, &elem, i, open))
			break ;
		// printf("EXPANSION1: %s | OPEN: %d\n", data->line + i, open);
		if (handle_open(data, i, &open) && !open && ex_1_4(data, i))
			break ;
		if (ex_1_5(data, i, open))
			*(data->buf_str)++ = data->line[i];
		if (ex_1_6(data, i, open))
			i++;
	}
	// printf("NEW: %s\n", *new);
	return (data->buf_str = NULL, 1);
}
