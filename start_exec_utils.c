#include "minishell.h"

int here_doc(t_pipex *data, int index)
{
    int i;
    char *infile;

    i = -1;
    printf("START HEREDOC!\n");
    while (data->cmnds[index][++i])
    {
        printf("HEREDOC! %d\n", i);
        if ((!ft_strncmp(data->cmnds[index][i], "<<", 3) || !ft_strncmp(data->cmnds[index][i], "<", 2))
            && (!ft_strncmp(data->paths[index], "pathnfound", 11) || i != is_red_inline(data, index)))
        {
            printf("GET_INPUT!\n");
            infile = get_input(data, index, i);
            free_str(infile);
            i++;
        }
    }
    return (1);
}

char    *trim_last(char *old)
{
    int i;
    int check;
    char *new;

    i = -1;
    while (old[++i])
    {
        if (old[i] == '/')
            check = i;
    }
    new = malloc(sizeof(char) * (check + 1));
    if (!new)
        return (NULL);
    new[check] = 0;
    i = -1;
    while (++i < check)
        new[i] = old[i];
    free(old);
    return (new);
}

int bigger_one(char *s1, char *s2)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (s1[i])
        i++;
    while (s2[j])
        j++;
    if (i > j)
        return (i);
    return (j);
}

void    update_env(t_pipex *data, int index)
{
    int i;
    char *buf;

    i = -1;
    buf = NULL;
    // if (!ft_strncmp(data->ops[index][1], ".", 2))
    //     return ;
    while (data->cur_env[++i] && i < 100)
    {
        if (!ft_strncmp(data->cur_env[i], "OLDPWD=", 7))
        {
            buf = data->cur_env[i];
            data->cur_env[i] = ft_strjoin("OLDPWD=", data->cur_path);
            printf("OLD: %s\n", getenv("OLDPWD"));
            free(buf);
        }
    }
    buf = ft_calloc(sizeof(char), (BUF_SIZE_ENV * 100) + 1);
    if (!buf)
        return (printf("malloc fail!\n"), error_code(data, NULL, 1, 1));
    getcwd(buf, BUF_SIZE_ENV * 100);
    i = -1;
    printf("BUF: %s\n", buf);
    if (!buf)
        return (printf("FAILED GETCWD()\n"), error_code(data, NULL, 0, 0));
    while (data->cur_env[++i] && i < 100)
    {
        if (!ft_strncmp(data->cur_env[i], "PWD=", 4))
        {
            if (!ft_strncmp(data->ops[index][1], ".", 1)
                && (!*buf || !ft_strncmp(buf, data->cur_path, bigger_one(buf, data->cur_path))))
            {
                free(buf);
                if (data->cur_path[bigger_one(data->cur_path, data->cur_path) - 1] != '/')
                    buf = ft_strjoin("/", data->ops[index][1]);
                else
                    buf = ft_strjoin(NULL, data->ops[index][1]);
                data->cur_path = ft_strjoin(data->cur_path, buf);
                data->cur_env[i] = ft_strjoin("PWD=", data->cur_path);
                free(data->cur_path);
                data->cur_path = data->cur_env[i] + 4;
            }
            else
            {
                free_str(data->cur_env[i]);
                data->cur_env[i] = ft_strjoin("PWD=", buf);
            }
            free(buf);
        }
    }
}

char    *get_home(t_pipex *data, char **env)
{
    char *home_dir;

    home_dir = getenv("HOME");
    printf("home: %s\n", home_dir);
    if (!home_dir)
    {
        printf("Home is not set\n");
        return (free_list(env), error_code(data, NULL, 1, 1), NULL);
    }
    return (home_dir);
}

void cd_cmnd(char **argv, t_pipex *data, int index)
{
    char    *home_dir;

    if (data->ops[index][2])
        return (printf("-bash: cd: too many arguments\n"), error_code(data, NULL, 0, 1));
    home_dir = get_home(data, data->cur_env);
    if (!strncmp(argv[0], "cd", 3))
    {
        if (!argv[1] || !strncmp(argv[1], "~", 2))
            chdir(home_dir);
        else if (argv[1] && chdir(argv[1]) == -1)
        {
            if (errno == ENOENT)
                printf("-bash: cd: %s: No such a file or directory\n", argv[2]);
            if (errno == ENOTDIR)
                printf("-bash: cd: %s: Not a directory\n", argv[2]);
            if (errno == EACCES)
                printf("-bash: cd: %s: Permission denied\n", argv[2]);
            if (errno == ENOMEM)
                printf("-bash: cd: %s: Cannot allocate memory\n", argv[2]);
        }
        else if (argv[1])
            update_env(data, index);
        printf("PWD: %s\n", getenv("PWD"));
    }
}

void env_cmnd(t_pipex *data, int index)
{
    int i;
    int fd;


    i = -1;
    fd = open_out(data, index);
    if (fd == -2)
        fd = 1;
    // printf("FD: %d\n", fd);
    while (data->cur_env[++i])
    {
        write(fd, data->cur_env[i], ft_strlen(data->cur_env[i]));
        write(fd, "\n", 1);
    }
    if (fd > 2)
        close(fd);
}

int is_valid_cwd(t_pipex *data)
{
    char *buf;

    buf = ft_calloc(sizeof(char), (BUF_SIZE_ENV * 100) + 1);
    if (!buf)
        return (printf("malloc fail!\n"), error_code(data, NULL, 1, 1), -1);
    getcwd(buf, BUF_SIZE_ENV * 100);
    if (!buf)
        return (printf("FAILED GETCWD()\n"), error_code(data, NULL, 0, 0), -1);
    if (!*buf)
        return (free(buf), 0);
    return (free(buf), 1);
}

