/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:42:41 by bhocsak           #+#    #+#             */
/*   Updated: 2024/10/11 16:42:43 by bhocsak          ###   ########.fr       */
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
