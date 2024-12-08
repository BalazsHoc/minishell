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
		if (data->cmnds)
			free_list_list(data->cmnds);
		data->cmnds = NULL;
		if (data->ops)
			free_list_list(data->ops);
		data->ops = NULL;
		if (data->paths)
			free_list(data->paths);
		data->paths = NULL;
		if (data->input)
			free(data->input);
		data->input = NULL;
		if (data->line)
			free(data->line);
		data->line = NULL;
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
}

void	free_str(char *str)
{
	if (str)
		free(str);
}
