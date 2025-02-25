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

char	*malloc_cpy_export_continue(char *new, char *str, int count)
{
	int	i;

	i = -1;
	while (str[++i] && (i == 0 || (str[i - 1] != '=')))
		new[i] = str[i];
	new[i--] = 34;
	count = 0;
	while (str[++i])
	{
		if (str[i] == 34)
			new[i + 1 + count++] = 92;
		new[i + 1 + count] = str[i];
	}
	new[i + 1 + count] = 34;
	return (new);
}

char	*malloc_cpy_export(t_pipex *data, char *str, int track, int i)
{
	char	*new;
	int		count;

	new = NULL;
	count = 0;
	while (str[++i])
	{
		count++;
		if (!track && str[i] == '=')
			track = 1;
		if (str[i] == 34)
			count++;
	}
	if (!track)
		return (ft_strdup(data, str));
	else if (track == 1)
		new = ft_calloc(sizeof(char), (count + 2 + 1), data);
	return (malloc_cpy_export_continue(new, str, count));
}

int	is_shlvl(char *str)
{
	if (!ft_strncmp(str, "SHLVL", 5)
		&& (ft_strlen(str) == 5 || !ft_strncmp(str, "SHLVL=", 6)))
		return (1);
	return (0);
}

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
