#include "minishell.h"

char *get_input(t_pipex *data, int index_1, int index_2, int index_3)
{
    char    *buf;
    char    *key;
    char    *input;
 
	g_signal = 0;
	key = data->lines[index_1]->cmnds[index_2][index_3 + 1];
	input = NULL;
	buf = readline("> ");
	while (buf && !g_signal && (!ft_strcmp_2(buf, key)))
	{
		if (buf[0] != '\0')
		{
			input = join_this(input, buf, data);
			free_str(&buf);
		}
		buf = readline("> ");
	}
	// printf("%d\n", g_signal);
    if (!input)
        return (free_str(&buf), ft_strdup(data, ""));
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



void print_list(char **arr)
{
    int i;

    i = 0;
    while (arr[i])
        printf("%s\n", arr[i++]);
}

// char    *trim_last(char *old, t_pipex *data)
// {
//     int i;
//     int check;
//     char *new;

//     i = -1;
//     while (old[++i])
//     {
//         if (old[i] == '/')
//             check = i;
//     }
//     new = ft_calloc(sizeof(char), (check + 1), data);
//     i = -1;
//     while (++i < check)
//         new[i] = old[i];
//     free(old);
//     return (new);
// }

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
    char *cur_pwd;

    i = -1;
    buf = NULL;
    cur_pwd = get_pwd(data);
    // if (!ft_strncmp(data->ops[index][1], ".", 2))
    //     return ;
    while (data->cur_env[++i] && i < 100)
    {
        if (!ft_strncmp(data->cur_env[i], "OLDPWD=", 7))
        {
            buf = data->cur_env[i];
            data->cur_env[i] = ft_strjoin("OLDPWD=", cur_pwd + 4, data);
            // printf("OLD: %s\n", getenv("OLDPWD"));
            free(buf);
        }
    }
    buf = ft_calloc(sizeof(char), (BUF_SIZE_ENV * 100) + 1, data);
    getcwd(buf, BUF_SIZE_ENV * 100);
    i = -1;
    // printf("BUF: %s\n", buf);
    if (!buf)
        return (printf("failed getcwd() !\n"), error_code(data));
    while (data->cur_env[++i] && i < 100)
    {
        if (!ft_strncmp(data->cur_env[i], "PWD=", 4))
        {
            if (!ft_strncmp(data->lines[index_1]->ops[index_2][1], ".", 1) && !*buf)
                // || !ft_strncmp(buf, data->cur_path, bigger_one(buf, data->cur_path))))
            {
                free(buf);
                if (cur_pwd[ft_strlen(cur_pwd) - 1] != '/')
                    buf = ft_strjoin("/", data->lines[index_1]->ops[index_2][1], data);
                else
                    buf = ft_strjoin(NULL, data->lines[index_1]->ops[index_2][1], data);
                cur_pwd = ft_strjoin(cur_pwd + 4, buf, data);
                data->cur_env[i] = ft_strjoin("PWD=", cur_pwd, data);
                // data->cur_path = data->cur_env[i] + 4;
                free_str(&cur_pwd);
                // printf("CUR: %s\n", data->cur_path);
            }
            else
            {
                free_str(&data->cur_env[i]);
                data->cur_env[i] = ft_strjoin("PWD=", buf, data);
            }
            // printf("THIS IS NEW PWD: %s\n", data->cur_env[i]);
            free(buf);
        }
    }
}

char    *get_home(t_pipex *data)
{
    int i;

    i = -1;
    while (data->cur_env[++i])
    {
        if (!ft_strncmp(data->cur_env[i], "HOME=", 5))
            return (data->cur_env[i] + 5);
    }
    return (NULL);
}

char *get_old(t_pipex *data, int index_1, int index_2)
{
    int i;

    i = -1;
    while (data->cur_env[++i])
    {
        if (!ft_strncmp(data->cur_env[i], "OLDPWD=", 7) && printf("%s\n", data->cur_env[i] + 7))
            return (data->cur_env[i]);
    }
    return (write(2, "bash: cd: OLDPWD not set\n", 26), exit_child(data, index_1, index_2, 1), NULL);
}

