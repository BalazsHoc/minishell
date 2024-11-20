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
			return (printf("malloc fail!\n"), free_list(*env), error_code(NULL, NULL, 1, 1));
	new_env[count_env(*env)] = NULL;
	i = -1;
	while (++i < count_env(*env))
	{
		new_env[i] = malloc(sizeof(char) * (ft_strlen((*env)[i]) + 1));
		if (!new_env[i])
			return (printf("malloc fail!\n"), free_list(new_env), error_code(NULL, NULL, 1, 1));
		ft_memcpy(new_env[i], (*env)[i], ft_strlen((*env)[i]));
		new_env[i][ft_strlen((*env)[i])] = 0;
		// env[i] = buf;
	}
	*env = new_env;
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_pipex *data;

	if (argc != 1 && argv)
		return (printf("No argument is accepted\n"), 1);
	init_env(&env);
	data = malloc(sizeof(t_pipex) * 1);
	if (!data)
		return (printf("malloc fail!"), free_list(env), 0);
	data->cur_env = env;
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (*line != '\0')
		{
			add_history(line);
			parsing(data, line, env);
		}
		else
			free(line);
	}
	return (printf("\n"), free(data), free_list(env), rl_clear_history(), 0);
}
