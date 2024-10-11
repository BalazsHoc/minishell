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

int	g_signal_number;

static void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		g_signal_number = 2;
		write(1, "\nminishell$ ", 12);
	}
	if (sig == SIGQUIT)
		return ;
}

int	main(int argc, char **argv, char **env)
{
	char	*line;

	(void)argc;
	(void)argv;
	(void)env;
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
	while (1)
	{
		write(1, "minishell$ ", 11);
		if (g_signal_number != 2)
		{
			line = get_next_line(0, false);
			g_signal_number = 0;
		}
		if (!line)
		{
			printf("\n");
			break ;
		}
		if (line[0] != '\n')
			parsing(line, env);
		free(line);
	}
	return (0);
}
