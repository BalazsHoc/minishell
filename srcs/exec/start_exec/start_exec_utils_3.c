/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec_utils_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:38:38 by bhocsak           #+#    #+#             */
/*   Updated: 2025/02/02 14:38:41 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	exec_cmnds_util_1(t_pipex *data, int index, int i)
{
	if (ft_strncmp(data->l[index]->paths[i], "pathnfound", 11)
		&& is_valid_in(data, index, i) >= 0 && data->fd_out >= 0
		&& data->l[index]->ops[i][0][0]
				&& data->l[index]->pipes[i][1] != -1
				&& data->l[index]->pipes[i][0] != -1)
		return (1);
	return (0);
}

int	exec_cmnds_util_2(t_pipex *data, int index, int i)
{
	if ((data->here_2_old < find_key(data, index, i,
				is_red_inline(data, index, i) + 1)
			|| find_key(data, index, i,
				is_red_inline(data, index, i) + 1) == data->here_2)
		&& get_input_2(data, index, i))
		return (1);
	return (0);
}

void	exec_cmnds_util_3(t_pipex *data, int index, int i)
{
	data->here_2_old = find_key(data, index, i,
			is_red_inline(data, index, i) + 1);
}

int	exec_cmnds_util_4(t_pipex *data, int index, int i, char *path)
{
	if (is_valid_in(data, index, i) == -1 && !data->l[index]->exit_codes[i])
		return (write(2, "bash: ", 6),
			write(2, data->l[index]->cmnds[i][
				first_invalid_in(data, index, i)],
			ft_strlen(data->l[index]->cmnds[i][
				first_invalid_in(data, index, i)])),
						write(2, ": No such file or directory\n", 29),
							exit_child(data, index, i, 1), 1);
	else if (check_cmnd_as_dir(data, index, i)
		&& !one_of_those(data->l[index]->ops[i][0])
		&& one_of_those_3(data->l[index]->ops[i][0])
			&& !data->l[index]->exit_codes[i])
		return (write(2, "bash: ", 6),
			write(2, data->l[index]->ops[i][0], ft_strlen(data->l[
					index]->ops[i][0])), write(2, ": Not a directory\n", 19),
					exit_child(data, index, i, 126), 1);
	else if (((path && !(path[5])) || !path) && !ft_strncmp(data->l[
				index]->paths[i], "pathnfound", 11)
		&& !data->l[index]->exit_codes[i])
		return (write(2, "bash: ", 6),
			write(2, data->l[index]->ops[i][0],
			ft_strlen(data->l[index]->ops[i][0])),
					write(2, ": No such file or directory\n", 29),
					exit_child(data, index, i, 127), 1);
	return (0);
}

void	exec_cmnds(t_pipex *data, int index, int i)
{
	while (data->l[index]->cmnds[++i])
	{
		data->fd_in = 0;
		data->fd_out = 0;
		data->l[index]->fd_ou[i] = open_out(data, index, i);
		if (exec_cmnds_util_1(data, index, i))
		{
			if (!ft_strncmp(data->l[index]->paths[i], "minicmnds", 10))
				exec_mini(data, index, i);
			else
				exec_cmnd(data, index, i);
		}
		else if (exec_cmnds_util_4(data, index, i, get_path(data)))
			continue ;
		else if (!ft_strncmp(data->l[index]->paths[i], "pathnfound", 11)
			&& data->l[index]->ops[i][0] && !data->l[index]->exit_codes[i]
			&& write(2, data->l[index]->ops[i][0],
			ft_strlen(data->l[index]->ops[i][0]))
				&& write(2, ": command not found\n", 21))
			exit_child(data, index, i, 127);
		close_pipes(data, index, i);
	}
}
