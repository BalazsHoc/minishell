#include "../minishell.h"

int		glob_var;

void heredoc_sigint_handler(int sig)
{
    if (sig == SIGINT)
        glob_var = 1;
}

char *get_input(t_pipex *data, int index_1, int index_2)
{
    int     fd;
    char    *buf;
    char    *key;
    char    *input;
    struct sigaction sa, old_sa;

    glob_var = 0;
    sa.sa_handler = heredoc_sigint_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, &old_sa);
    key = data->cmnds[index_1][index_2 + 1];
    if (!ft_strncmp(data->cmnds[index_1][index_2], "<", 2))
        return (NULL);
    else
        fd = 0;
    buf = get_next_line(fd, data);
    input = NULL;
    while (buf && !ft_strcmp_2(buf, key))
    {
        if (glob_var)
        {
            sigaction(SIGINT, &old_sa, NULL);
            return (free_str(input), free_str(buf), NULL);
        }
        input = join_this(input, buf);
        free(buf);
        buf = get_next_line(fd, data);
    }
    sigaction(SIGINT, &old_sa, NULL);
    return (printf("\n"), free_str(buf), input);
}
