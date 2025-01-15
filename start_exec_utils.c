#include "minishell.h"

char *get_input(t_pipex *data, int index_1, int index_2, int index_3)
{
    int     fd;
    char    *buf;
    char    *key;
    char    *input;
 
	g_signal = 0;
	key = data->lines[index_1]->cmnds[index_2][index_3 + 1];
	fd = 0;
	input = NULL;
	buf = readline("> ");
	while (buf && !g_signal && !ft_strcmp_2(buf, key))
	{
		if (!buf)
			break ;
		if (buf[0] != '\0')
		{
			input = join_this(input, buf);
			free_str(&buf);
		}
		buf = readline("> ");
	}
	// printf("%d\n", g_signal);
    return (input);
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
    // printf("DATA OLD: %d\n", i);
    if (i == 0 || !data->line[i - 1] || !data->line[i] || !data->line[i + 1])
        return (i);
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
            return (data->here_2 = i + j + 1, i + j + 1);
            // return (data->here_2 = i + j + 1, printf("SET HERE: %d\n", i+j+1), i + j + 1);
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
            free_str(&infile);
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
                free_str(&data->cur_env[i]);
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
        perror("getenv() failed");
        return (free_list(env), error_code(data), NULL);
    }
    return (home_dir);
}

void print_cd_err(int errnum)
{
    if (errnum == ENOENT)
        write(2, "bash: cd: %s: No such a file or directory\n", 43);
    else if (errnum == ENOTDIR)
        write(2, "bash: cd: %s: Not a directory\n", 31);
    else if (errnum == EACCES)
        write(2, "bash: cd: %s: Permission denied\n", 33);
    else if (errnum == ENOMEM)
        write(2, "bash: cd: %s: Cannot allocate memory\n", 38);
    else
        write(2, "bash: cd: failed\n", 18);
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
            print_cd_err(errno);
        else
            update_env(data, index_1, index_2);
    }
    else if (argv[1] && chdir(argv[1]) == -1)
        print_cd_err(errno), exit_child(data, index_1, index_2, 1);
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
        return (perror("malloc failed!"), error_code(data), -1);
    getcwd(buf, BUF_SIZE_ENV * 100);
    if (!buf)
        return (perror("getcwd() failed!"), error_code(data), -1);
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
        return (perror("malloc failed!"), error_code(data), NULL);
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

int already_there(t_pipex *data, char *str)
{
    int i;
    int j;

    j = 0;
    i = -1;
    while (str[j] && str[j] != '=')
        j++;
    // printf("ALRDY COUNT TILL =: %d\n", j);
    while (data->cur_env[++i])
    {
        if (!ft_strncmp(str, data->cur_env[i], j + 1)
            && data->cur_env[i][j] == '=')
            return (i);
            // return (printf("ALRDY THERE %s\n", str), i);
    }
    return (-1);
    // return (printf("NOT ALRDY THERE %s\n", str), -1);
}

int already_there_2(t_pipex *data, char *str)
{
    int i;
    int j;

    j = 0;
    i = -1;
    while (str[j] && str[j] != '=')
        j++;
    // printf("ALRDY COUNT TILL =: %d\n", j);
    while (data->export[++i])
    {
        if (!ft_strncmp(str, data->export[i], j + 1)
            && data->export[i][j] == '=')
            return (i);
            // return (printf("ALRDY THERE %s\n", str), i);
    }
    return (-1);
    // return (printf("NOT ALRDY THERE %s\n", str), -1);
}

