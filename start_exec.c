#include "minishell.h"

int free_this(char *s)
{
    if (s)
        free(s);
    return (1);
}

int is_red_inline(t_pipex *data, int index_1, int index_2)
{
    int i;
    int check;

    i = -1;
    check = -1;
    while (data->lines[index_1]->cmnds[index_2] && data->lines[index_1]->cmnds[index_2][++i])
    {
        if (!ft_strncmp(data->lines[index_1]->cmnds[index_2][i], "<", 2))
            check = i;
        if (!ft_strncmp(data->lines[index_1]->cmnds[index_2][i], "<<", 3))
            check = i;
    }
    return (check);
}

int is_in_inline(t_pipex *data, int index_1, int index_2)
{// is  a single redirection in the line? 
    int i;
    int check;

    i = -1;
    check = -1;
    while (data->lines[index_1]->cmnds[index_2] && data->lines[index_1]->cmnds[index_2][++i])
    {
        if (!ft_strncmp(data->lines[index_1]->cmnds[index_2][i], "<", 2))
            check = i;
    }
    return (check);
}

char *replace_nl(char *str)
{
    int i;

    i = -1;
    while (str[++i])
    {
        if (str[i] == '\n')
            str[i] = 0;
    }
    return (str);
}

int is_valid_in(t_pipex *data, int index_1, int index_2)
{
    int i;
    int fd;
    int check;

    i = -1;
    fd = -1;
    check = 0;
    while (data->lines[index_1]->cmnds[index_2][++i])
    {
        if (!ft_strncmp(data->lines[index_1]->cmnds[index_2][i], "<", 2) && !data->lines[index_1]->red_cmnd[index_2][i] && data->lines[index_1]->cmnds[index_2][i + 1]
            && data->lines[index_1]->red_cmnd[index_2][i] == 0)
        {
            fd = open(data->lines[index_1]->cmnds[index_2][i + 1], O_RDONLY);
            if (fd == -1)
                return (-1);
            check = i + 1;
            close_pipe(data, &fd);
        }
    }
    return (check);
}

int first_invalid_in(t_pipex *data, int index_1, int index_2)
{
    int i;
    int fd;

    i = -1;
    fd = -1;
    while (data->lines[index_1]->cmnds[index_2][++i])
    {
        if (!ft_strncmp(data->lines[index_1]->cmnds[index_2][i], "<", 2) && data->lines[index_1]->cmnds[index_2][i + 1]
            && data->lines[index_1]->red_cmnd[index_2][i] == 0)
        {
            close_pipe(data, &fd);
            fd = open(data->lines[index_1]->cmnds[index_2][i + 1], O_RDONLY);
            if (fd == -1)
                return (i + 1);
        }
    }
    close_pipe(data, &fd);
    return (0);
}

