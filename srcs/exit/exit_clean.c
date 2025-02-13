/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_clean.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:48:11 by bhocsak           #+#    #+#             */
/*   Updated: 2025/02/02 14:48:12 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	er_c(t_pipex *data)
{
	if (data)
		free_struct(data);
	rl_clear_history();
	exit(errno);
}

void	exit_child(t_pipex *data, int index_1, int index_2, int errnum)
{
	int	status;

	data->pid[index_2] = fork();
	if (data->pid[index_2] == -1)
		return (perror("fork failed\n"), er_c(data));
	if (!data->pid[index_2])
	{
		errno = errnum;
		er_c(data);
	}
	else
	{
		if (waitpid(data->pid[index_2], &status, 0) == -1)
			return (perror("waitpid failed!"), er_c(data));
		data->l[index_1]->exit_codes[index_2] = WEXITSTATUS(status);
		errno = WEXITSTATUS(status);
	}
}
