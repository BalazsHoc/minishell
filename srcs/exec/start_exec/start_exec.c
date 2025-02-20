/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:37:14 by bhocsak           #+#    #+#             */
/*   Updated: 2025/02/02 14:37:16 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	*ft_strnjoin_start(t_pipex *data, char *s1, char *s2, int size)
{
	char			*joined;
	int				i;
	int_least64_t	j;

	if (s1 == 0 && s2 == 0)
		return (0);
	i = size + ft_strlen(s2);
	joined = ft_calloc(sizeof(char), (i + 1), data);
	i = 0;
	while (s1[i] && i < size)
	{
		joined[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
	{
		joined[i + j] = s2[j];
		j++;
	}
	return (joined);
}

char	*cut_out_key(t_pipex *data, char *cur, int where, int size)
{
	char	*buf_1;
	char	*buf_2;
	char	*val;

	val = get_val(data, cur + where + 1);
	buf_1 = ft_strnjoin_start(data, cur, val, where);
	buf_2 = ft_strjoin(buf_1, cur + where + size + 1, data);
	free_str(&cur);
	free_str(&val);
	free_str(&buf_1);
	return (buf_2);
}

void	update_input(t_pipex *data, int index_1, int index_2)
{
	int		i;
	char	*buf;

	buf = data->l[index_1]->input[index_2];
	i = -1;
	while (buf[++i])
	{
		if (buf[i] == '$')
			buf = cut_out_key(data, buf, i, check_key(data, buf + i + 1));
	}
	data->l[index_1]->input[index_2] = buf;
}

void	handle_expansion_here_doc(t_pipex *data, int index_1)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (data->l[index_1]->cmnds[++j])
	{
		if (check_here_doc(data, index_1, j))
		{
			if (exec_cmnds_util_2(data, index_1, j))
				exec_cmnds_util_3(data, index_1, j);
		}
	}
	while (++i < data->l[index_1]->cmnd_count)
	{
		if (data->l[index_1]->input[i] && !data->l[index_1]->red_cmnd[i][
			is_red_inline(data, index_1, i) + 1])
			update_input(data, index_1, i);
	}
}

void	start_exec(t_pipex *data, int index, int i, int status)
{
	if (!here_doc(data, index, -1, -1))
		return ;
	handle_expansion_here_doc(data, index);
	exec_cmnds(data, index, i);
	close_pipes_array(data, index);
	data->buf_int = 0;
	while (++i < data->l[index]->cmnd_count)
	{
		if (check_here_doc(data, index, i))
			data->buf_int = 1;
		if (!data->l[index]->exit_codes[i])
		{
			waitpid(data->pid[i], &status, 0);
			if (WIFEXITED(status))
			{
				data->l[index]->exit_codes[i] = WEXITSTATUS(status);
				errno = data->l[index]->exit_codes[i];
			}
		}
	}
	if (skip_nl(data) && !data->buf_int)
		set_here(data, index);
	data->last_exit_status = data->l[index]->exit_codes[data->l[
		index]->cmnd_count - 1];
	data->buf_int = 0;
}
