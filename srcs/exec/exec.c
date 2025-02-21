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

void	handle_child(t_pipex *d, int i_1, int i_2)
{
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
		&& d->l[i_1]->fd_ou[i_2] == -1)
		d->fd_out = dup2(d->l[i_1]->pipes[i_2 + 1][1], STDOUT_FILENO);
	else if (d->l[i_1]->fd_ou[i_2] >= 0)
		d->fd_out = dup2(d->l[i_1]->fd_ou[i_2], STDOUT_FILENO);
	else if (d->l[i_1]->fd_ou[i_2] == -2
		&& d->l[i_1]->buf_pipes[i_2][1] != -1)
		d->fd_out = dup2(d->l[i_1]->buf_pipes[i_2][1], STDOUT_FILENO);
	if ((d->fd_out == -1 || d->fd_in == -1))
		return (perror("dup2"), cl_chi_pipes(d, i_1, i_2), er_c(d));
	cl_chi_pipes(d, i_1, i_2);
	// char *args[] = {"/bin/bash", "./cat", NULL};
	// char *path = "/bin/bash";
	// printf("PATH: %s, %s, %s\n", path, args[0], args[1]);
	// printf("PATH: %s, %s, %s\n", d->l[i_1]->paths[i_2], d->l[i_1]->ops[i_2][0], d->l[i_1]->ops[i_2][1]);
	// if (execve(path, args, NULL) == -1)
	if (execve(d->l[i_1]->paths[i_2], d->l[i_1]->ops[i_2], d->cur_env) == -1)
		return (perror("execve"), er_c(d));
}

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

// void handle_mini_child(t_pipex *d, int i_1, int i_2)
// {
//     // Print current file descriptors to check if stdin is open
//     printf("Before redirection: isatty(STDIN_FILENO) = %d\n", isatty(STDIN_FILENO));

//     // Ensure stdin is valid
//     if (isatty(STDIN_FILENO) == 0) {
//         int fd = open("/dev/null", O_RDONLY);
//         if (fd != -1)
//         {
//             dup2(fd, STDIN_FILENO);
//             close(fd);
//         }
//         printf("Redirected stdin to /dev/null\n");
//     }

//     // Print to check if stdin was successfully redirected
//     printf("After redirection: isatty(STDIN_FILENO) = %d\n", isatty(STDIN_FILENO));

//     // Redirect stdin properly
//     if (d->l[i_1]->fd_infiles[i_2] != -1) {
//         printf("Redirecting stdin from infile\n");
//         d->fd_in = dup2(d->l[i_1]->fd_infiles[i_2], STDIN_FILENO);
//     }
//     else if (d->l[i_1]->pipes[i_2][1] != -1 && d->l[i_1]->fd_infiles[i_2] == -1
//         && !check_here_doc(d, i_1, i_2) && i_2 > 0) {
//         printf("Redirecting stdin from pipe\n");
//         d->fd_in = dup2(d->l[i_1]->pipes[i_2][0], STDIN_FILENO);
//     }
//     else if (d->l[i_1]->buf_pipes[i_2][1] != -1
//         && d->l[i_1]->fd_infiles[i_2] == -1
//         && check_here_doc(d, i_1, i_2)) {
//         printf("Redirecting stdin from here-doc\n");
//         d->fd_in = dup2(d->l[i_1]->buf_pipes[i_2][0], STDIN_FILENO);
//     }

//     // Debug check if redirection worked
//     printf("After dup2: isatty(STDIN_FILENO) = %d\n", isatty(STDIN_FILENO));

//     // Redirect stdout
//     if (i_2 < d->l[i_1]->cmnd_count - 1
//         && d->l[i_1]->fd_ou[i_2] == -1 && d->l[i_1]->pipes[i_2 + 1][1] != -1) {
//         printf("Redirecting stdout to pipe\n");
//         d->fd_out = dup2(d->l[i_1]->pipes[i_2 + 1][1], STDOUT_FILENO);
//     }
//     else if (d->l[i_1]->fd_ou[i_2] >= 0) {
//         printf("Redirecting stdout to outfile\n");
//         d->fd_out = dup2(d->l[i_1]->fd_ou[i_2], STDOUT_FILENO);
//     }
//     else if (d->l[i_1]->fd_ou[i_2] == -2
//         && d->l[i_1]->buf_pipes[i_2][1] != -1) {
//         printf("Redirecting stdout to buffer pipe\n");
//         d->fd_out = dup2(d->l[i_1]->buf_pipes[i_2][1], STDOUT_FILENO);
//     }

