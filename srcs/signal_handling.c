#include "../minishell.h"

int		glob_var;

void signal_main(int sig)
{
    glob_var += 1;
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

void signal_exec_ours(int sig)
{
    if (sig == SIGINT)
        glob_var += 1;
}

void signal_exec_pre_cmds(int sig)
{
    if (sig == SIGINT)
    {
        glob_var += 1;
        printf("\n");
    }
}

void    signal_change(t_pipex *data, int flag)
{
    struct sigaction sa, main_sa;

    glob_var = 0;
    if (flag == 1) // for our commands
        sa.sa_handler = signal_exec_ours;
    if (flag == 2) // for prebuilt commands
        sa.sa_handler = signal_exec_pre_cmds;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, &main_sa);
    data->main_sa = main_sa;
}
