#include "../minishell.h"

int	g_signal;

void	terminal_settings(void)
{
	struct termios	original_termios;
	struct termios	new_termios;

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

void	signal_main(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 1;
		write(STDIN_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signal_back(void)
{
	signal(SIGINT, signal_main);
	signal(SIGQUIT, signal_main);
}

void	signal_mini_commands(int sig)
{
	if (sig == SIGINT)
	{
		g_signal += 1;
		errno = 130;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	signal_exec_cmnd(int sig)
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