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

#include "../../minishell.h"

// TAKE THAT OUT
void	print_that_shit(t_pipex *data)
{
	int	i;
	int	j;

	i = -1;
	while (data->cmnds[++i])
	{
		j = -1;
		printf("data->cmnds[%d]\n", i);
		while (data->cmnds[i][++j])
		{
			if (data->cmnds[i][j])
				printf("ELEM: %d:%d | $%s$\n", i, j, data->cmnds[i][j]);
		}
		// j = -1;
		// if (data->ops && data->ops[i])
		// {
		// 	while (data->ops[i][++j])
		// 		printf("OP:   %d:%d | %s\n", i, j, data->ops[i][j]);
		// }
		// printf("PATH: %s\n", data->paths[i]);
	}
	// i = -1;
	// while (data->mini_env[++i])
	// 	printf("ENV[%d]: %s\n", i, data->mini_env[i]);
}

void	init_exit_codes(t_pipex *data, int cmnd_count)
{
	data->exit_codes = malloc(sizeof(int) * (cmnd_count + 1));
	if (!data->exit_codes)
	{
		perror("malloc failed!\n");
		error_code(data);
	}
	while (cmnd_count >= 0)
	{
		data->exit_codes[cmnd_count] = 0;
		cmnd_count--;
	}
}

void	init_ops(t_pipex *data)
{
    int i;
	int j;

    i = -1;
    data->ops = ft_calloc(sizeof(char **), (data->cmnd_count + 1));
    if (!data->ops)
        return (perror("malloc fail!\n"), error_code(data));
    data->ops[data->cmnd_count] = 0;
    while (data->cmnds[++i])
    {
		j = count_ops(data, i);
		if (j != -1)
		{
			// if (echo_exit_code(data->cmnds[i]))
			// 	j = 3;
			data->ops[i] = malloc(sizeof(char *) * (j + 1));
			if (!data->ops[i])
				return (perror("malloc fail!\n"), error_code(data));
			data->ops[i][j] = 0;
			// if (echo_exit_code(data->cmnds[i]))
			// 	fill_echo_exit(data, i);
			// else
			if (j > 0)
				fill_ops(data, i);
		}
    }
}

void	init_cmds(t_pipex *data, char **env)
{
	int	i;

	i = -1;
	data->cmnds = malloc(sizeof(char **) * (data->cmnd_count + 1));
	if (!data->cmnds)
		return (perror("malloc fail!\n"), error_code(data));
	data->cmnds[data->cmnd_count] = NULL;
	while (++i < data->cmnd_count)
	{
		data->cmnds[i] = malloc(sizeof(char *) * (count_elem(data, i, 0) + 1));
		if (!data->cmnds[i])
			return (perror("malloc fail!\n"), error_code(data));
		data->cmnds[i][count_elem(data, i, 0)] = NULL;
		data->cmnds[i] = fill_cmnds(data->cmnds[i], data, i, env);
		if (!data->cmnds[i])
			return (error_code(data));
	}
}

void	init_paths(t_pipex *data, int i)
{
	data->paths = malloc(sizeof(char *) * (data->cmnd_count + 1));
	if (!data->paths)
		return (perror("malloc fail!\n"), error_code(data));
	data->paths[data->cmnd_count] = NULL;
	while (++i < data->cmnd_count)
	{
		if (is_mini(data, i))
			data->paths[i] = ft_strdup("minicmnds");
		else if (!ft_strncmp(data->ops[i][0], "echo", 5))
			data->paths[i] = ft_strdup("/usr/bin/echo");
		else if (data->ops[i] && data->ops[i][0])
		{
			data->paths[i] = find_path(data, data->ops[i][0]);
			if (!data->paths[i])
				data->paths[i] = ft_strdup("pathnfound");
		}
		else
			data->paths[i] = ft_strdup("pathnfound");
		if (!data->paths[i])
			return (perror("malloc fail!\n"), error_code(data));
	}
}

void	parsing(t_pipex *data)
{
	data->cmnd_count = count_cmnds(data->line);
	init_exit_codes(data, data->cmnd_count);
	// printf("COUNT CMND_LINES%d\n", cmnd_count);
	if (!syntax_check(data->line, -1, 0))
		return (perror("bash: syntax error near unexpected token `|'"), exit_child(data, 0, 1));
	data->paths = NULL;
	data->cmnds = NULL;
	data->ops = NULL;
	while (check_open(data->line))
		return (printf("bash: syntax error: open quotes \n"), exit_child(data, 0, 1), free_struct(data));
	init_cmds(data, data->cur_env);
	// print_that_shit(data);
	if (!check_reds(data))
		return (free_struct(data));
	return (signal_change(1), set_cur_path(data), init_ops(data), check_folder(data), init_paths(data, -1),
		start_exec(data), signal_back(data), free_struct(data));
}