//     if (d->fd_out == -1 || d->fd_in == -1) {
//         perror("Error dup2");
//         return (cl_chi_pipes(d, i_1, i_2), er_c(d));
//     }
//     // Call child process
//     d->fd_out_2 = dup(STDOUT_FILENO);
//     printf("Calling mini_child()\n");
//     mini_child(d, i_1, i_2);

//     // Restore stdout
//     printf("Restoring stdout\n");
//     close(d->fd_out_2);
//     // dup2(d->fd_out_2 , STDOUT_FILENO);

//     close_children_pipe(d, &d->fd_in);
//     close_children_pipe(d, &d->fd_out);
//     cl_chi_pipes(d, i_1, i_2);

//     return (er_c(d));
// }

void	handle_mini_child(t_pipex *d, int i_1, int i_2)
{
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
		&& d->l[i_1]->fd_ou[i_2] == -1
		&& d->l[i_1]->pipes[i_2 + 1][1] != -1)
		d->fd_out = dup2(d->l[i_1]->pipes[i_2 + 1][1], STDOUT_FILENO);
	else if (d->l[i_1]->fd_ou[i_2] >= 0)
		d->fd_out = dup2(d->l[i_1]->fd_ou[i_2], STDOUT_FILENO);
	else if (d->l[i_1]->fd_ou[i_2] == -2
		&& d->l[i_1]->buf_pipes[i_2][1] != -1)
		d->fd_out = dup2(d->l[i_1]->buf_pipes[i_2][1], STDOUT_FILENO);
	if (d->fd_out == -1 || d->fd_in == -1)
		return (perror("error dup2"), cl_chi_pipes(d, i_1, i_2), er_c(d));
	return (mini_child(d, i_1, i_2), close_pipe(d, &d->fd_out),
		close_children_pipe(d, &d->fd_in), cl_chi_pipes(d, i_1, i_2), er_c(d));
}

void	handle_parent_child(t_pipex *d, int i_1, int i_2)
{
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
		&& d->l[i_1]->fd_ou[i_2] == -1
		&& d->l[i_1]->pipes[i_2 + 1][1] != -1)
		d->fd_out = dup2(d->l[i_1]->pipes[i_2 + 1][1], STDOUT_FILENO);
	else if (d->l[i_1]->fd_ou[i_2] >= 0)
		d->fd_out = dup2(d->l[i_1]->fd_ou[i_2], STDOUT_FILENO);
	else if (d->l[i_1]->fd_ou[i_2] == -2 && d->l[i_1]->buf_pipes[i_2][1] != -1)
		d->fd_out = dup2(d->l[i_1]->buf_pipes[i_2][1], STDOUT_FILENO);
	if (d->fd_out == -1 || d->fd_in == -1)
		return (perror("error dup2"), er_c(d));
	cl_chi_pipes(d, i_1, i_2);
	return (parent_child(d, i_1, i_2), close_pipe(d, &d->fd_out),
		close_children_pipe(d, &d->fd_in), er_c(d));
}

void	exec_cmnd(t_pipex *data, int index_1, int index_2)
{
	if (check_cat_inline(data, index_1))
		signal_change(NULL, 3);
	else
		signal_change(NULL, 2);
	if ((check_here_doc(data, index_1, index_2)
			&& data->l[index_1]->pipes[index_2][1])
		|| data->l[index_1]->fd_ou[index_2] == -2)
		create_buf_pipe(data, index_1, index_2);
	data->pid[index_2] = fork();
	if (data->pid[index_2] < 0)
		return (perror("fork"), er_c(data));
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
		if ((check_here_doc(data, index_1, index_2)
				&& data->l[index_1]->pipes[index_2][1])
			|| data->l[index_1]->fd_ou[index_2] == -2)
			create_buf_pipe(data, index_1, index_2);
		data->pid[index_2] = fork();
		if (data->pid[index_2] < 0)
			return (perror("fork"), er_c(data));
		else if (!data->pid[index_2])
			handle_mini_child(data, index_1, index_2);
	}
	else
	{
		if ((check_here_doc(data, index_1, index_2)
				&& data->l[index_1]->pipes[index_2][1])
			|| data->l[index_1]->fd_ou[index_2] == -2)
			create_buf_pipe(data, index_1, index_2);
		data->pid[index_2] = fork();
		if (data->pid[index_2] < 0)
			return (perror("fork"), er_c(data));
		else if (!data->pid[index_2])
			handle_parent_child(data, index_1, index_2);
		mini_parent(data, index_1, index_2);
	}
}
