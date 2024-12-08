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
			printf("ELEM: %d:%d | $%s$\n", i, j, data->cmnds[i][j]);
		j = -1;
		if (data->ops && data->ops[i])
		{
			while (data->ops[i][++j])
				printf("OP:   %d:%d | %s\n", i, j, data->ops[i][j]);
		}
		printf("PATH: %s\n", data->paths[i]);
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
	int j;

    i = -1;
    data->ops = ft_calloc(sizeof(char **), (cmnd_count + 1));
    if (!data->ops)
        return (perror("malloc fail!\n"), error_code(data));
    data->ops[cmnd_count] = 0;
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
			fill_ops(data, i);
		}
    }
}

void	init_cmds(t_pipex *data, int count, char **env)
{
	int	i;

	i = -1;
	data->cmnds = malloc(sizeof(char **) * (count + 1));
	if (!data->cmnds)
		return (perror("malloc fail!\n"), error_code(data));
	data->cmnds[count] = NULL;
	while (++i < count)
	{
		data->cmnds[i] = malloc(sizeof(char *) * (count_elem(data->line, i, 0) + 1));
		if (!data->cmnds[i])
			return (perror("malloc fail!\n"), error_code(data));
		data->cmnds[i][count_elem(data->line, i, 0)] = NULL;
		data->cmnds[i] = fill_cmnds(data->cmnds[i], data, i, env);
		if (!data->cmnds[i])
			return (error_code(data));
	}
}

void	init_paths(t_pipex *data, int count, int i)
{
	data->paths = malloc(sizeof(char *) * (count + 1));
	if (!data->paths)
		return (perror("malloc fail!\n"), error_code(data));
	data->paths[count] = NULL;
	while (++i < count)
	{
		if (is_mini(data, i))
			data->paths[i] = ft_strdup("minicmnds");
		else if (echo_exit_code(data->cmnds[i]))
			data->paths[i] = ft_strdup("/bin/bash");
		else if (data->ops[i] && data->ops[i][0])
		{
			data->paths[i] = find_path(data, data->ops[i][0]);
			if (!data->paths[i] && printf("bash: command not found %s\n", data->ops[i][0]))
			{
				data->paths[i] = ft_strdup("pathnfound");
				errno = 127;
				exit_child(data);
			}
		}
		else
			data->paths[i] = ft_strdup("pathnfound");
		if (!data->paths[i])
			return (perror("malloc fail!\n"), error_code(data));
	}
}

char	*trimm_it(char *line, t_pipex *data)
{
	char *buf;

	buf = ft_strtrim(line, " \n\t\f\v\r");
	if (!buf)
		error_code(data);
	free_str(line);
	line = NULL;
	return (buf);
}

void	parsing(t_pipex *data)
{
	int		cmnd_count;

	data->line = trimm_it(data->line, data);
	if (!syntax_check(data->line, -1, 0))
		return (perror("bash: syntax error near unexpected token `|'"), error_code(data));
	cmnd_count = count_cmnds(data->line);
	// printf("COUNT CMND_LINES%d\n", cmnd_count);
	data->paths = NULL;
	data->cmnds = NULL;
	data->ops = NULL;
	data->input = NULL;
	while (check_open(data->line))
		return (printf("bash: syntax error: open quotes \n"), errno = 1, free_struct(data));
		// data->line = trimm_it(join_this(join_this(data->line, "\n"), readline("> ")), data);
	init_cmds(data, cmnd_count, data->cur_env);
	// print_that_shit(data);
	if (!check_reds(data))
		return (free_struct(data));
	return (signal_change(data, 1), set_cur_path(data), init_ops(data, cmnd_count), init_paths(data, cmnd_count, -1),
		start_exec(data, cmnd_count), free_struct(data), signal_back(data));
}
