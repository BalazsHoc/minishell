/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:51:45 by bhocsak           #+#    #+#             */
/*   Updated: 2025/02/02 14:51:46 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_mini(t_pipex *data, int index_1, int index_2)
{
	if (data->l[index_1]->ops[index_2] && data->l[index_1]->ops[index_2][0]
		&& ((!ft_strncmp(data->l[index_1]->ops[index_2][0], "env", 4)
			&& get_path(data)) || !ft_strncmp(data->l[
					index_1]->ops[index_2][0], "export", 7)
		|| !ft_strncmp(data->l[index_1]->ops[index_2][0], "/bin/env", 9)
		|| !ft_strncmp(data->l[index_1]->ops[index_2][0], "/usr/bin/env", 13)
		|| !ft_strncmp(data->l[index_1]->ops[index_2][0], "cd", 3)
			|| !ft_strncmp(data->l[index_1]->ops[index_2][0], "unset", 6)
		|| !ft_strncmp(data->l[index_1]->ops[index_2][0], "pwd", 4)
			|| !ft_strncmp(data->l[index_1]->ops[index_2][0], "exit", 5)
		|| !ft_strncmp(data->l[index_1]->ops[index_2][0], "/usr/bin/pwd", 13)
	|| !ft_strncmp(data->l[index_1]->ops[index_2][0], "/bin/pwd", 9)
	|| (!ft_strncmp(data->l[index_1]->ops[index_2][0], "ls", 3)
	&& !is_valid_cwd(data))))
		return (1);
	return (0);
}

int	is_mini_2(t_pipex *data, int index_1, int index_2)
{
	if (data->l[index_1]->ops[index_2] && data->l[index_1]->ops[index_2][0]
		&& (!ft_strncmp(data->l[index_1]->ops[index_2][0], "/bin/env/", 10)
		|| !ft_strncmp(data->l[index_1]->ops[index_2][0], "/usr/bin/env/", 14)
		|| !ft_strncmp(data->l[index_1]->ops[index_2][0], "/usr/bin/pwd/", 14)
		|| !ft_strncmp(data->l[index_1]->ops[index_2][0], "/bin/pwd/", 10)))
		return (1);
	return (0);
}

int	slash_in_cmnd(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '/')
			return (1);
	}
	return (0);
}

char	*find_path_2(t_pipex *data, char **arr, char *cmnd)
{
	int		i;
	char	*full_path;
	char	*new;

	i = -1;
	new = NULL;
	if (!slash_in_cmnd(cmnd))
		new = ft_strjoin("/", cmnd, data);
	while (arr[++i])
	{
		if (!slash_in_cmnd(cmnd) && ft_strncmp(arr[i], cmnd, ft_strlen(cmnd)))
			full_path = ft_strjoin(arr[i], new, data);
		else
			full_path = ft_strdup(data, cmnd);
		if (!access(full_path, X_OK))
			return (free_list((void *)arr), free_str(&new), full_path);
		free_str(&full_path);
	}
	if (ft_strncmp(get_pwd(data) + 4, arr[0], ft_strlen(get_pwd(data) + 4)))
		return (free_str(&new), free_str(&arr[0]),
			arr[0] = ft_strdup(data, get_pwd(data) + 4),
			find_path_2(data, arr, cmnd));
	return (free_list((void *)arr), free_str(&new), NULL);
}

char	*find_path(t_pipex *data, char *cmnd)
{
	int		i;
	char	*path;
	char	**arr;

	i = 0;
	path = NULL;
	if (!cmnd || (!one_of_those_3(cmnd) && slash_in_cmnd(cmnd)))
		return (NULL);
	while (data->cur_env && data->cur_env[i] && i < 100)
	{
		if (!ft_strncmp("PATH=", (const char *)data->cur_env[i], 5))
		{
			path = data->cur_env[i] + 5;
			break ;
		}
		i++;
	}
	if ((!path || !*path))
		path = cmnd;
	arr = ft_split(path, ':');
	if (!arr || !*arr)
		return (NULL);
	return (find_path_2(data, arr, cmnd));
}
