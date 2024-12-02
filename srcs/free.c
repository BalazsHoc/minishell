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

void free_env(char **env)
{
	int i;

	i = -1;
	while (env[++i])
		free_str(env[i]);
}

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
		if (data->paths)
			free_list(data->paths);
		if (data->cmnds)
			free_list_list(data->cmnds);
		if (data->ops)
			free_list_list(data->ops);
		if (data->input)
			free_str(data->input);
		// free(data);
	}
}

void	free_list(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
			free(arr[i]);
	free(arr);
}

void	free_list_list(char ***arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free_list(arr[i++]);
}

void	free_str(char *str)
{
	if (str)
		free(str);
}

void	free_a(char *line, t_pipex *data)
{
	if (data)
		free_struct(data);
	if (line)
		free(line);
	exit_child(1, NULL, NULL);
}
