#include "minishell.h"

void free_this(char *s)
{
    if (s)
        free(s);
}

int this_in_that(char c, char *s)
{
    int i;

    i = 0;
    while (s && s[i])
    {
        if (c == s[i])
            return (1);
        i++;
    }
    return (0);
}

char *join_this(char *s1, char *s2)
{
    int i;
    int j;
    char *new;

    i = 0;
    j = 0;
    if (!s2)
        return (free_this(s1), NULL);
    while (s1 && s1[i])
        i++;
    while (s2 && s2[j])
        j++;
    if (i + j == 0)
        return (NULL);
    new = malloc(sizeof(char) * (i + j + 1));
    if (!new)
        return (free_this(s1), NULL);
    new[i + j] = 0;
    i = 0;
    while (s1 && s1[i])
    {
        new[i] = s1[i];
        i++;
    }
    j = 0;
    while (s2 && s2[j])
        new[i++] = s2[j++];
    free_this(s1);
    return (new);
}

char *this(char *buf)
{
    int i;
    char *new;

    i = 0;
    if (!buf || !*buf)
        return (NULL);
    while (buf[i] && buf[i] != '\n')
        i++;
    if (buf[i] == '\n')
        i++;
    new = malloc(sizeof(char) * (i + 1));
    if (!new)
        return (free_this(buf), NULL);
    new[i] = 0;
    i = 0;
    while (buf[i] && buf[i] != '\n')
    {
        new[i] = buf[i];
        i++;
    }
    if (buf[i] == '\n')
        new[i] = '\n';
    return (new);
}

char *that(char *buf)
{
    int i;
    int j;
    char *new;

    i = 0;
    j = 0;
    if (buf && !*buf)
        return (free_this(buf), NULL);
    while (buf && buf[i] && buf[i] != '\n')
        i++;
    if (buf[i] == '\n')
        i++;
    while (buf && buf[j])
        j++;
    if (j - i == 0)
        return (free_this(buf), NULL);
    new = malloc(sizeof(char) * (j - i + 1));
    if (!new)
        return (free_this(buf), NULL);
    new[j - i] = 0;
    if (!buf[i])
        return (free_this(buf), NULL);
    if (buf[i - 1] == '\n')
        i--;
    j = 0;
    while (buf[++i])
        new[j++] = buf[i];
    free_this(buf);
    return (new);
}

char *gnl(int fd)
{
    static char *buf;
    char *reader;
    int n;

    if (fd < 0 || BUF_SIZE < 0 || BUF_SIZE > INT_MAX)
        return (free_this(buf), NULL);
    n = 1;
    reader = malloc(sizeof(char) * BUF_SIZE + 1);
    if (!reader)
        return (free_this(buf), NULL);
    while (n && !this_in_that('\n', buf))
    {
        n = read(fd, reader, BUF_SIZE);
        if (n < 0)
            return (free_this(buf), NULL);
        reader[n] = 0;
        buf = join_this(buf, reader);
        if (!buf)
            return (free_this(reader), NULL);
    }
    free(reader);
    reader = this(buf);
    buf = that(buf);
    return (reader);
}

char *get_in(t_pipex *data, int index)
{
    int i;
    int fd;
    char *infile;
    char *buf;

    i = -1;
    infile = NULL;
    while (data->cmnds[index][++i])
    {
        if (!ft_strncmp(data->cmnds[index][i], "<", 2))
            infile = data->cmnds[index][i + 1];
    }
    fd = open(infile, O_RDONLY);
    if (fd == -1)
        printf("ERRNO: %d", errno);
    buf = gnl(fd);
    infile = NULL;
    while (buf)
    {
        infile = join_this(infile, buf);
        free(buf);
        buf = gnl(fd);
    }
    close(fd);
    return (infile);
}

void exec_cmnd(t_pipex *data)
{
    int i;
    char *infile;
    char *outfile;
    
    i = -1;
    outfile = NULL;
    while (data->cmnds[++i])
    {
        infile = get_in(data, i);
        if (!outfile)
            printf("INFILE: %s\n", infile);
        // outfile = find_out(data, i);
        // exec_this(infile, data, outfile);
    }
}