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

void	free_struct(t_pipex *data)
{
	if (data)
	{
		free_list(data->paths);
		free_list_list(data->cmnds);
		free(data);
	}
}

void	free_list(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	i--;
	while (i >= 0)
	{
		if (arr[i])
			free(arr[i]);
		i--;
	}
	free(arr);
}

void	free_list_list(char ***arr)
{
	int	i;

	i = 0;
	while (*(arr + i))
		i++;
	i--;
	while (i >= 0)
		free_list(arr[i--]);
	free(arr);
}

void	free_a(char *line, t_pipex *data)
{
	if (data)
		free_struct(data);
	if (line)
		free(line);
	exit_child(1, NULL, NULL);
}
