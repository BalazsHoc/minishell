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

static void handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	if (sig == SIGQUIT)
		return;
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

int	main(int argc, char **argv, char **env)
{
	t_pipex *data;

	if (argc != 1 && argv)
		return (printf("No argument is accepted\n"), 1);
	init_env(&env);
	data = malloc(sizeof(t_pipex) * 1);
	if (!data)
		return (perror("malloc failed!"), free_list(env), errno);
	data->cur_env = env;
	data->exit_code = 0;
	data->fd_out = 0;
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
	while (1)
	{
		data->line = readline("minishell$ ");
		if (!data->line)
			error_code(data);
		if (data->line[0] != '\0')
		{
			add_history(data->line);
			parsing(data);
		}
		else
			free_str(data->line);
	}
	return (printf("\n"), free_struct(data), free_list(data->cur_env), free(data), rl_clear_history(), 0);
}
