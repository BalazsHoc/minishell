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

void	init_data(t_pipex *data, char **env)
{
	data->lines = NULL;
	data->cur_env = env;
	data->export = NULL;
	data->buf_array = NULL;
	data->input = NULL;
	data->line = NULL;
	data->cur_path = NULL;
	data->pid = NULL;
	data->line_count = 0;
	data->here = 0;
	data->here_2 = 0;
	data->last_exit_status = 0;
	data->fd_out = 0;
	data->buf_int = 0;
	data->count_elem = 0;
}

void	init_env(char ***env)
{
	// char *buf;
	char **new_env;
    int i;
	
	i = 0;
	new_env = malloc(sizeof(char *) * (count_env(*env) + 1));
	if (!new_env)
			return (perror("malloc failed!"), error_code(NULL));
	new_env[count_env(*env)] = NULL;
	i = -1;
	while (++i < count_env(*env))
	{
		new_env[i] = ft_strdup((*env)[i]);
		if (!new_env[i])
			return (perror("malloc failed!"), free_list(new_env), error_code(NULL));
		// new_env[i] = malloc(sizeof(char) * (ft_strlen((*env)[i]) + 1));
		// ft_memcpy(new_env[i], (*env)[i], ft_strlen((*env)[i]));
		// new_env[i][ft_strlen((*env)[i])] = 0;
		// env[i] = buf;
	}
	*env = new_env;
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
	data->export = ft_calloc(sizeof(char *), (count + 1));
	if (!data->export)
		return (perror("malloc failed"), error_code(data));
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
	init_env(&env);
	data = ft_calloc(sizeof(t_pipex), 1);
	if (!data)
		return (perror("malloc failed!"), free_list(env), errno);
	init_data(data, env);
	init_export(data);
	data->fd_out = 0;
	data->last_exit_status = 0;
	signal(SIGINT, signal_main);
	signal(SIGQUIT, signal_main);
	while (1)
	{
		data->line = readline("minishell$ ");
		if (!data->line)
		{
			printf("exit\n");
			error_code(data);
		} 
		if (data->line[0] != '\0')
		{
			data->line = ft_strtrim(data->line, " \n\t\v\f\r\b");
			// add_history(data->line);
			parsing(data);
		}
		else
			free_str(&data->line);
	}
	return (printf("\n"), free_struct(data), rl_clear_history(), 0);
}
