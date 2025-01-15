#include "../minishell.h"

int	g_signal;

//	It will take sigquit access from printing anything 
void	terminal_settings()
{
	struct termios original_termios;
	struct termios new_termios;

	if (tcgetattr(STDIN_FILENO, &original_termios) == -1)
	{
		perror("Error terminal settings\n");
		exit(EXIT_FAILURE);
	}
	new_termios = original_termios;
	new_termios.c_cc[VQUIT] = 0;
	new_termios.c_cc[VEOF] = 0;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &new_termios) == -1)
	{
		perror("Error terminal settings\n");
		exit(EXIT_FAILURE);
	}
}

void signal_main(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 1;
		write(STDIN_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		// printf("SIGQUIT here\n");
		return;
	}
}

void    signal_back()
{
	signal(SIGINT, signal_main);
	signal(SIGQUIT, signal_main);
    // struct sigaction sa;

    // sa.sa_handler = signal_main;
    // sigemptyset(&sa.sa_mask);
    // sa.sa_flags = 0;
    // sigaction(SIGINT, &sa,  &data->main_sa);
	// sigaction(SIGQUIT, &sa,  &data->main_sa);
	// // signal(SIGQUIT, SIG_IGN);
}

void signal_mini_commands(int sig) // here_doc
{
     if (sig == SIGINT)
	 {
		g_signal += 1;
		errno = 130;
        ioctl(STDIN_FILENO, TIOCSTI, "\n");
		// rl_replace_line("", 0);
		// rl_on_new_line();
	 }
	if (sig == SIGQUIT)
		printf("SIGQUIT\n");
}

void signal_exec_cmnd(int sig) // cat
{
    if (sig == SIGINT)
	{
		g_signal += 1;
		errno = 130;
		printf("\n");
		return ;
	}
	if (sig == SIGQUIT)
		printf("Quit (core dumped)\n");
}

void	signal_change(int flag)
{
	if (flag == 0)
	{
		signal(SIGINT, signal_main);
		signal(SIGQUIT, signal_main);
	}
    if (flag == 1) // for our commands
	{
		signal(SIGINT, signal_mini_commands);
		signal(SIGQUIT, signal_mini_commands);
	}
        // signal_mini_commands;
    if (flag == 2) // for prebuilt commands
	{
		signal(SIGINT, signal_exec_cmnd);
		signal(SIGQUIT, signal_exec_cmnd);
	}
        // signal_exec_cmnd();
    // sigemptyset(&sa.sa_mask);
    // sa.sa_flags = 0;
    // sigaction(SIGINT, &sa, &main_sa);
	// sigaction(SIGQUIT, &sa, &main_sa);
}
