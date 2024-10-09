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

int g_signal_number;

static void prompt(void)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork failed");
		exit(EXIT_FAILURE);
	}
	else if (child_pid == 0)
	{
		printf("minishell$ ");
		exit(1);
	}
}

static void handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		g_signal_number = 2;
		printf("\n");
		prompt();
	}
	if (sig == SIGQUIT)
		return ;
}

int main(int argc, char **argv, char **env)
{
	char	*line;

	(void)argc;
	(void)argv;
	(void)env;
	g_signal_number = 0;
	while (1)
	{
		signal(SIGINT, handle_signal);
		signal(SIGQUIT, handle_signal);
		prompt();
		line = get_next_line(0, false);
		if (!line)
		{
			printf("\n");
			break ;
		}
		if (line[0] == '\n')
			g_signal_number = 0;
		else
			printf("%s", line);
		// from_tokenization(line, env);
		free(line);
	}
	return (0);
}
