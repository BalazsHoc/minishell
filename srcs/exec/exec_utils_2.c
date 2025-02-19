/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:58:35 by bhocsak           #+#    #+#             */
/*   Updated: 2025/02/18 14:58:37 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void close_in_out_2(t_pipex *d)
{
	close_pipe(d, &d->fd_out);
	close_pipe(d, &d->fd_out_2);
	close_pipe(d, &d->fd_in_2);
	close_pipe(d, &d->fd_in);
	d->fd_in = -2;
	d->fd_out = -2;
	d->fd_out_2 = -2;
}

int	check_cat_inline(t_pipex *data, int i_1)
{
	int	i;

	i = 0;
	while (data->l[i_1]->cmnds[i]
		&& data->l[i_1]->ops[i] && data->l[i_1]->ops[i][0]
		&& (!ft_strncmp(data->l[i_1]->ops[i][0], "cat", 4)
		|| !ft_strncmp(data->l[i_1]->ops[i][0], "usr/bin/cat", 12)
			|| !ft_strncmp(data->l[i_1]->ops[i][0], "/bin/cat", 9)))
		i++;
	if (i == data->l[i_1]->cmnd_count)
		return (1);
	return (0);
}

int	handle_mini_child_u_2(t_pipex *d, int i_1, int i_2)
{
	d->fd_out = -2;
	d->fd_out_2 = dup(STDOUT_FILENO);
	d->fd_in = -2;
	d->fd_in_2 = dup(STDIN_FILENO);
	if (check_infile(d, i_1, i_2))
		d->l[i_1]->fd_infiles[i_2] = open_this_read(d,
				d->l[i_1]->cmnds[i_2][is_red_inline(d, i_1, i_2) + 1]);
	return (1);
}
