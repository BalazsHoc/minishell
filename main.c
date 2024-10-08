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
	{
		g_signal_number = 3;
		printf("fasz\n");
	}
	if (sig == SIGTERM)
	{
		g_signal_number = 15;
		printf("krva\n");
	}
}

int main(int argc, char **argv, char **env)
{
	char *line;

	g_signal_number = 0;
	(void)argc;
	(void)argv;
	(void)env;
	while (1)
	{
		signal(SIGINT, handle_signal);
		signal(SIGTERM, handle_signal);
		signal(SIGQUIT, handle_signal);
		if (g_signal_number == 4)
			exit(0);
		prompt();
		line = get_next_line(0, false);
		if (!line)
		{
			get_next_line(0, true);
			break;
		}
		// from_tokenization(line);
		printf("%s", line);
		free(line);
	}
	return (0);
}
