#include "minishell.h"

char *get_input(t_pipex *data, int index_1, int index_2, int index_3)
{
    int     fd;
    char    *buf;
    char    *key;
    char    *input;
 
    key = data->lines[index_1]->cmnds[index_2][index_3 + 1];
    fd = 0;
    buf = get_next_line(fd, data);
    input = NULL;
    while (buf && !ft_strcmp_2(buf, key))
    {
        input = join_this(input, buf);
        free(buf);
        buf = get_next_line(fd, data);
    }
    return (free_str(buf), input);
}

int find_key(t_pipex *data, int index_1, int index_2, int index_3)
{
    int i;
    int j;
    // int count;

    // printf("PENIS2\n");
    // printf("POS IN LNE: %d\n", data->lines[index_1]->pos_in_line[index_2][index_3]);
    // if (data->here_2_old > data->lines[index_1]->pos_in_line[index_2][index_3])
    i = data->here_2_old;
    // else
        // i = data->lines[index_1]->pos_in_line[index_2][index_3];
    // i = data->lines[index_1]->pos_in_line[index_2][index_3];
    // printf("FIND KEY! --> %s I: %d\n", data->lines[index_1]->cmnds[index_2][index_3], i);
    // count = 0;
    while (data->line[++i])
    {
        // printf("LINE: %s\n", data->line + i);
        // if (data->line[i] == '\n')
            // count++;
        j = 0;
        while (data->line[i + j] && data->lines[index_1]->cmnds[index_2][index_3][j] && data->line[i + j] == data->lines[index_1]->cmnds[index_2][index_3][j])
            j++;
        if (!data->lines[index_1]->cmnds[index_2][index_3][j] && (!data->line[i + j] || data->line[i + j] == '\n' || is_space(data->line[i + j])))
            // return (data->here_2 = i + j + 1, printf("SET HERE: %d\n", i+j+1), i + j + 1);
            return (data->here_2 = i + j + 1, i + j + 1);
        // {
            // while (data->line[i + j + k] && is_space(data->line[i + j + k]))
            //     k++;
            // if (!data->line[i + j + k] || data->line[i + j + k] == '\n')
            //     return (printf("RETURN : %d\n", i + j + k + 1), i + j + k + 1);
        // }
    }
    return (data->here_2_old);
    // return (printf("NOT FOUND\n"), data->here_2_old);
}

int here_doc(t_pipex *data, int index_1, int index_2)
{
    int i;
    int this;
    char *infile;

    i = -1;
    this = 0;
    // printf("\n\nHERE DOOOOOC %d\n", index_2);
    while (data->lines[index_1]->cmnds[index_2][++i])
    {
        if (!ft_strncmp(data->lines[index_1]->cmnds[index_2][i], "<<", 3) && !data->lines[index_1]->red_cmnd[index_2][i]
        // if (printf("\n0000\n") && !ft_strncmp(data->lines[index_1]->cmnds[index_2][i], "<<", 3) && printf("\n0000\n")
            && ((!ft_strncmp(data->lines[index_1]->paths[index_2], "pathnfound", 11)
                && i == is_red_inline(data, index_1, index_2)) || i != is_red_inline(data, index_1, index_2)) 
            && find_key(data, index_1 + this, index_2, i + 1) == data->here_2_old)
        {
            // printf("HEREDOC! %d | I: %d\n", index_2, i);
            infile = get_input(data, index_1, index_2, i);
            if (!infile)
                break ;
            free_str(infile);
        }
        // else if (!ft_strncmp(data->lines[index_1]->cmnds[index_2][i], "<<", 3)
        //     && (!ft_strncmp(data->lines[index_1]->paths[index_2], "pathnfound", 11)
        //     && index_1 == data->line_count - 1))
        //     return (0);
        else if (!ft_strncmp(data->lines[index_1]->cmnds[index_2][i], "<<", 3)
            && (!ft_strncmp(data->lines[index_1]->paths[index_2], "pathnfound", 11)
                || i != is_red_inline(data, index_1, index_2)) && find_key(data, index_1 + this, index_2, i + 1))
        {
            data->here_2_old = find_key(data, index_1 + this, index_2, i + 1);
            // printf("SET OLD: %d HEREDOC\n", data->here_2_old);
            // printf("THIS: %d", this);
        }
    }
    return (1);
}

