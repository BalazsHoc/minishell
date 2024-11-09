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

static void	handle_signal(int sig)
{
	if (sig == SIGINT)
		write(1, "\nminishell$ ", 12);
	if (sig == SIGQUIT)
		return ;
}

int	main(int argc, char **argv, char **env)
{
	char	*line;

	(void)argv;
	env = new_env(env);
	if (!env)
		return (printf("malloc fail!\n"), 0);
	if (argc != 1)
		return (printf("No argument is accepted\n"), 1);
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
	while (1)
	{
		write(1, "minishell$ ", 11);
		line = get_next_line(0, false);
		if (!line)
		{
			printf("\n");
			return (free_list(env), 0); // env remade so musrt be freed at the end (EOF) or error
		}
		if (line[0] != '\n')
			parsing(line, env);
		else
			free(line);
	}
	return (0);
}
