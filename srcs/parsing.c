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

char	**fill_cmnds(char **arr, char *line, int i, int k)
{
	int	j;
	int	index;

	j = -1;
	index = -1;
	while (line[++j] && i >= 0)
	{
		if (k == 0 && !is_space(line[j])
			&& (line[j] != '|' || is_or(line + j)))
		{
			arr[++index] = malloc(sizeof(char) * (count_chars(line + j) + 1)); //Problem if it fails  // you mean count_chars() or malloc() ??
			if (!arr[index])
				return (perror("malloc fail\n"), NULL);
			ft_memcpy(arr[index], line + j, (size_t)count_chars(line + j));
			// if (!arr[index])
			// 	return (perror("malloc fail\n"), NULL);
			// what about this? 
			arr[index][count_chars(line + j)] = '\0'; 
			j += count_chars(line + j);
		}
		if (line[j] == '|' && k++ != INT_MIN)
			i--;
		if (!line[j])
			break;
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
			printf("ELEM: %d: %s\n", i,data->cmnds[i][j++]);
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
		return (perror("malloc fail!\n"), error_code(data, line, 0));
	data->cmnds[count] = NULL;
	while (i < count)
	{
		data->cmnds[i] = malloc(sizeof(char *) * (count_elem(line, i) + 1));
		if (!data->cmnds[i])
			return (perror("malloc fail!\n"), error_code(data, line, 0));

		data->cmnds[i] = fill_cmnds(data->cmnds[i], line, i, -i);
		if (!data->cmnds[i])
			return (perror("malloc fail!\n"), error_code(data, line, 0));
		data->cmnds[i][count_elem(line, i)] = NULL;
		if (!data->cmnds[i])
			return (error_code(data, line, 0));
		i++;
	}
}

void	init_paths(t_pipex *data, char *line, int count, char **env)
{
	int	i;

	i = -1;
	data->paths = malloc(sizeof(char *) * (count + 1));
	if (!data->paths)
		return (perror("malloc fail!\n"), error_code(data, line, 0));
	data->paths[count] = NULL;
	while (++i < count)
	{
		if (cmnds_start(data->cmnds[i]) == -1)
			data->paths[i] = ft_strdup("pathnfound");
		else
		{
			data->paths[i] = find_path(env, data->cmnds[i][cmnds_start(data->cmnds[i])]);
			if (!data->paths[i])
			{
				data->paths[i] = ft_strdup("pathnfound");
				printf("zsh: command not found %s\n", data->cmnds[i][cmnds_start(data->cmnds[i])]);
				exit_child(1, line, data);
			}
		}
		if (!data->paths[i])
			return (perror("malloc fail!\n"), error_code(data, line, 0));
	}
}

void	parsing(char *line, char **env)
{
	t_pipex	*data;
	char	*trimmed;
	int		cmnd_count;

	trimmed = ft_strtrim(line, " \n\t\f\v\r");
	if (!trimmed)
	{
		free(line);
		exit(EXIT_FAILURE);
	}
	free(line);
	line = trimmed;
	if (!syntax_check(line, -1) || (line[0] == '|' && line[1] != '|'))
		return (perror("bash: syntax error near unexpected token `|'"), error_code(NULL, line, 0));
	data = malloc(sizeof(t_pipex) * 1);
	if (!data)
		return (perror("malloc fail!\n"), error_code(NULL, line, 1));
	cmnd_count = count_cmnds(line);
	data->paths = NULL;
	data->cmnds = NULL;
	init_cmds(data, line, cmnd_count);
	init_paths(data, line, cmnd_count, env);
	print_that_shit(data);
	// parsing_2(line, data, env);
	free_a(line, data);
}
