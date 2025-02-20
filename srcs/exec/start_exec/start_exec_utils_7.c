/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec_utils_7.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 15:11:00 by bhocsak           #+#    #+#             */
/*   Updated: 2025/02/16 15:11:02 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	*handle_no_eof_continue(t_pipex *data, int i_1, int i_2, int i)
{
	char	*buf_1;
	char	*buf_2;

	buf_1 = NULL;
	buf_2 = NULL;
	buf_1 = get_input(data, i_1, i_2, i - 1);
	if (buf_1 && *buf_1)
	{
		buf_2 = ft_strjoin(data->l[i_1]->input[i_2], buf_1, data);
		free_str(&buf_1);
		buf_2 = ft_strtrim(buf_2, "\n", data);
		if (buf_2[ft_strlen(buf_2) - 1] != '\n')
			buf_1 = ft_strjoin(buf_2, "\n", data);
		else
			buf_1 = ft_strdup(data, buf_2);
		free_str(&data->l[i_1]->input[i_2]);
	}
	else if (free_this(&buf_1))
		buf_1 = data->l[i_1]->input[i_2];
	return (free_str(&buf_2), buf_1);
}

char	*handle_no_eof(t_pipex *data, int i_1, int i_2, char *input)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	while (data->l[i_1]->cmnds[i_2][++i])
	{
		if (!ft_strncmp("<<", data->l[i_1]->cmnds[i_2][i], 3) && ++i)
			break ;
	}
	j = data->l[i_1]->pos[i_2][i];
	j += ft_strlen(data->l[i_1]->cmnds[i_2][i]);
	data->l[i_1]->input[i_2] = input;
	while (data->line[++j])
	{
		k = 0;
		while (data->line[j - 1] == '\n' && data->line[j + k]
			&& data->line[j + k] != '\n' && data->l[i_1]->cmnds[i_2][i][k]
				&& data->line[j + k] == data->l[i_1]->cmnds[i_2][i][k])
			k++;
		if (k > 0 && !data->l[i_1]->cmnds[i_2][i][k] && (!data->line[j + k]
			|| data->line[j + k] == '\n'))
			return (input);
	}
	return (handle_no_eof_continue(data, i_1, i_2, i));
}

int	is_eof(t_pipex *data, int i_1, int i_2)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	while (data->l[i_1]->cmnds[i_2][++i])
	{
		if (!ft_strncmp("<<", data->l[i_1]->cmnds[i_2][i], 3) && ++i)
			break ;
	}
	j = data->l[i_1]->pos[i_2][i];
	j += ft_strlen(data->l[i_1]->cmnds[i_2][i]);
	while (++j == 0 || (data->line[j - 1] && data->line[j]))
	{
		k = 0;
		while (data->line[j - 1] == '\n' && data->line[j + k]
			&& data->line[j + k] != '\n' && data->l[i_1]->cmnds[i_2][i][k]
			&& data->line[j + k] == data->l[i_1]->cmnds[i_2][i][k])
			k++;
		if (k > 0 && !data->l[i_1]->cmnds[i_2][i][k] && (!data->line[j + k]
			|| data->line[j + k] == '\n'))
			return (1);
	}
	return (0);
}

char	*account_for_eof(t_pipex *data, int j)
{
	char	*new;
	int		k;

	k = 0;
	new = ft_calloc(sizeof(char), (((data->here_2 - (j + 1)
						- data->here_2_old) + 1) + 1), data);
	while (k < (data->here_2 - (j + 1) - data->here_2_old) + 1)
	{
		new[k] = data->line[data->here_2_old + k];
		k++;
	}
	return (new);
}

int	get_input_2(t_pipex *data, int index_1, int i)
{
	int		k;
	int		j;
	char	*new;
	char	*buf;

	k = 0;
	j = 2;
	while (data->line[data->here_2 - j]
		&& !is_d_b(data->line, data->here_2 - j, 0))
		j++;
	if (is_eof(data, index_1, i))
		new = account_for_eof(data, j);
	else
	{
		new = ft_calloc(sizeof(char), ((data->here_2
						- data->here_2_old) + 1), data);
		while (k < (data->here_2 - data->here_2_old))
		{
			new[k] = data->line[data->here_2_old + k];
			k++;
		}
	}
	buf = ft_strjoin(new, "\n", data);
	buf = handle_no_eof(data, index_1, i, buf);
	return (free_str(&new), data->l[index_1]->input[i] = buf, 1);
}
