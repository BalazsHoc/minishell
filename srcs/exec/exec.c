/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:31:03 by bhocsak           #+#    #+#             */
/*   Updated: 2025/02/02 14:31:06 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_infile(t_pipex *data, int index_1, int index_2)
{
	if (is_in_inline(data, index_1, index_2) != -1
		&& !data->l[index_1]->red_cmnd[index_2][
		is_red_inline(data, index_1, index_2)]
		&& !ft_strncmp(data->l[index_1]->cmnds[index_2][
				is_red_inline(data, index_1, index_2)], "<", 2))
		return (1);
	return (0);
}

void	handle_child(t_pipex *d, int i_1, int i_2)
{
	d->fd_in = 0;
	d->fd_out = 0;
	if (check_infile(d, i_1, i_2))
		d->l[i_1]->fd_infiles[i_2] = open_this_read(d,
				d->l[i_1]->cmnds[i_2][is_red_inline(d, i_1, i_2) + 1]);
	if (d->l[i_1]->fd_infiles[i_2] != -1)
		d->fd_in = dup2(d->l[i_1]->fd_infiles[i_2], STDIN_FILENO);
	else if (i_2 > 0 && d->l[i_1]->pipes[i_2][1] != -1
		&& d->l[i_1]->fd_infiles[i_2] == -1 && !check_here_doc(d, i_1, i_2))
		d->fd_in = dup2(d->l[i_1]->pipes[i_2][0], STDIN_FILENO);
	else if (d->l[i_1]->buf_pipes[i_2][1] != -1
		&& d->l[i_1]->fd_infiles[i_2] == -1 && check_here_doc(d, i_1, i_2))
		d->fd_in = dup2(d->l[i_1]->buf_pipes[i_2][0], STDIN_FILENO);
	if (i_2 < d->l[i_1]->cmnd_count - 1
		&& d->l[i_1]->pipes[i_2 + 1][1] != -1
		&& d->l[i_1]->fd_outfiles[i_2] == -1)
		d->fd_out = dup2(d->l[i_1]->pipes[i_2 + 1][1], STDOUT_FILENO);
	else if (d->l[i_1]->fd_outfiles[i_2] != -1)
		d->fd_out = dup2(d->l[i_1]->fd_outfiles[i_2], STDOUT_FILENO);
	if (d->fd_out == -1 || d->fd_in == -1)
		return (perror("out dup2"), close_children_pipes(d, i_1, i_2),
			error_code(d));
	close_children_pipes(d, i_1, i_2);
	if (execve(d->l[i_1]->paths[i_2], d->l[i_1]->ops[i_2], d->cur_env) == -1)
		return (perror("execve"), error_code(d));
}

void	handle_mini_child(t_pipex *d, int i_1, int i_2)
{
	d->fd_in = 0;
	d->fd_out = 0;
	if (check_infile(d, i_1, i_2))
		d->l[i_1]->fd_infiles[i_2] = open_this_read(d,
				d->l[i_1]->cmnds[i_2][is_red_inline(d, i_1, i_2) + 1]);
	if (d->l[i_1]->fd_infiles[i_2] != -1)
		d->fd_in = dup2(d->l[i_1]->fd_infiles[i_2], STDIN_FILENO);
	else if (d->l[i_1]->pipes[i_2][1] != -1 && d->l[i_1]->fd_infiles[i_2] == -1
		&& !check_here_doc(d, i_1, i_2) && i_2 > 0)
		d->fd_in = dup2(d->l[i_1]->pipes[i_2][0], STDIN_FILENO);
	else if (d->l[i_1]->buf_pipes[i_2][1] != -1
		&& d->l[i_1]->fd_infiles[i_2] == -1
		&& check_here_doc(d, i_1, i_2))
		d->fd_in = dup2(d->l[i_1]->buf_pipes[i_2][0], STDIN_FILENO);
	if (i_2 < d->l[i_1]->cmnd_count - 1
		&& d->l[i_1]->fd_outfiles[i_2] == -1
		&& d->l[i_1]->pipes[i_2 + 1][1] != -1)
		d->fd_out = dup2(d->l[i_1]->pipes[i_2 + 1][1], STDOUT_FILENO);
	else if (d->l[i_1]->fd_outfiles[i_2] != -1)
		d->fd_out = dup2(d->l[i_1]->fd_outfiles[i_2], STDOUT_FILENO);
	if (d->fd_out == -1 || d->fd_in == -1)
		return (perror("error dup2"), error_code(d));
	return (mini_child(d, i_1, i_2), close_pipe(d, &d->fd_out),
		close_children_pipe(d, &d->fd_in),
		close_children_pipes(d, i_1, i_2), error_code(d));
}

void	exec_cmnd(t_pipex *data, int index_1, int index_2)
{
	signal_change(NULL, 2);
	if (check_here_doc(data, index_1, index_2)
		&& data->l[index_1]->pipes[index_2][1])
		create_buf_pipe(data, index_1, index_2);
	data->pid[index_2] = fork();
	if (data->pid[index_2] < 0)
		return (perror("fork"), error_code(data));
	else if (!data->pid[index_2])
		handle_child(data, index_1, index_2);
	else if (data->pid[index_2] && data->l[index_1]->input[index_2]
		&& data->l[index_1]->pipes[index_2][1])
	{
		write(data->l[index_1]->buf_pipes[index_2][1],
			data->l[index_1]->input[index_2],
			ft_strlen(data->l[index_1]->input[index_2]));
		free_str(&data->l[index_1]->input[index_2]);
	}
	close_pipe(data, &data->l[index_1]->pipes[index_2][1]);
}

void	exec_mini(t_pipex *data, int index_1, int index_2)
{
	if (data->l[index_1]->cmnds[1])
	{
		if (check_here_doc(data, index_1, index_2)
			&& data->l[index_1]->pipes[index_2][1])
			create_buf_pipe(data, index_1, index_2);
		data->pid[index_2] = fork();
		if (data->pid[index_2] < 0)
			return (perror("fork"), error_code(data));
		else if (!data->pid[index_2])
			handle_mini_child(data, index_1, index_2);
	}
	else
		mini_parent(data, index_1, index_2);
}
