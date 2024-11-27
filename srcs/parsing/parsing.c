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
		// j = -1;
		// if (data->ops && data->ops[i])
		// {
		// 	while (data->ops[i][++j])
		// 		printf("OP:   %d:%d | %s\n", i, j, data->ops[i][j]);
		// }
		// printf("PATH: %s\n", data->paths[i]);
		// if (i > 10)
			// break;
	}
	// i = -1;
	// while (data->mini_env[++i])
	// 	printf("ENV[%d]: %s\n", i, data->mini_env[i]);
}

void	init_ops(t_pipex *data, int cmnd_count)
{
    int i;

    i = -1;
    data->ops = ft_calloc(sizeof(char **), (cmnd_count + 1));
    if (!data->ops)
        return (perror("malloc fail!\n"), error_code(data, NULL, 1, errno));
    data->ops[cmnd_count] = 0;
    while (data->cmnds[++i])
    {
		// printf("INIT_OPS: I : %d\n", i);
		if (count_ops(data, i) != -1)
		{
			data->ops[i] = malloc(sizeof(char *) * (count_ops(data, i) + 1));
			// printf("lol\n");
			if (!data->ops[i])
				return (perror("malloc fail!\n"), error_code(data, NULL, 1, errno));
			data->ops[i][count_ops(data, i)] = 0;
			fill_ops(data, i);
		}
    }
}

void	init_cmds(t_pipex *data, char *line, int count, char **env)
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
		data->cmnds[i] = fill_cmnds(data->cmnds[i], line, i, env);
		if (!data->cmnds[i])
			return (perror("malloc fail!\n"), error_code(data, line, 0, 0));
		if (!data->cmnds[i])
			return (error_code(data, line, 0, 0));
	}
}

void	init_paths(t_pipex *data, int count)
{
	int	i;

	i = -1;
	data->paths = malloc(sizeof(char *) * (count + 1));
	if (!data->paths)
		return (perror("malloc fail!\n"), error_code(data, NULL, 0, errno));
	data->paths[count] = NULL;
	while (++i < count)
	{
		// printf("WRONG111111\n");
		if (is_mini(data, i))
			data->paths[i] = ft_strdup("minicmnds");
		else if (data->ops[i] && data->ops[i][0])
		{
			// printf("WRONG22222\n");
			data->paths[i] = find_path(data->cur_env, data->ops[i][0]);
			// printf("WRONG333333\n");
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

char	*trimm_it(char *line)
{
	char *buf;

	buf = ft_strtrim(line, " \n\t\f\v\r");
	if (!buf)
	{
		free(line);
		exit(EXIT_FAILURE);
	}
	free(line);
	line = buf;
	return (line);
}

void	parsing(t_pipex *data, char *line, char **env)
{
	int		cmnd_count;

	(void)env;
	line = trimm_it(line);
	if (!syntax_check(line, -1, 0))
		return (perror("bash: syntax error near unexpected token `|'"), error_code(NULL, line, 0, errno));
	cmnd_count = count_cmnds(line);
	printf("COUNT CMND_LINES%d\n", cmnd_count);
	data->paths = NULL;
	data->cmnds = NULL;
	data->ops = NULL;
	data->input = NULL;
	while (check_open(line))
		line = trimm_it(join_this(join_this(line, "\n"), readline("> ")));
		// return (printf("bash: format error bla bla\n"), free_a(line, data));
	init_cmds(data, line, cmnd_count, env);
	print_that_shit(data);
	if (!check_reds(data))
		return (free_struct(data));
	return (set_cur_path(data), init_ops(data, cmnd_count), init_paths(data, cmnd_count),
		print_that_shit(data), start_exec(data, cmnd_count), free_struct(data));
}
//	return (rl_clear_history(), free_list(env), error_code(data, line, 1, 1));