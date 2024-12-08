#include "../minishell.h"

void signal_main(int sig)
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

void    signal_back(t_pipex *data)
{
    struct sigaction sa;

    sa.sa_handler = signal_main;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa,  &data->main_sa);
}

void signal_mini_commands(int sig) // cd
{
    if (sig == SIGINT)
        return ;
}

void signal_exec_cmnd(int sig) // cat
{
    if (sig == SIGINT)
        printf("\n");
}

void    signal_change(int flag)
{
    struct sigaction sa, main_sa;

    if (flag == 1) // for our commands
        sa.sa_handler = signal_mini_commands;
    if (flag == 2) // for prebuilt commands
        sa.sa_handler = signal_exec_cmnd;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, &main_sa);
}
