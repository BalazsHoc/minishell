/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export_6.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjuarez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:19:02 by cjuarez           #+#    #+#             */
/*   Updated: 2025/02/23 18:19:05 by cjuarez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	*get_old(t_pipex *data, int index_1, int index_2)
{
	int	i;

	i = -1;
	while (data->cur_env[++i])
	{
		if (!ft_strncmp(data->cur_env[i], "OLDPWD=", 7)
			&& printf("%s\n", data->cur_env[i] + 7))
			return (data->cur_env[i] + 7);
	}
	return (write(2, "bash: cd: OLDPWD not set\n", 26),
		exit_child(data, index_1, index_2, 1), NULL);
}

char	*get_path(t_pipex *data)
{
	int	i;

	i = -1;
	while (data->cur_env[++i])
	{
		if (!ft_strncmp(data->cur_env[i], "PATH=", 5))
			return (data->cur_env[i]);
	}
	return (0);
}