char *get_path(t_pipex *data)
{
    int i;

    i = -1;
    while (data->cur_env[++i])
    {
        if (!ft_strncmp(data->cur_env[i], "PATH=", 5))
            return (data->cur_env[i]);
    }
    return (0);
}

char *get_pwd(t_pipex *data)
{
    int i;

    i = -1;
    while (data->cur_env[++i])
    {
        if (!ft_strncmp(data->cur_env[i], "PWD=", 4))
            return (data->cur_env[i]);
    }
    return (0);
}

void print_cd_err(int errnum, char *str)
{
    write(2, "bash: cd: ", 11);
    write(2, str, ft_strlen(str));
    if (errnum == ENOENT)
        write(2, ": No such file or directory\n", 29);
    else if (errnum == ENOTDIR)
        write(2, ": Not a directory\n", 19);
    else if (errnum == EACCES)
        write(2, ": Permission denied\n", 21);
    else if (errnum == ENOMEM)
        write(2, ": Cannot allocate memory\n", 26);
    else
        write(2, ": failed\n", 10);
}

void update_env_2_continue(t_pipex *data, char *buf_1, char *buf_2)
{
    int i;

    i = -1;
    while (data->cur_env[++i])
    {
        if (!ft_strncmp(data->cur_env[i], "OLDPWD=", 7) && buf_2)
        {
            free_str(&data->cur_env[i]);
            data->cur_env[i] = NULL;
            data->cur_env[i] = buf_2;
        }
        else if (!ft_strncmp(data->cur_env[i], "OLDPWD=", 7) && !buf_2 && buf_1)
        {
            free_str(&data->cur_env[i]);
            data->cur_env[i] = (buf_1);
        }
        else if (!ft_strncmp(data->cur_env[i], "PWD=", 4) && buf_2 && buf_1)
        {
            free_str(&data->cur_env[i]);
            data->cur_env[i] = (buf_1);
        }
    }
}

void update_env_2(t_pipex *data, int index_1, int index_2)
{
    int j;
    char *buf_1;
    char *buf_2;

    buf_1 = NULL;
    buf_2 = NULL;
    data->buf_str = get_old(data, index_1, index_2);
    if (!data->buf_str)
        return ;
    chdir(data->buf_str);
    j = 0;
    while (data->buf_str[j] && data->buf_str[j] != '=')
        j++;
    // printf("%s\n", data->buf_str + j);
    buf_1 = ft_strjoin("PWD", data->buf_str + j, data);
    // printf("BUF 1: %p\n", buf_1);
    data->buf_str = get_pwd(data);
    j = 0;
    while (data->buf_str && data->buf_str[j] && data->buf_str[j] != '=')
        j++;
    if (data->buf_str)
        buf_2 = ft_strjoin("OLDPWD", data->buf_str + j, data);
    // printf("BUF 2: %s\n", buf_2);
    data->buf_str = NULL;
    update_env_2_continue(data, buf_1, buf_2);
}

void cd_cmnd(char **argv, t_pipex *data, int index_1, int index_2)
{
    char    *home_dir;

    if (data->lines[index_1]->ops[index_2][0] && data->lines[index_1]->ops[index_2][1] && data->lines[index_1]->ops[index_2][2])
        return (write(2, "bash: cd: ", 11), write(2, "too many arguments\n", 20), exit_child(data, index_1, index_2, 1));
        // return (write(2, "too many arguments\n", 20), data->last_exit_status = 1);
    home_dir = get_home(data);
    if (!ft_strncmp(argv[1], ".", 2) && home_dir)
        return (update_env(data, index_1, index_2));
    if (!ft_strncmp(argv[1], "-", 2))
        return (update_env_2(data, index_1, index_2));
    if ((!argv[1] || !strncmp(argv[1], "~", 2)))
    {
        if (chdir(home_dir) == -1)
            print_cd_err(errno, argv[1]);
        else
            update_env(data, index_1, index_2);
    }
    else if (argv[1] && chdir(argv[1]) == -1)
        print_cd_err(errno, argv[1]), exit_child(data, index_1, index_2, 1);
        // print_cd_err(argv[1], errno), data->last_exit_status = 1, ;
    else if (argv[1])
        update_env(data, index_1, index_2);
    // printf("PWD: %s\n", getenv("PWD"));
}

