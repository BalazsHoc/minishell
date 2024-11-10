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
		while (data->cmnds[i][++j])
			printf("ELEM: %d:%d | %s\n", i, j, data->cmnds[i][j]);
		j = -1;
		if (data->ops[i])
		while (data->ops[i][++j])
			printf("OP:   %d:%d | %s\n", i, j, data->ops[i][j]);
		printf("PATH: %s\n", data->paths[i]);
	}
	// i = -1;
	// while (data->mini_env[++i])
	// 	printf("ENV[%d]: %s\n", i, data->mini_env[i]);
}

void	init_ops(t_pipex *data, int cmnd_count)
{
    int i;

    i = -1;
    data->ops = malloc(sizeof(char **) * (cmnd_count + 1));
    if (!data->ops)
        return (perror("malloc fail!\n"), error_code(data, NULL, 1, errno));
    data->ops[cmnd_count] = 0;
    while (data->cmnds[++i])
    {
        data->ops[i] = malloc(sizeof(char *) * (count_ops(data, i) + 1));
        if (!data->ops[i])
            return (perror("malloc fail!\n"), error_code(data, NULL, 1, errno));
        data->ops[i][count_ops(data, i)] = 0;
        fill_ops(data, i);
    }
}

void	init_cmds(t_pipex *data, char *line, int count)
{
	int	i;

	i = -1;
	data->cmnds = malloc(sizeof(char **) * (count + 1));
	if (!data->cmnds)
		return (perror("malloc fail!\n"), error_code(data, line, 0, 0));
	data->cmnds[count] = NULL;
	while (++i < count)
	{
		data->cmnds[i] = malloc(sizeof(char *) * (count_elem(line, i, 0) + 1));
		if (!data->cmnds[i])
			return (perror("malloc fail!\n"), error_code(data, line, 0, 0));
		data->cmnds[i][count_elem(line, i, 0)] = NULL;
		data->cmnds[i] = fill_cmnds(data->cmnds[i], line, i, -i);
		if (!data->cmnds[i])
			return (perror("malloc fail!\n"), error_code(data, line, 0, 0));
		if (!data->cmnds[i])
			return (error_code(data, line, 0, 0));
	}
	free(line);
}

void	init_paths(t_pipex *data, int count, char **env)
{
	int	i;

	i = -1;
	data->paths = malloc(sizeof(char *) * (count + 1));
	if (!data->paths)
		return (perror("malloc fail!\n"), error_code(data, NULL, 0, errno));
	data->paths[count] = NULL;
	while (++i < count)
	{
		if (data->ops[i][0] && ft_strncmp(data->ops[i][0], "cd", 3)
			&& ft_strncmp(data->ops[i][0], "env", 4) && ft_strncmp(data->ops[i][0], "export", 7))
		{
			data->paths[i] = find_path(env, data->ops[i][0]);
			if (!data->paths[i])
			{
				data->paths[i] = ft_strdup("pathnfound");
				printf("zsh: command not found %s\n", data->ops[i][0]);
				exit_child(127, NULL, data);
			}
		}
		else
			data->paths[i] = ft_strdup("pathnfound");
		if (!data->paths[i])
			return (perror("malloc fail!\n"), error_code(data, NULL, 0, errno));
	}
}

// void init_env(t_pipex *data, char **env)
// {
// 	int i;
	
// 	i = -1;
// 	data->mini_env = ft_calloc(sizeof(char *), (count_env(env) + 1));
// 	if (!data->mini_env)
// 		return (printf("malloc fail!\n"), error_code(data, NULL, 1, 0));
// 	data->mini_env[count_env(env)] = NULL;
// 	while (++i < count_env(env))
// 	{
// 		data->mini_env[i] = malloc(sizeof(char) * (ft_strlen(env[i]) + 1));
// 		if (!data->mini_env[i])
// 			return (printf("malloc fail!\n"), error_code(data, NULL, 1, 0));
// 		ft_memcpy(data->mini_env[i], env[i], ft_strlen(env[i]));
// 		data->mini_env[i][ft_strlen(env[i])] = 0;
// 	}
// }

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
	if (!syntax_check(line, -1, 0))
		return (perror("bash: syntax error near unexpected token `|'"), error_code(NULL, line, 0, errno));
	data = malloc(sizeof(t_pipex) * 1);
	if (!data)
		return (perror("malloc fail!\n"), free_list(env), error_code(NULL, line, 1, errno));
	cmnd_count = count_cmnds(line);
	printf("COUNT CMND_LINES%d\n", cmnd_count);
	data->paths = NULL;
	data->cmnds = NULL;
	data->ops = NULL;
	data->input = NULL;
	while (check_open(line))
		line = join_this(join_this(line, "\n"), get_next_line(0, 0));
	init_cmds(data, line, cmnd_count);
	data->cur_env = env;
	if (!check_reds(data))
		return (free_struct(data));
	return (init_cur_path(data), init_ops(data, cmnd_count), init_paths(data, cmnd_count, env),
		print_that_shit(data), start_exec(data, env), free_struct(data));
}
