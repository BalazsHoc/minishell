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

void	make_prompt(t_pipex *data)
{
	free_str(&data->prompt);
	if (data->cwd)
		data->prompt = ft_strjoin(data->cwd, "$ ", data);
}

void	init_env(t_pipex *data, char **env, int i)
{
	data->cur_env = ft_calloc(sizeof(char *), (count_env(env) + 1), data);
	i = -1;
	while (++i < count_env(env))
	{
		if (!ft_strncmp(env[i], "_=", 2))
			data->cur_env[i] = ft_strdup(data, "_=/usr/bin/env");
		else if (!ft_strncmp(env[i], "SHLVL=", 6))
		{
			if (env[i] + 6)
			{
				data->buf_str = ft_itoa(ft_atoi(env[i] + 6) + 1, data);
				data->cur_env[i] = ft_strjoin("SHLVL=", data->buf_str, data);
				free_str(&data->buf_str);
			}
		}
		else
			data->cur_env[i] = ft_strdup(data, env[i]);
		if (!ft_strncmp(env[i], "PWD=", 4))
			data->cwd = ft_strdup(data, env[i] + 4);
		if (!ft_strncmp(env[i], "HOME=", 5))
			data->home = ft_strdup(data, env[i] + 5);
	}
}

void	init_export(t_pipex *d, int i, int count, char *buf)
{
	while (d->cur_env[i])
		i++;
	d->export = ft_calloc(sizeof(char *), (i - 1 + 1), d);
	count = 0;
	while (d->cur_env[++i])
	{
		if (!ft_strncmp(d->cur_env[i], "SHLVL=", 6))
		{
			d->buf_str = ft_itoa(ft_atoi(d->cur_env[i] + 6) + 1, d);
			buf = ft_strjoin("SHLVL=\"", d->buf_str, d);
			d->export[count++] = ft_strjoin(buf, "\"", d);
			free_str(&buf);
			free_str(&d->buf_str);
		}
		else if (ft_strncmp(d->cur_env[i], "_=", 2))
			d->export[count++]
				= malloc_cpy_export(d, d->cur_env[i], 0, -1);
	}
}

void	init_data(t_pipex *data, char **env)
{
	data->l = NULL;
	data->cur_env = NULL;
	data->prompt = NULL;
	data->export = NULL;
	data->cur_env = NULL;
	data->buf_array = NULL;
	data->line = NULL;
	data->pid = NULL;
	data->cwd = NULL;
	data->line_count = 0;
	data->here_2 = 0;
	data->last_exit_status = 0;
	data->fd_out = 0;
	data->fd_out_2 = 0;
	data->fd_in = -1;
	data->fd_in_2 = -1;
	data->buf_int = 0;
	data->count_elem = 0;
	data->home = NULL;
	data->main_pid = get_pid(data);
	init_env(data, env, 0);
	if (!data->cwd)
		get_pwd(data);
	init_export(data, 0, 0, NULL);
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
		make_prompt(data);
		signal_change(NULL, 0);
		data->line = readline(data->prompt);
		signal_change(data, 0);
		if (!data->line && printf("exit\n"))
			return (errno = data->last_exit_status, er_c(data), 0);
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