void print_list(char **arr)
{
    int i;

    i = 0;
    while (arr[i])
        printf("%s\n", arr[i++]);
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

void    update_env(t_pipex *data, int index_1, int index_2)
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
            if (!ft_strncmp(data->lines[index_1]->ops[index_2][1], ".", 1) && !*buf)
                // || !ft_strncmp(buf, data->cur_path, bigger_one(buf, data->cur_path))))
            {
                free(buf);
                if (data->cur_path[bigger_one(data->cur_path, data->cur_path) - 1] != '/')
                    buf = ft_strjoin("/", data->lines[index_1]->ops[index_2][1]);
                else
                    buf = ft_strjoin(NULL, data->lines[index_1]->ops[index_2][1]);
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
        printf("bash: cd: %s: No such a file or directory\n", str);
    if (errnum == ENOTDIR)
        printf("bash: cd: %s: Not a directory\n", str);
    if (errnum == EACCES)
        printf("bash: cd: %s: Permission denied\n", str);
    if (errnum == ENOMEM)
        printf("bash: cd: %s: Cannot allocate memory\n", str);
}

void cd_cmnd(char **argv, t_pipex *data, int index_1, int index_2)
{
    char    *home_dir;

    if (data->lines[index_1]->ops[index_2][0] && data->lines[index_1]->ops[index_2][1] && data->lines[index_1]->ops[index_2][2])
        return (write(2, "too many arguments\n", 20), exit_child(data, index_1, index_2, 1));
        // return (write(2, "too many arguments\n", 20), data->last_exit_status = 1);
    home_dir = get_home(data, data->cur_env);
    if (!ft_strncmp(argv[1], ".", 2))
        return (update_env(data, index_1, index_2));
    if (!argv[1] || !strncmp(argv[1], "~", 2))
    {
        if (chdir(home_dir) == -1)
            print_cd_err(argv[2], errno);
        else
            update_env(data, index_1, index_2);
    }
    else if (argv[1] && chdir(argv[1]) == -1)
        print_cd_err(argv[1], errno), exit_child(data, index_1, index_2, 1);
        // print_cd_err(argv[1], errno), data->last_exit_status = 1, ;
    else if (argv[1])
        update_env(data, index_1, index_2);
    // printf("PWD: %s\n", getenv("PWD"));
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

void set_rest(t_pipex *data, char **buf)
{
    int i;
    int j;

    i = 0;
    j = -1;
    while (data->cur_env[++j])
    {
        if (!buf[i])
            buf[i] = data->cur_env[j];
        else
            j--;
        i++;
    }
}

char **malloc_export_env(t_pipex *data, int count)
{
    int i;
    char **arr;
    
    i = 0;
    while (data->cur_env[i])
        i++;
    arr = ft_calloc(sizeof(char *), (i + count + 1));
    if (!arr)
        return (printf("malloc fail!\n"), error_code(data), NULL);
    arr[i + count] = NULL;
    return (arr);
}

int env_count(t_pipex *data)
{
    int i;

    i = 0;
    while (data->cur_env[i])
        i++;
    return (i);
}

void export_env(t_pipex *data, int index_1, int index_2, int count)
{
    int i;
    int rand;
    char **buf;

    buf = malloc_export_env(data, count);
    rand = 0;
    i = -1;
    while (data->lines[index_1]->ops[index_2][++i + 1])
    {
        if (rand != (INT_MAX / data->lines[index_1]->ops[index_2][i + 1][ft_strlen(data->lines[index_1]->ops[index_2][i + 1]) - 1]) % (env_count(data) + 1))
            rand = (INT_MAX / data->lines[index_1]->ops[index_2][i + 1][ft_strlen(data->lines[index_1]->ops[index_2][i + 1]) - 1]) % (env_count(data) + 1);
        else 
            rand = ((data->lines[index_1]->ops[index_2][i + 1][0] / data->lines[index_1]->ops[index_2][i + 1][ft_strlen(data->lines[index_1]->ops[index_2][i + 1]) - 1]) - 1) % (count - 1);
        // printf("RAND: %d\n", rand);
        buf[rand] = ft_strdup(data->lines[index_1]->ops[index_2][i + 1]);
    }
    set_rest(data, buf);
    free(data->cur_env);
    data->cur_env = buf;
}

void export_display(t_pipex *data)
{
    int i;

    i = -1;
    while (data->export[++i])
        printf("declare -x %s\n", data->export[i]);
}

char *malloc_cpy_export(t_pipex *data, char *str, int track, int i)
{
    char *new;

    new = NULL;
    while (str[++i])
    {
        if (str[i] == '=')
            track++;
    }
    if (!track)
        return (ft_strdup(str));
    new = ft_calloc(sizeof(char), (i + 2 + 1));
    if (!new)
        return (error_code(data), NULL);
    new[i + 2] = 0;
    i = 0;
    while (str[i] && (i == 0 || (str[i - 1] != '=')))
    {
        new[i] = str[i];
        i++;
    }
    new[i--] = 34;
    while (str[++i])
        new[i + 1] = str[i];
    new[i + 1] = 34;
    return (new);
}

void    update_export(t_pipex *data, int index_1, int index_2, int count)
{
    int i;
    int j;
    char **arr;

    i = 0;
    if (!count)
        return (exit_child(data, index_1, index_2, 1));
        // return (data->last_exit_status = 1);
    while (data->export[i])
        i++;
    arr = malloc(sizeof(char *) * (count + i + 1));
    if (!arr)
        error_code(data);
    arr[count + i] = 0;
    i = -1;
    while (data->export[++i])
        arr[i] = data->export[i];
    j = -1;
    while (data->lines[index_1]->ops[index_2][1 + ++j])
        arr[i++] = malloc_cpy_export(data, data->lines[index_1]->ops[index_2][1 + j], 0, -1);
    data->export = arr;
}

int no_identifier(char c)
{
    if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57) || (c == '_'))
        return (0);
    return (1);
}

