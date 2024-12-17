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

void	free_struct(t_pipex *data)
{
	if (data)
	{
		free_list_list(data->cmnds);
		data->cmnds = NULL;
		free_list_list(data->ops);
		data->ops = NULL;
		free_list(data->paths);
		data->paths = NULL;
		free_str(data->line);
		data->line = NULL;
		if (data->exit_codes)
		{
			data->last_exit_status = data->exit_codes[data->cmnd_count - 1];
			free(data->exit_codes);
			data->exit_codes = NULL;
		}
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
			free(arr[i]);
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
	if (arr[0])
	{
		while (arr[i])
			free_list(arr[i++]);
	}
	free(arr);
	arr = NULL;
}

void	free_str(char *str)
{
	if (str)
		free(str);
	str = NULL;
}