int is_it_last(t_pipex *data, int index_1, int index_2, int i)
{
    int j;
    int count;
    int check;

    count = 0;
    while (data->lines[index_1]->ops[index_2][i][count] && data->lines[index_1]->ops[index_2][i][count] != '=')
        count++;
    // printf("COUNT TILL =: %d\n", count);
    j = -1;
    check = 0;
    while (data->lines[index_1]->ops[index_2][++j])
    {
        // printf("CHECK LAST\n");
        if (!ft_strncmp(data->lines[index_1]->ops[index_2][j], data->lines[index_1]->ops[index_2][i], count + 1)
            && data->lines[index_1]->ops[index_2][j][count] == '=')
            check = j;
    }
    if (check == i)
        return (1);
        // return (printf("ITS LAST %s\n", data->lines[index_1]->ops[index_2][i]), 1);
    return (0);
    // return (printf("ITS NOT LAST %s\n", data->lines[index_1]->ops[index_2][i]), 0);
}

void export_env(t_pipex *data, int index_1, int index_2, int count)
{
    int i;
    int rand;
    char **buf;

    buf = malloc_export_env(data, count);
    rand = 0;
    i = -1;
    data->buf_str = NULL;
    while (data->lines[index_1]->ops[index_2][++i + 1])
    {
        if (rand != (INT_MAX / data->lines[index_1]->ops[index_2][i + 1][ft_strlen(data->lines[index_1]->ops[index_2][i + 1]) - 1]) % (env_count(data) + 1))
            rand = (INT_MAX / data->lines[index_1]->ops[index_2][i + 1][ft_strlen(data->lines[index_1]->ops[index_2][i + 1]) - 1]) % (env_count(data) + 1);
        else 
            rand = ((data->lines[index_1]->ops[index_2][i + 1][0] / data->lines[index_1]->ops[index_2][i + 1][ft_strlen(data->lines[index_1]->ops[index_2][i + 1]) - 1]) - 1) % (count - 1);
        if (already_there(data, data->lines[index_1]->ops[index_2][i + 1]) != -1 && is_it_last(data, index_1, index_2, i + 1))
        {
            data->buf_str = data->cur_env[already_there(data, data->lines[index_1]->ops[index_2][i + 1])];
            data->cur_env[already_there(data, data->lines[index_1]->ops[index_2][i + 1])] = ft_strdup(data->lines[index_1]->ops[index_2][i + 1]);
            free_str(&data->buf_str);
        }
        else if (is_it_last(data, index_1, index_2, i + 1))
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
    int count;

    new = NULL;
    count = 0;
    while (str[++i])
    {
        count++;
        if (!track && str[i] == '=' && str[i + 1])
            track = 1;
        if (str[i] == 34)
            count++;
    }
    if (!track)
        return (ft_strdup(str));
    else if (track == 1)
    // printf("STR: %s | COUNT: %d\n", str, count);
        new = ft_calloc(sizeof(char), (count + 2 + 1));
    if (!new)   
        return (error_code(data), NULL);
    new[count + 2] = 0;
    i = -1;
    while (str[++i] && (i == 0 || (str[i - 1] != '=')))
        new[i] = str[i];
    new[i--] = 34;
    count = 0;
    while (str[++i])
    {
        if (str[i] == 34)
        {
            new[i + 1 + count++] = 92;
        } 
        new[i + 1 + count] = str[i];
    }
    new[i + 1 + count] = 34;
    return (new);
}

char **malloc_arr(t_pipex *data, int size)
{
    char **arr;

    arr = ft_calloc(sizeof(char *), (size + 1));
    if (!arr)
        return (perror("malloc failed"), error_code(data), NULL);
    arr[size] = NULL;
    return (arr);
}

void    update_export(t_pipex *data, int index_1, int index_2, int count)
{
    int i;
    int j;

    i = 0;
    // printf("UPDATE EXPORT\n");
    data->buf_str = NULL;
    while (data->export[i])
        i++;
    data->buf_array = malloc_arr(data, count + i);
    count = i;
    while (--i >= 0)
        data->buf_array[i] = ft_strdup(data->export[i]); 
    j = -1;
    // printf("COUNT: %d | %s\n", count, data->buf_array[count - 1]);
    while (data->lines[index_1]->ops[index_2][1 + ++j])
    {
        // printf("CHECK FOR: %s\n", data->lines[index_1]->ops[index_2][1 + j]);
        if (already_there_2(data, data->lines[index_1]->ops[index_2][1 + j]) != -1 && is_it_last(data, index_1, index_2, 1 + j))
        {
            // printf("TRUE: \n");
            data->buf_str = data->buf_array[already_there_2(data, data->lines[index_1]->ops[index_2][1 + j])];
            // printf("BUF: STR: %s\n", data->buf_str);
            data->buf_array[already_there_2(data, data->lines[index_1]->ops[index_2][1 + j])] = ft_strdup(data->lines[index_1]->ops[index_2][1 + j]);
            free_str(&data->buf_str);
        }
        else if (is_it_last(data, index_1, index_2, 1 + j))
            data->buf_array[count++] = malloc_cpy_export(data, data->lines[index_1]->ops[index_2][1 + j], 0, -1);
            // data->buf_array[count++] = ft_strdup(data->lines[index_1]->ops[index_2][1 + j]);
    }
    free_list(data->export);
    data->export = data->buf_array;
}

int no_identifier(char c)
{
    if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57) || (c == '_'))
        return (0);
    return (1);
}

