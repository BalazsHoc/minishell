/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 12:59:02 by bhocsak           #+#    #+#             */
/*   Updated: 2024/10/17 12:59:04 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	free_this(char **s)
{
	if (*s)
	{
		free(*s);
		*s = NULL;
	}
	return (1);
}

void	free_list_ptr(char ***list)
{
	int	i;

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
	int	i;

	i = -1;
	while (++i < cmnd_count)
	{
		if (arr[i])
			free(arr[i]);
	}
	free(arr);
	arr = NULL;
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