int is_valid_cwd(t_pipex *data)
{
    char *buf;

    buf = ft_calloc(sizeof(char), (BUF_SIZE_ENV * 100) + 1, data);
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
    arr = ft_calloc(sizeof(char *), (i + count + 1), data);
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
    int check;

    j = 0;
    i = -1;
    while (str[j] && str[j] != '=')
        j++;
        
    // printf("ALRDY COUNT TILL =: %d\n", j);
    while (data->export[++i])
    {
        check = 0;
        while (data->export[i][check])
            check++;
        if (!ft_strncmp(str, data->export[i], j + 1) || (str[j] == '=' && !ft_strncmp(str, data->export[i], j - 1) && j <= check && data->export[i][j] == 0))
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
        if (!ft_strncmp(data->lines[index_1]->ops[index_2][j], data->lines[index_1]->ops[index_2][i], count + 1))
            check = j;
    }
    if (check == i)
        return (1);
        // return (printf("ITS LAST %s\n", data->lines[index_1]->ops[index_2][i]), 1);
    return (0);
    // return (printf("ITS NOT LAST %s\n", data->lines[index_1]->ops[index_2][i]), 0);
}

int has_equal(char *str)
{
    int i;

    i = 0;
    while (str[i] && str[i] != '=')
        i++;
    if (str[i] == '=')
        return (1);
    return (0);
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
        // if (!ft_strncmp(data->lines[index_1]->ops[index_2][1 + i], "_=", 2))
        if (!has_equal(data->lines[index_1]->ops[index_2][i + 1]))
            continue;
        if (rand != (INT_MAX / data->lines[index_1]->ops[index_2][i + 1][ft_strlen(data->lines[index_1]->ops[index_2][i + 1]) - 1]) % (env_count(data) + 1))
            rand = (INT_MAX / data->lines[index_1]->ops[index_2][i + 1][ft_strlen(data->lines[index_1]->ops[index_2][i + 1]) - 1]) % (env_count(data) + 1);
        else 
            rand = ((data->lines[index_1]->ops[index_2][i + 1][0] / data->lines[index_1]->ops[index_2][i + 1][ft_strlen(data->lines[index_1]->ops[index_2][i + 1]) - 1]) - 1) % (count - 1);
        if (ft_strncmp(data->lines[index_1]->ops[index_2][1 + i], "_=", 2) && already_there(data, data->lines[index_1]->ops[index_2][i + 1]) != -1 && is_it_last(data, index_1, index_2, i + 1))
        {
            data->buf_str = data->cur_env[already_there(data, data->lines[index_1]->ops[index_2][i + 1])];
            data->cur_env[already_there(data, data->lines[index_1]->ops[index_2][i + 1])] = ft_strdup(data, data->lines[index_1]->ops[index_2][i + 1]);
            free_str(&data->buf_str);
        }
        else if (ft_strncmp(data->lines[index_1]->ops[index_2][1 + i], "_=", 2) && is_it_last(data, index_1, index_2, i + 1))
            buf[rand] = ft_strdup(data, data->lines[index_1]->ops[index_2][i + 1]);
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
        return (ft_strdup(data, str));
    else if (track == 1)
        new = ft_calloc(sizeof(char), (count + 2 + 1), data);
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

    arr = ft_calloc(sizeof(char *), (size + 1), data);
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
    // printf("COUNT: %d | I: %d\n", count , i);
    data->buf_array = malloc_arr(data, count + i);
    count = i;  
    while (--i >= 0)
        data->buf_array[i] = ft_strdup(data, data->export[i]); 
    j = -1;
    // printf("COUNT: %d | %s\n", count, data->buf_array[count - 1]);
    while (data->lines[index_1]->ops[index_2][1 + ++j])
    {
        // printf("CHECK FOR: %s\n", data->lines[index_1]->ops[index_2][1 + j]);
        if (ft_strncmp(data->lines[index_1]->ops[index_2][1 + j], "_=", 2) && already_there_2(data, data->lines[index_1]->ops[index_2][1 + j]) != -1 && is_it_last(data, index_1, index_2, 1 + j))
        {
            // printf("TRUE: \n");
            data->buf_str = data->buf_array[already_there_2(data, data->lines[index_1]->ops[index_2][1 + j])];
            // printf("BUF: STR: %s\n", data->buf_str);
            data->buf_array[already_there_2(data, data->lines[index_1]->ops[index_2][1 + j])] = ft_strdup(data, data->lines[index_1]->ops[index_2][1 + j]);
            free_str(&data->buf_str);
        }
        else if ((ft_strlen(data->lines[index_1]->ops[index_2][1 + j]) || ft_strncmp(data->lines[index_1]->ops[index_2][1 + j], "_=", 2)) && is_it_last(data, index_1, index_2, 1 + j))
            data->buf_array[count++] = malloc_cpy_export(data, data->lines[index_1]->ops[index_2][1 + j], 0, -1);
        // printf("NEW: %s\n", data->buf_array[count - 1]);
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
                return (write(2, "bash: export: `", 16), write(2, data->lines[index_1]->ops[index_2][1], ft_strlen(data->lines[index_1]->ops[index_2][1])),
                    write(2, "': not a valid identifier\n", 27), exit_child(data, index_1, index_2, 1));
            else if (no_identifier(data->lines[index_1]->ops[index_2][1 + i][j]))
                return (write(2, "bash: export: `", 16), write(2, data->lines[index_1]->ops[index_2][1], ft_strlen(data->lines[index_1]->ops[index_2][1])),
                    write(2, "': not a valid identifier\n", 27), exit_child(data, index_1, index_2, 1));
        }
        if (data->lines[index_1]->ops[index_2][1 + i][j] && j == 0)
                return (write(2, "bash: export: `", 16), write(2, data->lines[index_1]->ops[index_2][1], ft_strlen(data->lines[index_1]->ops[index_2][1])),
                    write(2, "': not a valid identifier\n", 27), exit_child(data, index_1, index_2, 1));
        else if (data->lines[index_1]->ops[index_2][1 + i][j] && ft_strncmp(data->lines[index_1]->ops[index_2][1 + i], "_=", 2) && already_there(data, data->lines[index_1]->ops[index_2][1 + i]) == -1)
            count++;
        else if (ft_strncmp(data->lines[index_1]->ops[index_2][1 + i], "_=", 2) && already_there_2(data, data->lines[index_1]->ops[index_2][1 + i]) == -1)
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
    key = ft_calloc(sizeof(char), (i + 1), data);
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
            if (ft_strncmp(data->lines[index_1]->ops[index_2][i + 1] , "_", 2)
                && !ft_strncmp(data->lines[index_1]->ops[index_2][i + 1], key, bigger_one(data->lines[index_1]->ops[index_2][i + 1], key)))
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
            if (ft_strncmp(data->lines[index_1]->ops[index_2][i + 1], "_", 2) && !ft_strncmp(data->lines[index_1]->ops[index_2][i + 1], key, bigger_one(data->lines[index_1]->ops[index_2][i + 1], key)))
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
    if (!data->lines[index_1]->ops[index_2][1])
        return (NULL);
    if (count == -1)
        return (NULL);
    return (ft_calloc(sizeof(char *), (count + 1), data));
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
            if (ft_strncmp(data->lines[index_1]->ops[index_2][j + 1] , "_", 2) && !ft_strncmp(data->lines[index_1]->ops[index_2][j + 1], key, bigger_one(data->lines[index_1]->ops[index_2][j + 1], key)))
                check = 1;
        }
        free_str(&key);
        if (!check)
            data->buf_array[data->buf_int++] = data->cur_env[i];
        else if (printf("FREE THIS ONE: %s | %p\n", data->cur_env[i], data->cur_env[i]))
            free_str(&data->cur_env[i]);
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
    while (data->export[++i])
    {
        j = -1;
        check = 0;
        key = key_this(data, data->export[i]);
        while (data->lines[index_1]->ops[index_2][++j + 1])
        {
            if (ft_strncmp(data->lines[index_1]->ops[index_2][j + 1] , "_", 2)
                && !ft_strncmp(data->lines[index_1]->ops[index_2][j + 1], key, bigger_one(data->lines[index_1]->ops[index_2][j + 1], key)))
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
    int check;

    i = 0;
	if (str[0] == '\0')
		return (0);
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\t' || str[i] == '\v')
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
    check = i;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
    if (!str[i] && check < i)
        return (1);
    return (0);
}

int is_overflow_continue(char *str, int sign)
{
    unsigned long long result;
    int i;

    i = 0;
    result = 0;
    while (str[i] >= '0' && str[i] <= '9')
    {
        if ((result > 100000000000000000 && str[i + 1])
            || (result > 922337203685477590)
            || (result == 922337203685477580 && (str[i] == '8' || str[i] == '9') && sign == 1)
            ||  (result == 922337203685477580 && str[i] == '9' && sign == -1))
            return (1);
        result = result * (unsigned long long)10 + (unsigned long long)(str[i] - '0');
        i++;
    }
    // if ((sign == 1 && result >= LLONG_MAX) || (sign == -1 && result > (unsigned long long)LLONG_MAX))
        // return (1);
    return (0);
}

int is_overflow(t_pipex *data, int index_1, int index_2)
{
    int i;
    int sign;
    char *nptr;

    i = 0;
    sign = 1;
    nptr = data->lines[index_1]->ops[index_2][1];
    while (nptr[i] == ' ' || nptr[i] == '\f' || nptr[i] == '\n'
		|| nptr[i] == '\r' || nptr[i] == '\t' || nptr[i] == '\v')
        i++;
    if (nptr[i] == '-' || nptr[i] == '+')
    {
        if (nptr[i] == '-')
            sign *= -1;
		i++;
    }
    while (nptr[i] == '0')
        i++;
    if (ft_strlen(nptr + i) > 19)
        return (1);
    return (is_overflow_continue(nptr + i, sign));
}

void    exit_cmnd(t_pipex *data, int index_1, int index_2)
{
    long long i;

    i = 0;
    printf("exit\n");
    if (data->lines[index_1]->ops[index_2][1])
    {
        if (is_overflow(data, index_1, index_2) || !only_dec(data->lines[index_1]->ops[index_2][1]))
            return (write(2, "bash: exit: ", 13), write(2, data->lines[index_1]->ops[index_2][1], ft_strlen(data->lines[index_1]->ops[index_2][1])), write(2, ": numeric argument required\n", 29), errno = 2, error_code(data));
        i = ft_atoi(data->lines[index_1]->ops[index_2][1]);
        if (i > 255 || i < 0)
            i = i % 256;
        errno = i;
    }
    // printf("LAST EXIT STATUS: %d\n", data->last_exit_status);
    if (data->lines[index_1]->ops[index_2][1] && data->lines[index_1]->ops[index_2][0] && data->lines[index_1]->ops[index_2][2] && data->last_exit_status == 0)
       return (write(2, "bash: exit: too many arguments\n", 32), errno = 1, exit_child(data, index_1, index_2, 1));
    else if (data->lines[index_1]->ops[index_2][1] && data->lines[index_1]->ops[index_2][0] && data->lines[index_1]->ops[index_2][2])
       return (write(2, "bash: exit: too many arguments\n", 32), exit_child(data, index_1, index_2, data->last_exit_status));
    else
        return (errno = data->last_exit_status, error_code(data));
}

void    exit_cmnd_child(t_pipex *data, int index_1, int index_2)
{
    long long i;

    i = 0;
    if (data->lines[index_1]->ops[index_2][1])
    {
        i = ft_atoi(data->lines[index_1]->ops[index_2][1]);
        if (is_overflow(data, index_1, index_2) || !only_dec(data->lines[index_1]->ops[index_2][1]))
            return (write(2, "bash: exit: ", 13), write(2, data->lines[index_1]->ops[index_2][1], ft_strlen(data->lines[index_1]->ops[index_2][1])), write(2, ": numeric argument required\n", 29), errno = 2, error_code(data));
        if (i > 255 || i < 0)
            i = i % 256;
        errno = i;
    }
    if (data->lines[index_1]->ops[index_2][2])
       return (write(2, "bash: exit: too many arguments\n", 32), errno = 1, error_code(data));
    return (errno = data->last_exit_status, error_code(data));
}

void print_update_env(t_pipex *data, int index_1, int index_2)
{
    int i;
    char *buf_1;
    char *buf_2;

    i = -1;
    buf_1 = NULL;
    buf_2 = NULL;
    while (data->cur_env[++i])
    {
        if (!ft_strncmp(data->cur_env[i], "_=", 2))
        {
            buf_1 = data->cur_env[i];
            if (!ft_strncmp(data->lines[index_1]->ops[index_2][0], "env", 4))
                buf_2 = ft_strdup(data, "/usr/bin/env");
            else 
                buf_2 = ft_strdup(data, data->lines[index_1]->ops[index_2][0]);
            data->cur_env[i] = ft_strjoin("_=", buf_2, data);
            free_str(&buf_1);
            free_str(&buf_2);
            break;
        }
    }
    print_list(data->cur_env);
}

void mini_parent(t_pipex *data, int index_1, int index_2)
{
    if (!ft_strncmp(data->lines[index_1]->ops[index_2][0], "cd", 3))
        cd_cmnd(data->lines[index_1]->ops[index_2], data, index_1, index_2);
    else if (!ft_strncmp(data->lines[index_1]->ops[index_2][0], "export", 7) && data->lines[index_1]->ops[index_2][1])
        export_update(data, index_1, index_2, -1);
    else if (!ft_strncmp(data->lines[index_1]->ops[index_2][0], "export", 7) && !data->lines[index_1]->ops[index_2][1])
        export_display(data);
    else if (!ft_strncmp(data->lines[index_1]->ops[index_2][0], "env", 4) || !ft_strncmp(data->lines[index_1]->ops[index_2][0], "/bin/env", 9) || !ft_strncmp(data->lines[index_1]->ops[index_2][0], "/usr/bin/env", 13))
        print_update_env(data, index_1, index_2);
    else if (!ft_strncmp(data->lines[index_1]->ops[index_2][0], "unset", 6))
        unset_cmnd(data, index_1, index_2, -1);
    else if (!ft_strncmp(data->lines[index_1]->ops[index_2][0], "pwd", 4) || !ft_strncmp(data->lines[index_1]->ops[index_2][0], "/bin/pwd", 9) || !ft_strncmp(data->lines[index_1]->ops[index_2][0], "/usr/bin/pwd", 13))
        printf("%s\n", get_pwd(data) + 5);
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
    else if (!ft_strncmp(data->lines[index_1]->ops[index_2][0], "env", 4) || !ft_strncmp(data->lines[index_1]->ops[index_2][0], "/bin/env", 9) || !ft_strncmp(data->lines[index_1]->ops[index_2][0], "/usr/bin/env", 13))
        print_update_env(data, index_1, index_2);
    else if (!ft_strncmp(data->lines[index_1]->ops[index_2][0], "unset", 6))
        unset_cmnd(data, index_1, index_2, -1);
    else if (!ft_strncmp(data->lines[index_1]->ops[index_2][0], "pwd", 4) || !ft_strncmp(data->lines[index_1]->ops[index_2][0], "/bin/pwd", 9) || !ft_strncmp(data->lines[index_1]->ops[index_2][0], "/usr/bin/pwd", 13))
        printf("%s\n", get_pwd(data) + 5);
    else if (!ft_strncmp(data->lines[index_1]->ops[index_2][0], "exit", 5))
        exit_cmnd_child(data, index_1, index_2);
    else if (!ft_strncmp(data->lines[index_1]->ops[index_2][0], "ls", 3) && !is_valid_cwd(data))
        printf("\n");
}
