#include "../minishell.h"

int		glob_var = 0;

void heredoc_sigint_handler(int sig)
{
    if (sig == SIGINT)
    {
        glob_var = 1; // Mark that SIGINT was received
        write(STDOUT_FILENO, "\n", 1);
    }
}

char *get_input(t_pipex *data, int index_1, int index_2)
{
    char *buf;
    char *key;
    char *input;
    struct sigaction sa, old_sa;

    glob_var = 0;
    sa.sa_handler = heredoc_sigint_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, &old_sa);
    key = data->cmnds[index_1][index_2 + 1];
    if (!ft_strncmp(data->cmnds[index_1][index_2], "<", 2))
        return (NULL);
    buf = readline("> ");
    if (!buf)
        error_code(data);
    input = NULL;
    while (buf && !ft_strcmp_2(buf, key))
    {
        if (glob_var)
        {
            sigaction(SIGINT, &old_sa, NULL);
            return (free_str(input), free_str(buf), NULL);
        }
        input = join_this(input, buf);
        if (!input)
            return (free_str(buf), error_code(data), NULL);
        free_str(buf);
        buf = readline("> ");
    }
    sigaction(SIGINT, &old_sa, NULL);
    free_str(buf);
    return (input);
}