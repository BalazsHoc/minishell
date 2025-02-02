#include "../minishell.h"

int	g_signal;

void signal_main(int sig)
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

void signal_mini_commands(int sig) // here_doc
{
     if (sig == SIGINT)
	 {
		g_signal = 2;
        ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	 }
}

void signal_exec_cmnd(int sig) // cat
{
    if (sig == SIGINT)
	{
		g_signal = 2;
		printf("\n");
		return ;
	}
	if (sig == SIGQUIT)
	{
		printf("Quit (core dumped)\n");
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
    if (flag == 1) // for our commands
	{
		signal(SIGINT, signal_mini_commands);
		signal(SIGQUIT, SIG_IGN);
	}
    if (flag == 2) // for prebuilt commands
	{
		signal(SIGINT, signal_exec_cmnd);
		signal(SIGQUIT, signal_exec_cmnd);
	}
}
