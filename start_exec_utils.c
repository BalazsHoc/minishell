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

int change_dir(char **argv, t_pipex *data, char **env)
{
    char    *home_dir;

    home_dir = get_home(data, env);
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
            printf("Penis_Wrong\n");
            return (1);
        }
        printf("Penis_Good\n");
        return (1);
    }
    return (0);
}

// void change_dir(t_pipex *data, int index)
// {
//     if (!ft_strncmp(data->ops[index][0], "cd", 3) && data->ops[index][1])
//     {
//         if (chdir(data->ops[index][1]) == -1)
//         {
//             if (errno == ENOENT)
//                 printf("-bash: cd: %s: No such file or directory\n", data->ops[index][1]);
//             if (errno == ENOTDIR)
//                 printf("-bash: cd: %s: Not a directory\n", data->ops[index][1]);
//             if (errno == EACCES)
//                 printf("-bash: cd: %s: Permission denied\n", data->ops[index][1]);
//             if (errno == ENOMEM)
//                 printf("-bash: cd: Cannot allocate memory\n");
//         }
//     }
// }

// void export_cmnd_set(t_pipex *data, int index)
// {
//     int i;
//     char **new;

//     i = -1;
//     new = malloc(sizeof(char *) * (count_env(data->mini_env) + 2));
//     if (!new)
//         return (printf("malloc fail!\n"), error_code(data, NULL, 1, 0));
//     new[count_env(data->mini_env) + 1] = 0;
//     while (i < count_env)
//     {
//         new[i] = malloc(sizeof(char) * (ft_strlen(data->mini_env[i]) + 1));
// 		if (!new[i])
// 			return (printf("malloc fail!\n"), error_code(data, NULL, 1, 0));
// 		ft_memcpy(new[i], data->mini_env[i], ft_strlen(data->mini_env[i]));
// 		data->mini_env[i][ft_strlen(data->mini_env[i])] = 0;
//     }
//     // if (is_quote_inline(data->ops[index][1]))

//     ft_memcpy(new[i], data->ops[index][1], ft_strlen(data->ops[index][1]));
//     free_list(data->mini_env);
//     data->mini_env = new;
// }

// void    export_cmnd(t_pipex *data, int index)
// {
//     if (!data->ops[index][1])
//         // TODO --> view all exported variables
//         ;
//     if (!ft_strncmp(data->ops[index][1], "-p", 3))
//         // TODO --> view all exported variables on current shell
//         ;
//     if (!ft_strncmp(data->ops[index][1], "-f", 3))
//         // TODO --> names refer to functions
//         ;
//     if (!ft_strncmp(data->ops[index][1], "-n", 3))
//         // TODO --> named variables or functions with -f will no longer be exported
//         ;
//     else if (is_quote_inline(data->ops[index][1]))
//         // TODO --> if there is quote inside the value declaration
//         ;
//     else
//         export_cmnd_set(data, index);
// }

void env_cmnd(t_pipex *data, char **env, int index)
{
    int i;
    int fd;


    i = -1;
    fd = open_out(data, index);
    if (fd == -2)
        fd = 1;
    // printf("FD: %d\n", fd);
    while (env[++i])
    {
        write(fd, env[i], ft_strlen(env[i]));
        write(fd, "\n", 1);
    }
    if (fd > 2)
        close(fd);
}

int mini_commands(t_pipex *data, int *index, char **env)
{
    if (!ft_strncmp(data->ops[*index][0], "cd", 3) && ++(*index))
        change_dir(data->ops[*index - 1], data, env);
    else if (!ft_strncmp(data->ops[*index][0], "env", 4) && !data->cmnds[*index + 1])
        env_cmnd(data, env, ++(*index) - 1);
    // if (!ft_strncmp(data->ops[*index][0], "export", 7) && ++(*index))
    //     export_cmnd(data, *index - 1);
    // printf("hura\n");
    return (1);
}