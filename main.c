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

char	*ft_strtrim_2(char *str, t_pipex *data)
{
	char	*new;
	int		i;

	i = 0;
	while (is_space(str[i]))
		i++;
	new = ft_strdup(data, str + i);
	free_str(&str);
	return (new);
}

void	init_env(t_pipex *data, char **env)
{
	int	i;

	i = 0;
	data->cur_env = ft_calloc(sizeof(char *), (count_env(env) + 1), data);
	i = -1;
	while (++i < count_env(env))
	{
		if (!ft_strncmp(env[i], "_=", 2))
			data->cur_env[i] = ft_strdup(data, "_=/usr/bin/env");
		else if (!ft_strncmp(env[i], "SHLVL=", 6))
			data->cur_env[i] = ft_strdup(data, "SHLVL=1");
		else
			data->cur_env[i] = ft_strdup(data, env[i]);
	}
}

void	init_export(t_pipex *data)
{
	int	i;
	int	count;

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
		if (!ft_strncmp(data->cur_env[i], "SHLVL=", 6))
			data->export[count++] = ft_strdup(data, "SHLVL=2");
		else if (ft_strncmp(data->cur_env[i], "_=", 2))
			data->export[count++]
				= malloc_cpy_export(data, data->cur_env[i], 0, -1);
	}
}

void	init_data(t_pipex *data, char **env)
{
	data->l = NULL;
	data->cur_env = NULL;
	data->export = NULL;
	data->cur_env = NULL;
	data->buf_array = NULL;
	data->line = NULL;
	data->pid = NULL;
	data->line_count = 0;
	data->here_2 = 0;
	data->last_exit_status = 0;
	data->fd_out = 0;
	data->fd_out_2 = 0;
	data->fd_in = -1;
	data->fd_in_2 = -1;
	data->buf_int = 0;
	data->count_elem = 0;
	init_env(data, env);
	init_export(data);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	*data;

	if (argc > 1)
		return (write(2, "Only 1 argc is accepted.\n", 26), 1);
	(void)argv;
	data = ft_calloc(sizeof(t_pipex), 1, NULL);
	init_data(data, env);
	g_signal = 0;
	while (1)
	{
		signal_change(NULL, 0);
		data->line = readline("minishell$ ");
		signal_change(data, 0);
		if (!data->line)
			return (printf("exit\n"), errno = data->last_exit_status,
				er_c(data), 0);
		if (data->line[0] != '\0')
		{
			data->line = ft_strtrim_2(data->line, data);
			parsing(data, -1);
		}
		else
			free_str(&data->line);
	}
	return (printf("\n"), free_struct(data), rl_clear_history(), 0);
}
