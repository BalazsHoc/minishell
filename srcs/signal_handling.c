#include "../minishell.h"

int		glob_var;

void signal_main(int sig)
{
    glob_var += 1;
    // printf("glob_var: %d", glob_var);
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		// write(1, "\n", 1);
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
    sigaction(SIGINT, &sa,  &data->old_sa);
}

void signal_exec(int sig)
{
    if (sig == SIGINT)
        glob_var += 1;
    // printf("glob_var: %d", glob_var);
}

void    signal_change(t_pipex *data)
{
    struct sigaction sa, old_sa;

    glob_var = 0;
    sa.sa_handler = signal_exec;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, &old_sa);
    data->old_sa = old_sa;
    // printf("glob_var: %d", glob_var);
}

char *get_input(t_pipex *data, int index_1, int index_2)
{
    int     fd;
    char    *buf;
    char    *key;
    char    *input;
    // int     sig_num;
    // struct sigaction sa, old_sa;

    // glob_var = 0;
    // sa.sa_handler = signal_exec;
    // sigemptyset(&sa.sa_mask);
    // sa.sa_flags = 0;
    // sigaction(SIGINT, &sa, &old_sa);
    // sig_num = glob_var;
    key = data->cmnds[index_1][index_2 + 1];
    if (!ft_strncmp(data->cmnds[index_1][index_2], "<", 2))
        return (NULL);
    else
        fd = 0;
    buf = get_next_line(fd, data);
    input = NULL;
    while (buf && !ft_strcmp_2(buf, key))
    {
        // if (sig_num != glob_var)
        // {
        //     printf("Penis\n");
        //     sigaction(SIGINT, &data->old_sa, NULL);
        //     return (free_str(input), free_str(buf), NULL);
        // }
        input = join_this(input, buf);
        free(buf);
        buf = get_next_line(fd, data);
    }
    // sigaction(SIGINT, &old_sa, NULL);
    return (printf("\n"), free_str(buf), input);
}
