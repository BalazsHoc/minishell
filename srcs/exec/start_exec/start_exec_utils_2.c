/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:38:27 by bhocsak           #+#    #+#             */
/*   Updated: 2025/02/02 14:38:29 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	here_doc_util_1(t_pipex *data, int index_1, int index_2, int i)
{
	if (!ft_strncmp(data->l[index_1]->cmnds[index_2][i], "<<", 3)
		&& !data->l[index_1]->red_cmnd[index_2][i]
				&& find_key(data, index_1, index_2, i + 1) == data->here_2_old)
		return (1);
	return (0);
}

int	here_doc_util_2(t_pipex *data, int index_1, int index_2, int i)
{
	if (((!ft_strncmp(data->l[index_1]->paths[index_2], "pathnfound", 11)
				|| (is_valid_in(data, index_1, index_2) == -1))
			&& i == is_red_inline(data, index_1, index_2))
		|| i != is_red_inline(data, index_1, index_2))
		return (1);
	return (0);
}

int	here_doc_util_3(t_pipex *data, int index_1, int index_2, int i)
{
	if (!ft_strncmp(data->l[index_1]->cmnds[index_2][i], "<<", 3)
				&& (!ft_strncmp(data->l[index_1]->paths[index_2],
					"pathnfound", 11)
					|| i != is_red_inline(data, index_1, index_2))
						&& find_key(data, index_1, index_2, i + 1))
		return (1);
	return (0);
}

int	here_doc(t_pipex *data, int index_1, int index_2, int i)
{
	signal_change(NULL, 1);
	data->buf_str = NULL;
	while (data->l[index_1]->cmnds[++index_2])
	{
		i = -1;
		while (data->l[index_1]->cmnds[index_2][++i])
		{
			if (here_doc_util_1(data, index_1, index_2, i))
			{
				data->buf_str = get_input(data, index_1, index_2, i);
				if (!data->buf_str && g_signal)
					return (signal_change(NULL, 2), 0);
				if (here_doc_util_2(data, index_1, index_2, i))
					free_str(&data->buf_str);
				else if (data->buf_str)
					data->l[index_1]->input[index_2] = data->buf_str ;
				data->buf_str = NULL;
			}
			else if (here_doc_util_3(data, index_1, index_2, i))
				data->here_2_old = find_key(data, index_1, index_2, i + 1);
		}
	}
	return (1);
}

int	if_th(t_pipex *data, int index_1, int index_2, int i)
{
	if (!ft_strncmp(data->l[index_1]->cmnds[index_2][i + 1], "|", 2)
		&& index_2 != data->l[index_1]->ex)
		return (1);
	return (0);
}