char **malloc_env_export(t_pipex *data, int index)
{
    int i;
    int j;
    char **buf;

    i = 0;
    j = 0;
    while (data->ops[index][i + 1])
        i++;
    while ((data->cur_env)[j])
        j++;
    buf = ft_calloc(sizeof(char *), (i + j + 1));
    if (!buf)
        printf("malloc fail!\n"), error_code(data, NULL, 1, 1);
    buf[i + j] = NULL;
    return (buf);
}

void set_rest(t_pipex *data, char **buf)
{
    int i;
    int j;

    i = -1;
    j = -1;
    while (data->cur_env[++j])
    {
        if (!buf[++i])
            buf[i] = data->cur_env[j];
        else
            j--;
    }
    data->cur_env = buf;
}

void export_cmnd(t_pipex *data, int index)
{
    int i;
    int j;
    int rand;
    char **buf;

    buf = malloc_env_export(data, index);
    j = 0;
    while (data->cur_env[j])
        j++;
    i = -1;
    rand = 0;
    while (data->ops[index][++i + 1])
    {
        if (rand != (INT_MAX / data->ops[index][i + 1][ft_strlen(data->ops[index][i + 1]) - 1]) % (j + 1))
            rand = (INT_MAX / data->ops[index][i + 1][ft_strlen(data->ops[index][i + 1]) - 1]) % (j + 1);
        else 
            rand = ((data->ops[index][i + 1][0] / data->ops[index][i + 1][ft_strlen(data->ops[index][i + 1]) - 1]) - 1) % (j - 1);
        buf[rand] = malloc(sizeof(char) * (ft_strlen(data->ops[index][i + 1]) + 1));
        if (!buf[rand])
            printf("malloc fail!\n"), error_code(data, NULL, 1, 1);
        buf[rand][ft_strlen(data->ops[index][i + 1])] = 0;
        ft_strlcpy(buf[rand], data->ops[index][i + 1], ft_strlen(data->ops[index][i + 1]) + 1);
    }
    set_rest(data, buf);
}

char *key_this(t_pipex *data, char *s)
{
    int i;
    char *key;

    i = 0;
    while (s[i] && s[i] != '=')
        i++;
    key = malloc(sizeof(char) * (i + 1));
    if (!key)
        return (printf("malloc fail!\n"), error_code(data, NULL, 1, 1), NULL);
    key[i] = 0;
    i = 0;
    while (s[i] && s[i] != '=')
    {
        key[i] = s[i];
        i++;
    }
    return (key);
}

int count_unset_env(t_pipex *data, int index)
{
    int i;
    int j;
    int k;
    char *key;

    i = -1;
    k = 0;
    while (data->ops[index][++i + 1])
    {
        j = 0;
        while (data->cur_env[j])
        {
            key = key_this(data, data->cur_env[j]);
            if (!ft_strncmp(data->ops[index][i + 1], key, bigger_one(data->ops[index][i + 1], key)))
                k++;
            j++;
            free_str(key);
        }
    }
    return (j - k);
}

char **malloc_env_unset(t_pipex *data, int count)
{
    char **buf;

    buf = malloc(sizeof(char *) * (count + 1));
    if (!buf)
        return (printf("malloc fail!\n"), error_code(data, NULL, 1, 1), NULL);
    buf[count] = NULL;
    return (buf);
}

void print_list(char **arr)
{
    int i;
    i=0;
    while (arr[i])
    {
        printf("ARR: %s\n", arr[i++]);
    }
}

void unset_cmnd(t_pipex *data, int index, int i, int k)
{
    int j;
    int check;
    char **new;
    char *key;

    new = malloc_env_unset(data, count_unset_env(data, index));
    while (data->cur_env[++i])
    {
        j = -1;
        check = 0;
        key = key_this(data, data->cur_env[i]);
        while (data->ops[index][++j + 1])
        {
            if (!ft_strncmp(data->ops[index][j + 1], key, bigger_one(data->ops[index][j + 1], key)))
                check = 1;
        }
        free_str(key);
        if (!check)
            new[k++] = data->cur_env[i];
        else
            free(data->cur_env[i]);
        
    }
    free(data->cur_env);
    data->cur_env = new;
}

int mini_commands(t_pipex *data, int *index)
{
    if (!ft_strncmp(data->ops[*index][0], "cd", 3) && ++(*index))
        cd_cmnd(data->ops[*index - 1], data, (*index) - 1);
    else if (!ft_strncmp(data->ops[*index][0], "env", 4) && !data->cmnds[*index + 1])
        env_cmnd(data, ++(*index) - 1);
    else if (!ft_strncmp(data->ops[*index][0], "exit", 5) && !data->cmnds[*index + 1])
        return (error_code(data, NULL, 1, 0), 0);
    else if (!ft_strncmp(data->ops[*index][0], "pwd", 4) && ++(*index))
        printf("%s\n", data->cur_path);
    else if (!ft_strncmp(data->ops[*index][0], "ls", 3) && !is_valid_cwd(data))
        ++(*index);
    else if (!ft_strncmp(data->ops[*index][0], "export", 7) && ++(*index))
        export_cmnd(data, *index - 1);
    else if (!ft_strncmp(data->ops[*index][0], "unset", 6) && ++(*index))
        unset_cmnd(data, *index - 1, -1, 0);
    return (1);
}
