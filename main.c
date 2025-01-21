/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:13:20 by bhocsak           #+#    #+#             */
/*   Updated: 2024/10/08 10:13:25 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data(t_pipex *data)
{
	data->lines = NULL;
	data->cur_env = NULL;
	data->export = NULL;
	data->cur_env = NULL;
	data->buf_array = NULL;
	data->line = NULL;
	data->cur_path = NULL;
	data->pid = NULL;
	data->line_count = 0;
	data->here_2 = 0;
	data->last_exit_status = 0;
	data->fd_out = -1;
	data->fd_in = -1;
	data->buf_int = 0;
	data->count_elem = 0;
}

void	init_env(t_pipex *data, char **env)
{
    int i;
	
	i = 0;
	data->cur_env = ft_calloc(sizeof(char *), (count_env(env) + 1), data);
	i = -1;
	while (++i < count_env(env))
	{
		if (ft_strncmp(env[i], "_=", 2))
			data->cur_env[i] = ft_strdup(NULL, env[i]);
		else
			data->cur_env[i] = ft_strdup(NULL, "_=/usr/bin/env");
	}
}

void	init_export(t_pipex *data)
{
	// make sure _= can not be deleted
	int i;
	int count;

	i = -1;
	count = 0;
	while (data->cur_env[++i])
	{
		if (ft_strncmp(data->cur_env[i], "_=", 2))
			count++;
	}
	data->export = ft_calloc(sizeof(char *), (count + 1), data);
	data->export[count] = 0;
	i = -1;
	count = 0;
	while (data->cur_env[++i])
	{
		if (ft_strncmp(data->cur_env[i], "_=", 2))
			data->export[count++] = malloc_cpy_export(data, data->cur_env[i], 0, -1);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_pipex *data;

	// terminal_settings();
	if (argc != 1 && argv)
		return (printf("No argument is accepted\n"), 1);
	data = ft_calloc(sizeof(t_pipex), 1, NULL);
	init_data(data);
	init_env(data, env);
	init_export(data);
	data->fd_out = 0;
	data->last_exit_status = 0;
	g_signal = 0;
	while (1)
	{
		signal_change(0);
		g_signal = 0;
		data->line = readline("minishell$ ");
		if (!data->line)
		{
			printf("exit\n");
			error_code(data);
		} 
		if (data->line[0] != '\0')
		{
			data->line = ft_strtrim(data->line, " \n\t\v\f\r\b", data);
			// add_history(data->line);
			parsing(data);
		}
		else
			free_str(&data->line);
	}
	return (printf("\n"), free_struct(data), rl_clear_history(), 0);
}