int first_invalid_out(t_pipex *data, int index_1, int index_2)
{
    int i;
    int fd;

    i = -1;
    fd = -1;
    while (data->lines[index_1]->cmnds[index_2][++i])
    {
        if ((!ft_strncmp(data->lines[index_1]->cmnds[index_2][i], ">>", 3) || !ft_strncmp(data->lines[index_1]->cmnds[index_2][i], ">", 2))
            && data->lines[index_1]->cmnds[index_2][i + 1] && data->lines[index_1]->red_cmnd[index_2][i] == 0)
        {
            close_pipe(data, &fd);
            fd = open(data->lines[index_1]->cmnds[index_2][i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd == -1)
                return (i + 1);
        }
    }
    close_pipe(data, &fd);
    return (i);
}


int open_out(t_pipex *data, int index_1, int index_2)
{
    int i;
    int fd;

    i = -1;
    fd = -1;
    if (is_valid_in(data, index_1, index_2) == -1 && first_invalid_in(data, index_1, index_2) < first_invalid_out(data, index_1, index_2))
        return (-1);
    while (data->lines[index_1]->cmnds[index_2][++i])
    {
        if ((!ft_strncmp(data->lines[index_1]->cmnds[index_2][i], ">>", 3)
            || !ft_strncmp(data->lines[index_1]->cmnds[index_2][i], ">", 2)) && data->lines[index_1]->red_cmnd[index_2][i] == 0)
            {
                close_pipe(data, &fd);
                if (!ft_strncmp(data->lines[index_1]->cmnds[index_2][i], ">>", 3))
                    fd = open(data->lines[index_1]->cmnds[index_2][i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
                else
                    fd = open(data->lines[index_1]->cmnds[index_2][i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd == -1)
                    return (printf("bash: %s: %s\n", data->lines[index_1]->cmnds[index_2][i + 1], strerror(errno)), exit_child(data, index_1, index_2, 1), -1);
            }
    }
    return (fd);
}


int get_input_2(t_pipex *data, int index_1, int i)
{
    int k;
    int j;
    char *new;

    // printf("START GET INPUT 2\n");
    k = 0;
    j = 2;
    while (data->line[data->here_2 - j] && !is_delim_back(data->line, data->here_2 - j, 0))
        j++;
    // printf("J: %d\n", j);
    // printf("data_here_2: %d | data_here_2_old: %d | J: %d\n", data->here_2, data->here_2_old, (data->here_2 - (j + 1) - data->here_2_old) + 1);
    (void)i;
    // while (data->lines[index_1]->cmnds[data->lines[index_1]->cmnd_count - 1][i])
    //     i++;
    (void)index_1;
    new = ft_calloc(sizeof(char), (((data->here_2 - (j + 1) - data->here_2_old) + 1) + 1), data);
    while (k < (data->here_2 - (j + 1) - data->here_2_old) + 1)
    {
        new[k] = data->line[data->here_2_old + k];
        k++;
    }
    data->lines[index_1]->input[i] = new;
    return (1);
    // data->buf_int = 2;
    // k = data->lines[index_1]->pos_in_line[data->lines[index_1]->cmnd_count - 1][i - 1];
    // i = 0;
    // while (data->line[k + i] != '\n')
    //     i++;
    // k += i + 1;
    // printf("K: %d\n", k);
    // i = 0;
    // while (data->line[data->here_2 - data->buf_int] && data->line[data->here_2 - data->buf_int] != '\n')
    //     data->buf_int++;
    // if (data->line[data->here_2 - data->buf_int] == '\n')
    //     data->buf_int--;
    // printf("BUF INT: %d\n", data->buf_int);
    // while (data->line[k + i] && k + i < data->here_2 - data->buf_int)
    //     i++;
    // // printf("I: %d\n", i);
    // new = ft_calloc(sizeof(char), (i + 1));
    // if (!new)
    //     return (perror("malloc failed!"), error_code(data), NULL);
    // new[i] = 0;
    // i = -1;
    // while (data->line[k + ++i] && k + i < data->here_2 - data->buf_int)
    //     new[i] = data->line[k + i];
    // data->buf_int = 0;
    // printf("NEW GET INPUT 2: %s\n", new);
}

int last_one(char **arr)
{
    int i;

    i = 0;
    while (arr[i])
        i++;
    if (i > 0)
        return (i - 1);
    return (0);
}

int find_first_here_doc(t_pipex *data, int index_1, int *index_2)
{
    int i;
    int j;
    int check;

    i = *index_2;
    check = -1;
    i = -1;
    while (check == -1 && data->lines[index_1]->cmnds[++i])
    {
        j = -1;
        while (data->lines[index_1]->cmnds[i][++j])
        {
            if (!ft_strncmp(data->lines[index_1]->cmnds[i][j], "<<", 3) && !data->lines[index_1]->red_cmnd[i][j])
            {
                check = j;
                break;
            }
        }
        j = 0;
    }
    return (check);
}

void set_data_here_2(t_pipex *data, int index_1)
{
    int i;
    int j;
    int check;

    i = -1;
    check = 0;
    // printf("HERE HRE EHERE %d\n",data->lines[index_1]->cmnd_count);
    while (!check && data->lines[index_1]->cmnds[++i] && data->lines[index_1]->cmnds[i][0] && data->lines[index_1]->cmnds[i][0][0] && data->lines[index_1]->cmnds[i][0][1] && !is_quote_one(data->lines[index_1]->cmnds[i][0][0]) && !is_quote_one(data->lines[index_1]->cmnds[i][0][1]))
    {
        j = -1;
        while (data->lines[index_1]->cmnds[i][++j])
        {
            if (!ft_strncmp(data->lines[index_1]->cmnds[i][j], "<<", 3) && !data->lines[index_1]->red_cmnd[i][j])
            {
                check = j;
                break;
            }
        }
        j = 0;
    }
    if (!check && data->lines[index_1]->cmnds[0][0][0])
    // if (!check && printf("PENIS6\n") && data->lines[index_1]->cmnds[0][0][0])
    {
        i = 0;
        while (!(is_quote_one(data->lines[index_1]->cmnds[0][0][0]) && is_quote_one(data->lines[index_1]->cmnds[0][0][1] == 34)) && data->line[data->lines[index_1]->pos_in_line[data->lines[index_1]->cmnd_count - 1][last_one(data->lines[index_1]->cmnds[data->lines[index_1]->cmnd_count - 1])] + i] 
            && data->line[data->lines[index_1]->pos_in_line[data->lines[index_1]->cmnd_count - 1][last_one(data->lines[index_1]->cmnds[data->lines[index_1]->cmnd_count - 1])] + i] != '\n')
        // while (!(printf("HI\n") && is_quote_one(data->lines[index_1]->cmnds[0][0][0]) && printf("PENIS2\n") && is_quote_one(data->lines[index_1]->cmnds[0][0][1] == 34)) && printf("PENIS2\n") && data->line[data->lines[index_1]->pos_in_line[data->lines[index_1]->cmnd_count - 1][last_one(data->lines[index_1]->cmnds[data->lines[index_1]->cmnd_count - 1])] + i] 
        //     && printf("PENIS3\n") && data->line[data->lines[index_1]->pos_in_line[data->lines[index_1]->cmnd_count - 1][last_one(data->lines[index_1]->cmnds[data->lines[index_1]->cmnd_count - 1])] + i] != '\n')
            i++;
        // printf("SET DATA HERE & OLD: I: %d\n", data->lines[index_1]->pos_in_line[data->lines[index_1]->cmnd_count - 1][last_one(data->lines[index_1]->cmnds[data->lines[index_1]->cmnd_count - 1])] + i);
        data->here_2 = data->lines[index_1]->pos_in_line[data->lines[index_1]->cmnd_count - 1][last_one(data->lines[index_1]->cmnds[data->lines[index_1]->cmnd_count - 1])] + i + 1;
        data->here_2_old = data->lines[index_1]->pos_in_line[data->lines[index_1]->cmnd_count - 1][last_one(data->lines[index_1]->cmnds[data->lines[index_1]->cmnd_count - 1])] + i + 1;
    }
    else if (check && data->lines[index_1]->cmnd_count)
    // if (check && printf("SET_DATE_HERE & OLD: CALL FROM FIRST HERE_DOC I: %d | J: %d\n", i, check + 1))
        data->here_2_old = find_key(data, index_1, i, check + 1);
    // else
    // {
    //     i = 0;
    //     while(data->line[i]) 
    //         i++;
    //     data->here_2_old = i - 1;
    // }
}
int check_exec_cmnd_1(t_pipex *data, int index, int i)
{
    if (ft_strncmp(data->lines[index]->paths[i], "pathnfound", 11)
            // && (is_valid_in(data, index, i) - 1 == is_red_inline(data, index, i) ) && data->fd_out >= 0 && data->lines[index]->ops[i][0][0])
            && is_valid_in(data, index, i) >= 0 && data->fd_out >= 0 && data->lines[index]->ops[i][0][0] && data->lines[index]->pipes[i][1] != -1 && data->lines[index]->pipes[i][0] != -1)
        return (1);
    return (0);
}

int is_path(t_pipex *data)
{
	int i;

	i = -1;
	while (data->cur_env[++i])
	{
		if (!ft_strncmp(data->cur_env[i], "PATH=", 5))
            return (1);
	}
    return (0);
}
int check_cmnd_as_dir(t_pipex *data, int index, int i)
{
    char *buf_1;
    char *buf_2;
    int j;

    j = 0;
    buf_1 = NULL;
    buf_2 = NULL;
    while (data->lines[index]->ops[i][0] && data->lines[index]->ops[i][0][j])
        j++;
    if (is_mini_2(data, index, i))
        return (1);
    else if (j > 1 && data->lines[index]->ops[i][0][j - 1] == '/' && one_of_those_3(data->lines[index]->ops[i][0]))
    {
        buf_1 = ft_strdup_2(data, data->lines[index]->ops[i][0]);
        buf_2 = find_path(data, buf_1);
        // printf("BUF_2: %s\n", buf_2);
        if (buf_2)
            return (free_str(&buf_1), free_str(&buf_2), 1);
        return (free_str(&buf_1), free_str(&buf_2), 0);
    }
    return (0);
}

int check_exec_cmnd_2(t_pipex *data, int index, int i)
{
    char *path;

    path = get_path(data);
    if (is_valid_in(data, index, i) == -1 && !data->lines[index]->exit_codes[i])
        return (write(2, "bash: ", 6),
            write(2, data->lines[index]->cmnds[i][first_invalid_in(data, index, i)],
                ft_strlen(data->lines[index]->cmnds[i][first_invalid_in(data, index, i)])), write(2, ": No such file or directory\n", 29), exit_child(data, index, i, 1), 1);
    else if(check_cmnd_as_dir(data, index, i) && !one_of_those(data, index, i) && one_of_those_3(data->lines[index]->ops[i][0]) && !data->lines[index]->exit_codes[i])
        return (write(2, "bash: ", 6),
            write(2, data->lines[index]->ops[i][0], ft_strlen(data->lines[index]->ops[i][0])), write(2, ": Not a directory\n", 19), exit_child(data, index, i, 126), 1);
    else if (((path && !(path[5])) || !path) && !ft_strncmp(data->lines[index]->paths[i], "pathnfound", 11) && !data->lines[index]->exit_codes[i])
        return (write(2, "bash: ", 6),
            write(2, data->lines[index]->ops[i][0],
                ft_strlen(data->lines[index]->ops[i][0])), write(2, ": No such file or directory\n", 29), exit_child(data, index, i, 127), 1);
    return (0);
}


int here_doc(t_pipex *data, int index_1, int index_2)
{
    int i;
    int this;
    char *infile;

    this = 0;
	signal_change(1);
    infile = NULL;
    while (data->lines[index_1]->cmnds[++index_2])
    {
        i = -1;
        // printf("\n\nHERE DOOOOOC %d\n", index_2);
        while (data->lines[index_1]->cmnds[index_2][++i])
        {
            if (!ft_strncmp(data->lines[index_1]->cmnds[index_2][i], "<<", 3) && !data->lines[index_1]->red_cmnd[index_2][i]
            // if (printf("\n0000\n") && !ft_strncmp(data->lines[index_1]->cmnds[index_2][i], "<<", 3) && printf("\n0000\n")
                // && (((!ft_strncmp(data->lines[index_1]->paths[index_2], "pathnfound", 11) || (is_valid_in(data, index_1, index_2) == 0))
                //     && i == is_red_inline(data, index_1, index_2)) || i != is_red_inline(data, index_1, index_2)) 
                && find_key(data, index_1 + this, index_2, i + 1) == data->here_2_old)
            {
                // printf("HEREDOC! %d | I: %d\n", index_2, i);
                infile = get_input(data, index_1, index_2, i);
                if (!infile)
                    break ;
                if (((!ft_strncmp(data->lines[index_1]->paths[index_2], "pathnfound", 11) || (is_valid_in(data, index_1, index_2) == -1))
                    && i == is_red_inline(data, index_1, index_2)) || i != is_red_inline(data, index_1, index_2))
                    free_str(&infile);
                else 
                    data->lines[index_1]->input[index_2] = infile;
                infile = NULL;
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
            // if ((ft_strncmp(data->lines[index_1]->paths[index_2], "pathnfound", 11)
            // && is_valid_in(data, index_1, index_2) && data->fd_out >= 0 && data->lines[index_1]->ops[i][0][0]))
            //     free_str(&infile);  
        }
    }
    return (signal_change(2), 1);
}

void    exec_cmnds(t_pipex *data, int index, int i)
{
    while (data->lines[index]->cmnds[++i])
    {
        data->lines[index]->fd_outfiles[i] = open_out(data, index, i);
        if (check_exec_cmnd_1(data, index, i))
        {
            if (check_here_doc(data, index, i))
            {
                if (data->here_2_old < find_key(data, index, i, is_red_inline(data, index, i) + 1) && get_input_2(data, index, 0))
                    data->here_2_old = find_key(data, index, i, is_red_inline(data, index, i) + 1);
                // else
                //     data->input = get_input(data, index, i, is_red_inline(data, index, i));
            }
            if (!ft_strncmp(data->lines[index]->paths[i], "minicmnds", 10))
                exec_mini(data, index, i);
            else
                exec_cmnd(data, index, i);
        }
        else if (check_exec_cmnd_2(data, index, i))
            continue;
        else if (!ft_strncmp(data->lines[index]->paths[i], "pathnfound", 11)
            && data->lines[index]->ops[i][0] && !data->lines[index]->exit_codes[i] 
            && write(2, data->lines[index]->ops[i][0], ft_strlen(data->lines[index]->ops[i][0])) && write(2, ": command not found\n", 21))
            //  data->lines[index]->ops[i][0]))
            exit_child(data, index, i, 127);
        close_pipes(data, index, i);
    }
}

int bigger_one_2(int i, int j)
{
    if (i > j)
        return (i);
    return (j);
}

int check_key(t_pipex *data, char *cur)
{
    int i;
    int j;
    int k;

    i = -1;
    // printf("CHECK: %s\n", cur);
    k = 0;
    while (cur[k] && is_char(cur[k]))
        k++;
    // printf("K: %d\n", k);
    while (data->cur_env[++i])
    {
        j = 0;
        while (data->cur_env[i][j] && data->cur_env[i][j] != '=')
            j++;
        // printf("J: %d\n", j);
        if (!ft_strncmp(data->cur_env[i], cur, bigger_one_2(j, k)))
            return (j);
            // return (printf("FOUND: WITH J: %d\n", j), j);
    }
    return (k);
}

char *get_val(t_pipex *data, char *cur)
{
    int i;
    int j;
    int k;

    i = -1;
    // printf("CUR: %s\n", cur);
    k = 0;
    while (cur[k] && is_char(cur[k]))
        k++;
    // printf("K: %d\n", k);
    while (data->cur_env[++i])
    {
        j = 0;
        while (data->cur_env[i][j] && data->cur_env[i][j] != '=')
            j++;
        if (!ft_strncmp(data->cur_env[i], cur, bigger_one_2(j, k)))
            return (ft_strdup(data, data->cur_env[i] + j + 1));
    }
    return (NULL);
}

char *ft_strnjoin_start(t_pipex *data, char *s1, char *s2, int size)
{
	char	*joined;
	int	i;
	int_least64_t	j;

	if (s1 == 0 && s2 == 0)
		return (0);
    // printf("FT_START JOIN: %s with %s | SIZE: %d\n", s1, s2, size);
	i = size + ft_strlen(s2);
	joined = ft_calloc(sizeof(char), (i + 1), data);
	i = 0;
	while (s1[i] && i < size)
	{
		joined[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
	{
		joined[i + j] = s2[j];
		j++;
	}
	return (joined);
}

// char *ft_strnjoin_end(t_pipex *data, char *s1, char *s2, int size)
// {
// 	char	*joined;
// 	size_t	i;
// 	size_t	j;

// 	if (s1 == 0 && s2 == 0)
// 		return (0);
// 	i = ft_strlen(s1) + ft_strlen(s2);
// 	joined = ft_calloc(sizeof(char), (i + 1), data);
// 	i = 0;
// 	while (s1[i])
// 	{
// 		joined[i] = s1[i];
// 		i++;
// 	}
// 	j = 0;
// 	while (s2[j])
// 	{
// 		joined[i + j] = s2[j];
// 		j++;
// 	}
// 	return (joined);
// }

char *cut_out_key(t_pipex *data, char *cur, int where, int size)
{
    char *buf_1;
    char *buf_2;
    char *val;

    // printf("where %d | size %d\n", where, size);
    val = get_val(data, cur + where + 1);
    // printf("VAL: %s\n", val);
    // return (NULL);
    buf_1 = ft_strnjoin_start(data, cur, val, where);
    // else
    //     buf_1 = ft_strnjoin_start(data, cur, val, )
    // printf("BUF 1: %s\n", buf_1);
    // if (!val)
    buf_2 = ft_strjoin(buf_1, cur + where + size + 1, data);
        
    // printf("BUF 2: %s\n", buf_2);
    free_str(&cur);
    free_str(&val);
    free_str(&buf_1);
    return (buf_2);
}

void    update_input(t_pipex *data, int index_1, int index_2)
{
    int i;
    char *buf;

    buf = data->lines[index_1]->input[index_2];
    i = -1;
    while (buf[++i])
    {
        // printf("BUF_CUR: %s\n", buf + i);
        if (buf[i] == '$')
        {
            buf = cut_out_key(data, buf, i, check_key(data, buf + i + 1));
            // i += check_key(data, buf + i);
        }
    }
    data->lines[index_1]->input[index_2] = buf;
}

void handle_expansion_here_doc(t_pipex *data, int index_1)
{
    int i;

    i = -1;
    while (++i < data->lines[index_1]->cmnd_count)
    {
        if (data->lines[index_1]->input[i] && !data->lines[index_1]->red_cmnd[i][is_red_inline(data, index_1, i) + 1])
            update_input(data, index_1, i);
    }
}

void start_exec(t_pipex *data, int index, int i, int status)
{
    here_doc(data, index, -1);
    handle_expansion_here_doc(data, index);
    exec_cmnds(data, index, i);
    close_pipes_array(data, index);
    while (++i < data->lines[index]->cmnd_count)
    {
        if (!data->lines[index]->exit_codes[i])
        {
            // printf("waiting..\n");
            waitpid(data->pid[i], &status, 0);
            if (WIFEXITED(status))
            {
                // printf("EXIT STATUS: %d\n", WEXITSTATUS(status));
                data->lines[index]->exit_codes[i] = WEXITSTATUS(status);
				errno = data->lines[index]->exit_codes[i];
            }
        }
    }
    set_data_here_2(data, index);
    data->last_exit_status = data->lines[index]->exit_codes[data->lines[index]->cmnd_count - 1];
    // printf("LAST1: %d\n", data->exit_codes[data->cmnd_count - 1]);
    // exit_child(data, data->cmnd_count - 1, data->exit_codes[data->cmnd_count - 1]);
    // printf("LAST2: %d\n", data->exit_codes[data->cmnd_count - 1]);
}