void    export_update(t_pipex *data, int index_1, int index_2)
{
    int i;
    int j;
    int count;
    int count_export;

    i = -1;
    count = 0;
    count_export = 0;
    while (data->lines[index_1]->ops[index_2][1 + ++i])
    {
        j = 0;
        while (data->lines[index_1]->ops[index_2][1 + i][j] && data->lines[index_1]->ops[index_2][1 + i][j] != '=')
        {
            if (j == 0 && !((data->lines[index_1]->ops[index_2][1 + i][j] >= 65 && data->lines[index_1]->ops[index_2][1 + i][j] <= 90)
                || (data->lines[index_1]->ops[index_2][1 + i][j] >= 97 && data->lines[index_1]->ops[index_2][1 + i][j] <= 122)
                    || data->lines[index_1]->ops[index_2][1 + i][j] == '_'))
                return (write(2, "not a valid identifier\n", 24), exit_child(data, index_1, index_2, 1));
            if (no_identifier(data->lines[index_1]->ops[index_2][1 + i][j]))
                return (write(2, "not a valid identifier\n", 24), exit_child(data, index_1, index_2, 1));
            j++;
        }
        if (data->lines[index_1]->ops[index_2][1 + i][j] && j == 0)
            return (write(2, "not a valid identifier\n", 24), exit_child(data, index_1, index_2, 1));
            // return (write(2, "not a valid identifier\n", 24), data->last_exit_status = 1);
        else if (data->lines[index_1]->ops[index_2][1 + i][j])
            count++;
        else
            count_export++;
    }
    if (count)
        export_env(data, index_1, index_2, count);
    update_export(data, index_1, index_2, count + count_export);
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

int count_unset_env(t_pipex *data, int index_1, int index_2)
{
    int i;
    int j;
    int k;
    char *key;

    i = -1;
    k = 0;
    while (data->lines[index_1]->ops[index_2][++i + 1])
    {
        j = 0;
        while (data->cur_env[j])
        {
            key = key_this(data, data->cur_env[j]);
            if (!ft_strncmp(data->lines[index_1]->ops[index_2][i + 1], key, bigger_one(data->lines[index_1]->ops[index_2][i + 1], key)))
                k++;
            j++;
            free_this(key);
        }
    }
    if (k == 0)
        return (-1);
    return (j - k);
}

int count_unset_export(t_pipex *data, int index_1, int index_2)
{
    int i;
    int j;
    int k;
    char *key;

    i = -1;
    k = 0;
    while (data->lines[index_1]->ops[index_2][++i + 1])
    {
        j = 0;
        while (data->export[j])
        {
            key = key_this(data, data->export[j]);
            if (!ft_strncmp(data->lines[index_1]->ops[index_2][i + 1], key, bigger_one(data->lines[index_1]->ops[index_2][i + 1], key)))
                k++;
            j++;
            free_str(key);
        }
    }
    if (k == 0)
        return (-1);
    return (j - k);
}

char **malloc_unset(t_pipex *data, int count, int index_1, int index_2)
{
    char **buf;

    if (!data->lines[index_1]->ops[index_2][1])
        return (NULL);
    if (count == -1)
        return (NULL);
    buf = malloc(sizeof(char *) * (count + 1));
    if (!buf)
        return (printf("malloc fail!\n"), error_code(data), NULL);
    buf[count] = NULL;
    return (buf);
}

void unset_env(t_pipex *data, int index_1, int index_2, int i)
{
    int j;
    int check;
    char *key;

    data->buf_array = malloc_unset(data, count_unset_env(data, index_1, index_2), index_1, index_2);
    if (!data->buf_array)
        return ;
    while (data->cur_env[++i])
    {
        j = -1;
        check = 0;
        key = key_this(data, data->cur_env[i]);
        while (data->lines[index_1]->ops[index_2][++j + 1])
        {
            if (!ft_strncmp(data->lines[index_1]->ops[index_2][j + 1], key, bigger_one(data->lines[index_1]->ops[index_2][j + 1], key)))
                check = 1;
        }
        free_str(key);
        if (!check)
            data->buf_array[data->buf_int++] = data->cur_env[i];
        else
            free(data->cur_env[i]);
    }
    free(data->cur_env);
    data->cur_env = data->buf_array;
}

void unset_export(t_pipex *data, int index_1, int index_2, int i)
{

    int j;
    int check;
    char *key;

    data->buf_array = malloc_unset(data, count_unset_export(data, index_1, index_2), index_1, index_2);
    if (!data->buf_array)
        return ;
    while (data->cur_env[++i])
    {
        j = -1;
        check = 0;
        key = key_this(data, data->export[i]);
        while (data->lines[index_1]->ops[index_2][++j + 1])
        {
            if (!ft_strncmp(data->lines[index_1]->ops[index_2][j + 1], key, bigger_one(data->lines[index_1]->ops[index_2][j + 1], key)))
                check = 1;
        }
        free_str(key);
        if (!check)
            data->buf_array[data->buf_int++] = data->export[i];
        else
            free(data->export[i]);
        
    }
    free(data->export);
    data->export = data->buf_array;
}

void unset_cmnd(t_pipex *data, int index_1, int index_2, int i)
{
    data->buf_int = 0;
    unset_env(data, index_1, index_2, i);
    data->buf_int = 0;
    unset_export(data, index_1, index_2, i);
}

int only_dec(char *str)
{
    int i;

    i = 0;
	if (str[0] == '\0')
		return (0);
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\t' || str[i] == '\v')
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
    if (!str[i])
        return (1);
    return (0);
}

void    exit_cmnd(t_pipex *data, int index_1, int index_2)
{
    int i;

    i = 0;
    if (data->lines[index_1]->ops[index_2][1])
    {
        if (!only_dec(data->lines[index_1]->ops[index_2][1]))
            return (write(2, "numeric argument required\n", 27), exit_child(data, index_1, index_2, 2));
        i = ft_atoi(data->lines[index_1]->ops[index_2][1]);
        if (i > 255 || i < 0)
            i = i % 256;
        printf("exit\n");
        exit_child(data, index_1, index_2, i);
    }
    if (data->lines[index_1]->ops[index_2][2])
        return (write(2, "too many arguments\n", 20), exit_child(data, index_1, index_2, 1));
        // return (write(2, "too many arguments\n", 20), data->last_exit_status = 1);
}

void mini_parent(t_pipex *data, int index_1, int index_2, int cmnd_count)
{

    if (!data->fd_out && index_2 < cmnd_count - 1 && dup2(data->lines[index_1]->pipes[index_2 + 1][1], STDOUT_FILENO) == -1)
        return (printf("dup2"), error_code(data));
    else if (data->fd_out && dup2(data->fd_out, STDOUT_FILENO) == -1)
        return (printf("dup2"), error_code(data));
    if (!ft_strncmp(data->lines[index_1]->ops[index_2][0], "cd", 3))
        cd_cmnd(data->lines[index_1]->ops[index_2], data, index_1, index_2);
    else if (!ft_strncmp(data->lines[index_1]->ops[index_2][0], "export", 7) && data->lines[index_1]->ops[index_2][1])
        export_update(data, index_1, index_2);
    else if (!ft_strncmp(data->lines[index_1]->ops[index_2][0], "unset", 6))
        unset_cmnd(data, index_1, index_2, -1);
    else if (!ft_strncmp(data->lines[index_1]->ops[index_2][0], "exit", 5))
        exit_cmnd(data, index_1, index_2);
    else if (!ft_strncmp(data->lines[index_1]->ops[index_2][0], "env", 4) && !data->lines[index_1]->ops[index_2][1])
        print_list(data->cur_env);
    else if (!ft_strncmp(data->lines[index_1]->ops[index_2][0], "pwd", 4))
        printf("%s\n", data->cur_path);
    else if (!ft_strncmp(data->lines[index_1]->ops[index_2][0], "ls", 3) && !is_valid_cwd(data))
        printf("\n");
    else if (!ft_strncmp(data->lines[index_1]->ops[index_2][0], "export", 7) && !data->lines[index_1]->ops[index_2][1])
        export_display(data);
}

void mini_child(t_pipex *data, int index_1, int index_2)
{
    if (!ft_strncmp(data->lines[index_1]->ops[index_2][0], "env", 4) && !data->lines[index_1]->ops[index_2][1])
        print_list(data->cur_env);
    else if (!ft_strncmp(data->lines[index_1]->ops[index_2][0], "pwd", 4))
        printf("%s\n", data->cur_path);
    else if (!ft_strncmp(data->lines[index_1]->ops[index_2][0], "ls", 3) && !is_valid_cwd(data))
        printf("\n");
    else if (!ft_strncmp(data->lines[index_1]->ops[index_2][0], "export", 7) && !data->lines[index_1]->ops[index_2][1])
        export_display(data);
    else if (!ft_strncmp(data->lines[index_1]->ops[index_2][0], "export", 7) && data->lines[index_1]->ops[index_2][1])
        export_update(data, index_1, index_2);
    else if (!ft_strncmp(data->lines[index_1]->ops[index_2][0], "unset", 6))
        unset_cmnd(data, index_1, index_2, -1);
    else if (!ft_strncmp(data->lines[index_1]->ops[index_2][0], "exit", 5))
        exit_cmnd(data, index_1, index_2);
}
