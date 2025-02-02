#include "../minishell.h"

void	signal_change(int flag)
{
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
}