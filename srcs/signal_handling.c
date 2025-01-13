#include "../minishell.h"

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
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		return;
	}
}

void    signal_back(t_pipex *data)
{
    struct sigaction sa;

    sa.sa_handler = signal_main;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa,  &data->main_sa);
}

void signal_mini_commands(int sig) // here_doc
{
     if (sig == SIGINT)
	 {
		errno = 130;
        printf("\n");
	 }
}

void signal_exec_cmnd(int sig) // cat
{
    if (sig == SIGINT)
	{
		errno = 130;
        printf("\n");
	}
}

void	signal_change(int flag)
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

// void signal_main(int sig)
// {
// 	if (sig == SIGINT)
// 	{
// 		write(1, "\n", 1);
// 		rl_replace_line("", 0);
// 		rl_on_new_line();
// 		rl_redisplay();
// 	}
// 	if (sig == SIGQUIT)
// 	{
// 		rl_replace_line("", 0);
// 		rl_on_new_line();
// 		rl_redisplay();
// 		return ;
// 	}
// }


// void	signal_head()
// {
//     signal(SIGINT, signal_main);
// 	signal(SIGQUIT, signal_main);
// }

// void signal_mini_commands(int sig) // here_doc
// {
//     if (sig == SIGINT)
// 	{
// 		write(STDOUT_FILENO, "\n", 1);
//     	return ;
// 	}
// }

// void signal_exec_cmnd(int sig) // cat
// {
//     if (sig == SIGINT)
//         printf("\n");
// 	else if (sig == SIGQUIT)
// 		printf("Quit (core dump)\n");
// }

// void    signal_change(int flag)
// {
//     if (flag == 1) // for our commands
// 	{
// 		signal(SIGINT, signal_mini_commands);
// 		signal(SIGQUIT, signal_mini_commands);
// 	}
//     if (flag == 2) // for prebuilt commands
//     {
// 		signal(SIGINT, signal_exec_cmnd);
// 		signal(SIGQUIT, signal_exec_cmnd);
// 	}
// }
