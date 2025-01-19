/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 12:59:02 by bhocsak           #+#    #+#             */
/*   Updated: 2024/10/17 12:59:04 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//only the if statements has been changed in free* functions

void	free_list_ptr(char ***list)
{
	int i;

	i = 0;
	while (list[i])
	{
		free(list[i]);
		i++;
	}
	free(list);
}

void	free_list_int(int **arr, int cmnd_count)
{
	int i;

	i = -1;
	while (++i < cmnd_count)
	{
		if (arr[i])
			free(arr[i]);
	}
	free(arr);
	arr = NULL;
}

// void	free_list_list_int(int **arr, int cmnd_count)
// {
// 	int i;
// 	int j;

// 	i = -1;
// 	while (++i < cmnd_count)
// 	{
// 		if (arr[i])
// 		{
// 			j = -1;
// 			while (arr[i][++j])
// 			{
// 				if (arr[i][j])
// 				{
// 					free(arr[i][j]);
// 					arr[i][j] = NULL;
// 				}
// 			}
// 			free(arr[i]);
// 			arr[i] = NULL;
// 		}
// 	}
// 	free(arr);
// 	arr = NULL;
// }

void	free_line(t_pipex *data, int index)
{
	close_everything(data, index);
	if (!data || !data->lines || !data->lines[index])
		return ;
	if (data->lines[index]->ops)
		free_list_list(data->lines[index]->ops);
	if (data->lines[index]->cmnds)
		free_list_list(data->lines[index]->cmnds);
	if (data->lines[index]->paths)
		free_list(data->lines[index]->paths);
	if (data->lines[index]->input)
		free_list(data->lines[index]->input);

	// FREE LIST LIST INT
	if (data->lines[index]->red_cmnd)
		free_list_int(data->lines[index]->red_cmnd, data->lines[index]->cmnd_count);
	if (data->lines[index]->pos_in_line)
		free_list_int(data->lines[index]->pos_in_line, data->lines[index]->cmnd_count);
	
	// FREE LIST INT
	if (data->lines[index]->fd_infiles)
	{
		free(data->lines[index]->fd_infiles);
		data->lines[index]->fd_infiles= NULL;
	}
	if (data->lines[index]->fd_outfiles)
	{
		free(data->lines[index]->fd_outfiles);
		data->lines[index]->fd_outfiles = NULL;
	}
	if (data->lines[index]->pipes)
	{
		free(data->lines[index]->pipes);
		data->lines[index]->pipes = NULL;
	}
	if (data->lines[index]->buf_pipes)
	{
		free(data->lines[index]->buf_pipes);
		data->lines[index]->buf_pipes = NULL;
	}
	if (data->lines[index]->exit_codes)
		free(data->lines[index]->exit_codes);
	free(data->lines[index]);
	data->lines[index] = NULL;
}

void 	free_lines(t_pipex *data)
{
	int i;

	i = -1;
	if (!data->lines)
		return ;
	while (++i < data->line_count)
	{
		if (i == data->line_count - 1 &&  data->lines[i]->exit_codes 
			&& data->lines[i]->exit_codes[data->lines[i]->cmnd_count - 1])
			data->last_exit_status = data->lines[i]->exit_codes[data->lines[i]->cmnd_count - 1];
		if (data->lines[i])
			free_line(data, i);
	}
	data->here_2 = 0;
	data->here_2_old = 0;
	free(data->lines);
	if (data->pid)
	{
		free(data->pid);
		data->pid = NULL;
	}
	data->lines = NULL;
	free_str(&data->line);
}

void	free_struct(t_pipex *data)
{
	if (data)
	{
		if (data->lines)
			free_lines(data);
		if (data->cur_env)
			free_list(data->cur_env);
		if (data->export)
			free_list(data->export);
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

void	free_list(char **arr)
{
	int	i;

	i = -1;
	if (!arr)
		return ;
	if (arr[0])
	{
		while (arr[++i])
			free_str(&arr[i]);
	}
	free(arr);
	arr = NULL;
}

void	free_list_list(char ***arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	if (arr[i])
	{
		while (arr[i])
			free_list(arr[i++]);
	}
	free(arr);
	arr = NULL;
}

void	free_str(char **str)
{
	if (*str)
		free(*str);
	*str = NULL;
}