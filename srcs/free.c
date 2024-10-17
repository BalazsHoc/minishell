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
	int	i;
	int	j;

	i = -1;
	if (!data)
		return ;
	while (data->cmnds && data->cmnds[++i])
	{
		j = -1;
		while (data->cmnds[i][++j])
	free(data->cmnds[i][j]);
		free(data->cmnds[i]);
	}
	if (data->cmnds)
		free(data->cmnds);
	i = -1;
	if (data->paths)
	{
		while (data->paths && data->paths[++i])
		free(data->paths[i]);
	}
	if (data->paths)
		free(data->paths);
	if (data)
		free(data);
}

void	free_str(char **s)
{
	if (s && *s)
	{
		free(*s);
		*s = NULL;
	}
}

void	free_list(char **arr)
{
	int	i;

	i = 0;
	while (*(arr + i))
		i++;
	i--;
	while (i)
		free_str((arr + i--));
	free(*arr);
	free(arr);
}

void	free_list_list(char ***arr)
{
	int	i;

	i = 0;
	while (*(arr + i))
		i++;
	i--;
	while (i)
		free_list(*(arr + i--));
	free_list(*arr);
	free(arr);
}

void	free_a(char *str, char **list, char ***list_list)
{
	if (str)
		free_str(&str);
	if (list)
		free_list(list);
	if (list_list)
		free_list_list(list_list);
}
