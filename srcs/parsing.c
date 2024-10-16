/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:41:53 by bhocsak           #+#    #+#             */
/*   Updated: 2024/10/11 15:41:55 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**fill_cmnds(char **arr, char *line, int i)
{
	int	j;
	int	k;
	int	index;

	j = -1;
	k = -i;
	index = -1;
	while (line[++j] && i >= 0)
	{
		if (k == 0 && !is_space(line[j]) && line[j] != '|')
		{
			arr[++index] = malloc(sizeof(char) * (count_chars(line + j) + 1));
			if (!arr[index])
				return (perror("malloc fail\n"), NULL);
			printf("COUNT CHAR: %d\n", count_chars(line + j));
			ft_memcpy(arr[index], line + j, (size_t)count_chars(line + j));
			arr[index][count_chars(line + j)] = '\0';
			j += count_chars(line + j);
		}
		if (line[j] == '|')
		{
			i--;
			k++;
		}
	}
	return (arr);
}

// TAKE THAT OUT
void	print_that_shit(t_pipex *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->cmnds[i])
	{
		j = 0;
		while (data->cmnds[i][j])
			printf("elem: %s\n", data->cmnds[i][j++]);
		printf("PATH: %s\n", data->paths[i]);
		i++;
	}
}

void	init_cmds(t_pipex *data, char *line, int count)
{
	int	i;

	i = 0;
	data->cmnds = malloc(sizeof(char **) * (count + 1));
	if (!data->cmnds)
		return (perror("malloc fail!\n"), error_code(data, line));
	data->cmnds[count] = NULL;
	while (i < count)
	{
		data->cmnds[i] = malloc(sizeof(char *) * (count_elem(line, i) + 1));
		if (!data->cmnds[i])
			return (perror("malloc fail!\n"), error_code(data, line));
		data->cmnds[i][count_elem(line, i)] = NULL;
		data->cmnds[i] = fill_cmnds(data->cmnds[i], line, i);
		if (!data->cmnds[i])
			return (error_code(data, line));
		i++;
	}
}

void	init_paths(t_pipex *data, char *line, int count, char **env)
{
	int	i;
	// char *path;

	i = -1;
	data->paths = malloc(sizeof(char *) * (count + 1));
	if (!data->paths)
		return (perror("malloc fail!\n"), error_code(data, line));
	data->paths[count] = NULL;
	while (++i < count)
	{
		data->paths[i] = find_path(env, data->cmnds[i][0]);
		if (!data->paths[i])
		{
			printf("zsh: command not found %s\n", data->cmnds[i][0]);
			exit_child(1, line, data);
			data->paths[i] = ft_strdup("pathnfound");
		}
		if (!data->paths[i])
			return (perror("malloc fail!\n"), error_code(data, line));
	}
}

void	parsing(char *line, char **env)
{
	t_pipex	*data;
	int		cmnd_count;

	data = malloc(sizeof(t_pipex) * 1);
	if (!data)
		return (perror("malloc fail!\n"), error_code(NULL, line));
	cmnd_count = count_cmnds(line);
	data->paths = NULL;
	data->cmnds = NULL;
	init_cmds(data, line, cmnd_count);
	init_paths(data, line, cmnd_count, env);
	print_that_shit(data);
	if (env)
		(void)env;
	free_struct(data);
}
