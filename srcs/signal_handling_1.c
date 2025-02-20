/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:30:33 by bhocsak           #+#    #+#             */
/*   Updated: 2025/02/02 14:30:36 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_signal;

void	signal_main(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 2;
		write(STDIN_FILENO, "\n", 2);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signal_mini_commands(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 2;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	signal_exec_cmnd(int sig)
{
	if (sig == SIGINT)
	{
		// g_signal = 2;
		return ;
	}
	if (sig == SIGQUIT)
		return ;
}

void	signal_exec_cmnd_2(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 2;
		printf("\n");
		return ;
	}
	if (sig == SIGQUIT)
	{
		write(2, "Quit (core dumped)\n", 20);
		g_signal = 3;
	}
}

void	signal_change(t_pipex *data, int flag)
{
	if (data && g_signal)
	{
		data->last_exit_status = g_signal + 128;
		g_signal = 0;
	}
	if (flag == 0)
	{
		signal(SIGINT, signal_main);
		signal(SIGQUIT, SIG_IGN);
	}
	if (flag == 1)
	{
		signal(SIGINT, signal_mini_commands);
		signal(SIGQUIT, SIG_IGN);
	}
	if (flag == 2)
	{
		signal(SIGINT, signal_exec_cmnd);
		signal(SIGQUIT, signal_exec_cmnd);
	}
	if (flag == 3)
	{
		signal(SIGINT, signal_exec_cmnd_2);
		signal(SIGQUIT, signal_exec_cmnd_2);
	}
}
