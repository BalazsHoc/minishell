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

static void	prompt(void)
{
	printf("minishell$ ");
	// while(1)
	// 	wait();
}

static void	opened_parent(void)
{
	pid_t	child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork failed");
		exit(EXIT_FAILURE);
	}
	else if (child_pid == 0)
	{
		prompt();
		exit(1);
	}
}

int	main(void)
{
	char	*line;

	while (1)
	{
		opened_parent();
		line = get_next_line(0, false);
		if (!line)
			break ;
		printf("%s", line);
		free(line);
	}
	return (0);
}
