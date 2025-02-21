/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:48:27 by bhocsak           #+#    #+#             */
/*   Updated: 2025/02/02 14:48:29 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_str(char **str)
{
	if (*str)
		free(*str);
	*str = NULL;
}

void	free_void(void *this)
{
	if (this)
		free(this);
	this = NULL;
}

void	free_line_continue(t_pipex *data, int index)
{
	free_void((data->l[index]->fd_infiles));
	free_void(data->l[index]->binary);
	free_void(data->l[index]->fd_ou);
	free_void(data->l[index]->pipes);
	free_void(data->l[index]->buf_pipes);
	free_void(data->l[index]->exit_codes);
	free(data->l[index]);
	data->l[index] = NULL;
}

void	free_line(t_pipex *data, int index)
{
	int	i;

	i = -1;
	close_everything(data, index);
	if (!data || !data->l || !data->l[index])
		return ;
	if (data->l[index]->ops)
		free_list_list(data->l[index]->ops);
	if (data->l[index]->cmnds)
		free_list_list(data->l[index]->cmnds);
	if (data->l[index]->paths)
		free_list(data->l[index]->paths);
	if (data->l[index]->input)
	{
		while (++i < data->l[index]->cmnd_count)
			free_str(&data->l[index]->input[i]);
		free(data->l[index]->input);
	}
	if (data->l[index]->red_cmnd)
		free_list_int(data->l[index]->red_cmnd, data->l[index]->cmnd_count);
	if (data->l[index]->pos)
		free_list_int(data->l[index]->pos, data->l[index]->cmnd_count);
	free_line_continue(data, index);
}

void	free_lines(t_pipex *data)
{
	int	i;

	i = -1;
	if (!data->l)
		return ;
	while (++i < data->line_count)
	{
		if (i == data->line_count - 1 && data->l[i] && data->l[i]->exit_codes
			&& data->l[i]->exit_codes[data->l[i]->cmnd_count - 1])
			data->last_exit_status = data->l[
				i]->exit_codes[data->l[i]->cmnd_count - 1];
		if (data->l[i])
			free_line(data, i);
		close_everything(data, i);
	}
	data->here_2 = 0;
	data->here_2_old = 0;
	free(data->l);
	if (data->pid)
	{
		free(data->pid);
		data->pid = NULL;
	}
	data->l = NULL;
	free_str(&data->line);
}

void	free_struct(t_pipex *data)
{
	if (data)
	{
		if (data->l)
			free_lines(data);
		if (data->cur_env)
			free_list(data->cur_env);
		if (data->export)
			free_list(data->export);
		if (data->buf_str)
			free_str(&data->buf_str);
		if (data->pid)
		{
			free(data->pid);
			data->pid = NULL;
		}
		free(data);
		data = NULL;
	}
}