// void    export_update_2(t_pipex *data, int index_1, int index_2, int i)
// {
//     char **arr;
//     int count;

//     arr = malloc
// }
void    export_update(t_pipex *data, int index_1, int index_2, int i)
{
    int j;
    int count;
    int count_export;

    count = 0;
    count_export = 0;
    while (data->lines[index_1]->ops[index_2][1 + ++i])
    {
        j = -1;
        while (data->lines[index_1]->ops[index_2][1 + i][++j] && data->lines[index_1]->ops[index_2][1 + i][j] != '=')
        {
            if (j == 0 && !((data->lines[index_1]->ops[index_2][1 + i][j] >= 65 && data->lines[index_1]->ops[index_2][1 + i][j] <= 90)
                || (data->lines[index_1]->ops[index_2][1 + i][j] >= 97 && data->lines[index_1]->ops[index_2][1 + i][j] <= 122)
                    || data->lines[index_1]->ops[index_2][1 + i][j] == '_'))
                return (write(2, "bash: export: not a valid identifier\n", 38), exit_child(data, index_1, index_2, 1));
            else if (no_identifier(data->lines[index_1]->ops[index_2][1 + i][j]))
                return (write(2, "bash: export: not a valid identifier\n", 38), exit_child(data, index_1, index_2, 1));
        }
        if (data->lines[index_1]->ops[index_2][1 + i][j] && j == 0)
            return (write(2, "bash: export: not a valid identifier\n", 38), exit_child(data, index_1, index_2, 1));
            // return (write(2, "not a valid identifier\n", 24), data->last_exit_status = 1);
        else if (data->lines[index_1]->ops[index_2][1 + i][j] && already_there(data, data->lines[index_1]->ops[index_2][1 + i]) == -1)
            count++;
        else if (already_there_2(data, data->lines[index_1]->ops[index_2][1 + i]) == -1)
            count_export++;
    }
    // printf("COUNT: %d | count_export: %d\n", count, count_export);
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
            free_str(&key);
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
        free_str(&key);
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
        free_str(&key);
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

void    exit_cmnd_child(t_pipex *data, int index_1, int index_2)
{
    int i;

    i = 0;
    if (data->lines[index_1]->ops[index_2][1])
    {
        if (!only_dec(data->lines[index_1]->ops[index_2][1]))
            return (write(2, "bash: exit: numeric argument required\n", 39), errno = 2, error_code(data));
        i = ft_atoi(data->lines[index_1]->ops[index_2][1]);
        if (i > 255 || i < 0)
            i = i % 256;
        errno = i;
    }
    if (data->lines[index_1]->ops[index_2][2])
       return (write(2, "bash: exit: too many arguments\n", 32), errno = 1, error_code(data));
    error_code(data);
        // return (write(2, "too many arguments\n", 20), data->last_exit_status = 1);
}

void    exit_cmnd(t_pipex *data, int index_1, int index_2)
{
    int i;

    i = 0;
    printf("exit\n");
    if (data->lines[index_1]->ops[index_2][1])
    {
        if (!only_dec(data->lines[index_1]->ops[index_2][1]))
            return (write(2, "bash: exit: numeric argument required\n", 39), errno = 2, error_code(data));
        i = ft_atoi(data->lines[index_1]->ops[index_2][1]);
        if (i > 255 || i < 0)
            i = i % 256;
        errno = i;
    }
    if (data->lines[index_1]->ops[index_2][1] && data->lines[index_1]->ops[index_2][0] && data->lines[index_1]->ops[index_2][2])
       return (write(2, "bash: exit: too many arguments\n", 32), errno = 1, exit_child(data, index_1, index_2, 1));
    else
        error_code(data);
}

void mini_parent(t_pipex *data, int index_1, int index_2)
{
    if (!ft_strncmp(data->lines[index_1]->ops[index_2][0], "cd", 3))
        cd_cmnd(data->lines[index_1]->ops[index_2], data, index_1, index_2);
    else if (!ft_strncmp(data->lines[index_1]->ops[index_2][0], "export", 7) && data->lines[index_1]->ops[index_2][1])
        export_update(data, index_1, index_2, -1);
    else if (!ft_strncmp(data->lines[index_1]->ops[index_2][0], "export", 7) && !data->lines[index_1]->ops[index_2][1])
        export_display(data);
    else if (!ft_strncmp(data->lines[index_1]->ops[index_2][0], "env", 4) && !data->lines[index_1]->ops[index_2][1])
        print_list(data->cur_env);
    else if (!ft_strncmp(data->lines[index_1]->ops[index_2][0], "unset", 6))
        unset_cmnd(data, index_1, index_2, -1);
    else if (!ft_strncmp(data->lines[index_1]->ops[index_2][0], "pwd", 4))
        printf("%s\n", data->cur_path);
    else if (!ft_strncmp(data->lines[index_1]->ops[index_2][0], "exit", 5))
        exit_cmnd(data, index_1, index_2);
    else if (!ft_strncmp(data->lines[index_1]->ops[index_2][0], "ls", 3) && !is_valid_cwd(data))
        printf("\n");
}

void mini_child(t_pipex *data, int index_1, int index_2)
{
    if (!ft_strncmp(data->lines[index_1]->ops[index_2][0], "cd", 3))
        cd_cmnd(data->lines[index_1]->ops[index_2], data, index_1, index_2);
    else if (!ft_strncmp(data->lines[index_1]->ops[index_2][0], "export", 7) && data->lines[index_1]->ops[index_2][1])
        export_update(data, index_1, index_2, -1);
    else if (!ft_strncmp(data->lines[index_1]->ops[index_2][0], "export", 7) && !data->lines[index_1]->ops[index_2][1])
        export_display(data);
    else if (!ft_strncmp(data->lines[index_1]->ops[index_2][0], "env", 4) && !data->lines[index_1]->ops[index_2][1])
        print_list(data->cur_env);
    else if (!ft_strncmp(data->lines[index_1]->ops[index_2][0], "unset", 6))
        unset_cmnd(data, index_1, index_2, -1);
    else if (!ft_strncmp(data->lines[index_1]->ops[index_2][0], "pwd", 4))
        printf("%s\n", data->cur_path);
    else if (!ft_strncmp(data->lines[index_1]->ops[index_2][0], "exit", 5))
        exit_cmnd_child(data, index_1, index_2);
    else if (!ft_strncmp(data->lines[index_1]->ops[index_2][0], "ls", 3) && !is_valid_cwd(data))
        printf("\n");
}
