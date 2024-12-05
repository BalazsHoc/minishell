#include "minishell.h"

int here_doc(t_pipex *data, int index)
{
    int i;
    char *infile;

    i = -1;
    while (data->cmnds[index][++i])
    {
        if (!ft_strncmp(data->cmnds[index][i], "<<", 3)
            && (!ft_strncmp(data->paths[index], "pathnfound", 11) || i != is_red_inline(data, index)))
        {
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
            // printf("OLD: %s\n", getenv("OLDPWD"));
            free(buf);
        }
    }
    buf = ft_calloc(sizeof(char), (BUF_SIZE_ENV * 100) + 1);
    if (!buf)
        return (printf("malloc fail!\n"), error_code(data));
    getcwd(buf, BUF_SIZE_ENV * 100);
    i = -1;
    // printf("BUF: %s\n", buf);
    if (!buf)
        return (printf("FAILED GETCWD()\n"), error_code(data));
    while (data->cur_env[++i] && i < 100)
    {
        if (!ft_strncmp(data->cur_env[i], "PWD=", 4))
        {
            if (!ft_strncmp(data->ops[index][1], ".", 1) && !*buf)
                // || !ft_strncmp(buf, data->cur_path, bigger_one(buf, data->cur_path))))
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
                // printf("CUR: %s\n", data->cur_path);
            }
            else
            {
                free_str(data->cur_env[i]);
                data->cur_env[i] = ft_strjoin("PWD=", buf);
            }
            // printf("THIS IS NEW PWD: %s\n", data->cur_env[i]);
            free(buf);
        }
    }
}

char    *get_home(t_pipex *data, char **env)
{
    char *home_dir;

    home_dir = getenv("HOME");
    // printf("home: %s\n", home_dir);
    if (!home_dir)
    {
        printf("Home is not set\n");
        return (free_list(env), error_code(data), NULL);
    }
    return (home_dir);
}

void print_cd_err(char *str, int errnum)
{
    if (errnum == ENOENT)
        printf("-bash: cd: %s: No such a file or directory\n", str);
    if (errnum == ENOTDIR)
        printf("-bash: cd: %s: Not a directory\n", str);
    if (errnum == EACCES)
        printf("-bash: cd: %s: Permission denied\n", str);
    if (errnum == ENOMEM)
        printf("-bash: cd: %s: Cannot allocate memory\n", str);
}

void cd_cmnd(char **argv, t_pipex *data, int index)
{
    char    *home_dir;

    if (data->ops[index][0] && data->ops[index][1] && data->ops[index][2])
        return (printf("-bash: cd: too many arguments\n"), error_code(data));
    home_dir = get_home(data, data->cur_env);
    if (!ft_strncmp(argv[1], ".", 2))
        return (update_env(data, index));
    if (!argv[1] || !strncmp(argv[1], "~", 2))
    {
        if (chdir(home_dir) == -1)
            print_cd_err(argv[2], errno);
        else
            update_env(data, index);
    }
    else if (argv[1] && chdir(argv[1]) == -1)
        print_cd_err(argv[2], errno);
    else if (argv[1])
        update_env(data, index);
    // printf("PWD: %s\n", getenv("PWD"));
}

char *env_cmnd(t_pipex *data, int index)
{
    int i;
    int j;
    int count;
    char *out;


    i = -1;
    if (data->ops[index][1])
        return (NULL);
    while (data->cur_env[++i])
        count += ft_strlen(data->cur_env[i]) + 1;
    out = malloc(sizeof(char) * (count + 1));
    if (!out)
        return (printf("malloc fail!\n"), error_code(data), NULL);
    out[count] = 0;
    i = -1;
    count = 0;
    while (data->cur_env[++i])
    {
        j = -1;
        while (data->cur_env[i][++j])
            out[count++] = data->cur_env[i][j];
        // FIGURE!! should the last line also be newline in the end?
        out[count++] = '\n';
    }
    return (out);
}

int is_valid_cwd(t_pipex *data)
{
    char *buf;

    buf = ft_calloc(sizeof(char), (BUF_SIZE_ENV * 100) + 1);
    if (!buf)
        return (printf("malloc fail!\n"), error_code(data), -1);
    getcwd(buf, BUF_SIZE_ENV * 100);
    if (!buf)
        return (printf("FAILED GETCWD()\n"), error_code(data), -1);
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
        printf("malloc fail!\n"), error_code(data);
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

void export_cmnd_1(t_pipex *data, int index)
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
        printf("RAND: %d\n", rand);
        buf[rand] = malloc(sizeof(char) * (ft_strlen(data->ops[index][i + 1]) + 1));
        if (!buf[rand])
            printf("malloc fail!\n"), error_code(data);
        buf[rand][ft_strlen(data->ops[index][i + 1])] = 0;
        ft_strlcpy(buf[rand], data->ops[index][i + 1], ft_strlen(data->ops[index][i + 1]) + 1);
    }
    set_rest(data, buf);
}

char *export_cmnd_2(t_pipex *data, char *this)
{
    int i;
    int j;
    int count;
    char *out;

    i = -1;
    while (data->cur_env[++i])
    {
        if (ft_strncmp(data->cur_env[i], "_=", 2))
            count += ft_strlen(data->cur_env[i]) + 1 + 11;
    }
    out = malloc(sizeof(char) * (count + 1));
    if (!out)
        return (printf("malloc fail!\n"), error_code(data), NULL);
    out[count] = 0;
    i = -1;
    count = 0;
    while (data->cur_env[++i])
    {
        if (ft_strncmp(data->cur_env[i], "_=", 2))
        {
            j = -1;
            while (++j < 11)
                out[count++] = this[j];
            j = -1;
            while (data->cur_env[i][++j])
                out[count++] = data->cur_env[i][j];
            if (!((data->cur_env[i + 1] && (!ft_strncmp(data->cur_env[i + 1], "_=", 2) && !data->cur_env[i + 2]))
                || !data->cur_env[i + 1]))
                out[count++] = '\n';
        }
    }
    return (out);
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
        return (printf("malloc fail!\n"), error_code(data), NULL);
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
        return (printf("malloc fail!\n"), error_code(data), NULL);
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

    if (!data->ops[index][1])
        return (printf("bash: unset: not enough arguments\n"), exit_child(data));
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

void mini_commands(t_pipex *data, int index)
{
    if (!ft_strncmp(data->ops[index][0], "cd", 3))
        cd_cmnd(data->ops[index], data, index);
    else if (!ft_strncmp(data->ops[index][0], "exit", 5))
        error_code(data);
    else if (!ft_strncmp(data->ops[index][0], "export", 7) && data->ops[index][1])
        export_cmnd_1(data, index);
    else if (!ft_strncmp(data->ops[index][0], "unset", 6))
        unset_cmnd(data, index, -1, 0);
}

void mini_child(t_pipex *data, int index)
{
    if (!ft_strncmp(data->ops[index][0], "env", 4) && !data->ops[index][1])
        printf("%s", env_cmnd(data, index));
    else if (!ft_strncmp(data->ops[index][0], "pwd", 4))
        printf("%s\n", data->cur_path);
    else if (!ft_strncmp(data->ops[index][0], "ls", 3) && !is_valid_cwd(data))
        printf("\n");
    else if (!ft_strncmp(data->ops[index][0], "export", 7) && !data->ops[index][1])
        printf("%s\n", export_cmnd_2(data, "declare -x "));
}
