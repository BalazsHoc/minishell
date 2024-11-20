#include "minishell.h"

char *join_this(char *s1, char *s2)
{
    int i;
    int j;
    char *new;

    i = 0;
    j = 0;
    if (!s2)
        return (free_str(s1), NULL);
    while (s1 && s1[i])
        i++;
    while (s2 && s2[j])
        j++;
    if (i + j == 0)
        return (NULL);
    new = malloc(sizeof(char) * (i + j + 1));
    if (!new)
        return (free_str(s1), NULL);
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
    free_str(s1);
    return (new);
}

char    *file_read(char *file)
{
    int fd;
    char *content;
    char *buf;

    fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		if (errno == 2)
			printf("zsh: no such file or directory: %s\n", file);
		return (NULL);
	}

    buf = get_next_line(fd, 0);
    content = NULL;
    while (buf)
    {
        content = join_this(content, buf);
        free(buf);
        buf = get_next_line(fd, 0);
    }
    close(fd);
	return (content);
}


// char	*handle_parent(t_pipex *data, int index, int (*pipes)[2])
// {
// 	if (data->input)
// 	{
// 		if (write(pipes[index][1], data->input, ft_strlen(data->input)) == -1)
// 		{
// 			perror("ERROR: write:");
// 			free_str(data->input);
// 			exit(EXIT_FAILURE);
// 		}
// 	}
// 	return (free_str(data->input), data->input = file_read(data->tmp), unlink(data->tmp), data->input);
// }

void	handle_child(t_pipex *data, int index, int (*pipes)[2], int cmnd_count)
{
    if (index > 0)
    {
        if (dup2(pipes[index - 1][0], STDIN_FILENO) == -1)
        {
            perror("ERROR: dup2 stdin");
            free_struct(data);
            exit(EXIT_FAILURE);
        }
        // close(pipes[index - 1][0]);
    }
	printf("PATH: %s | %s\n", data->paths[index], data->ops[index][0]);
	if (data->fd == -2 && index < cmnd_count - 1)
    {
        if (dup2(pipes[index][1], STDOUT_FILENO) == -1)
        {
            perror("dup2");
            free_struct(data);
            exit(EXIT_FAILURE);
        }
        // close(pipes[index][1]);
    }
	else if (data->fd != -2)
    {
        if (dup2(data->fd, STDOUT_FILENO) == -1)
        {
            perror("dup2");
            free_struct(data);
            exit(EXIT_FAILURE);
        }
    }
    for (int j = 0; j < cmnd_count - 1; j++) {
        close(pipes[j][0]);
        close(pipes[j][1]);
    }
	execve(data->paths[index], data->ops[index], NULL);
	perror("execve");
	free_struct(data);
	exit(EXIT_FAILURE);
}

void	handle_pwd_tmp(t_pipex *data, int index)
{
	while (!is_valid_cwd(data))
		chdir("..");
	data->tmp = create_tmp(data, index, "tmp_", 0);
}

// void exec_cmnd(t_pipex *data, int index)
// {
//     int pid;
//     int fd[2];
//     int tmp_fd;

// 	// we cannot use tmp if: we dont have a valid pwd or we create the tmp where was the last valid pwd
// 	// also the tmp cannot be any filename.. we have to know that this filename does not exist already inside the folder
// 	handle_pwd_tmp(data, index);
// 	tmp_fd = open(data->tmp, O_WRONLY | O_CREAT | O_TRUNC, 0666);
// 	if (tmp_fd == -1)
// 	{
// 		free_struct(data);
// 		perror("open tmpfile:");
// 	}
// 	if (pipe(fd) == -1)
// 	    error_code(data, NULL, 1, errno);
// 	pid = fork();
// 	if (pid < 0)
// 	{
// 		perror("fork");
// 		close(tmp_fd);
// 		close(fd[0]);
// 		close(fd[1]);
// 		free_struct(data);
// 		exit(EXIT_FAILURE);
// 	}
// 	else if (pid == 0)
// 		handle_child(fd, tmp_fd, data, index);
// 	else
// 		data->input= handle_parent(fd, tmp_fd, data);
// 	chdir(data->cur_path);
// }

// void pre_exec(t_pipex *data, int index)
// {
// 	int pid;

// 	pid = fork();
// 	if (pid < 0)
// 	{
// 		perror("fork");
// 		free_struct(data);
// 		exit(EXIT_FAILURE);
// 	}
// 	else if (pid == 0)
// 	{
// 		exec_cmnd(data, index);
// 		exit(0);
// 	}
// }

// void handle_child(int **pipes, t_pipex *data, int index, int cmnd_count)
// {
// 	if (index > 0)
// 	{
// 		dup2(pipes[index - 1][0], STDIN_FILENO);
// 		close(pipes[index - 1][0]);
// 	}
// 	if (index < cmnd_count -1 )
// 	{
// 		dup2(pipes[index][1], STDOUT_FILENO);
// 		close(pipes[index][1]);
// 	}
// 	execve(data->paths[index], data->ops[index], NULL);
// 	perror("execve");
// 	exit(1);
// }


// void exec_cmnd(t_pipex *data, int index, int cmnd_count, int (*pipes)[2])
// {
//     int pid;
//     // int tmp_fd;

// 	// // we cannot use tmp if: we dont have a valid pwd or we create the tmp where was the last valid pwd
// 	// // also the tmp cannot be any filename.. we have to know that this filename does not exist already inside the folder
// 	// handle_pwd_tmp(data, index);
// 	// tmp_fd = open(data->tmp, O_WRONLY | O_CREAT | O_TRUNC, 0666);
// 	// if (tmp_fd == -1)
// 	// {
// 	// 	free_struct(data);
// 	// 	perror("open tmpfile:");
// 	// }
// 	pid = fork();
// 	if (pid < 0)
// 	{
// 		perror("fork");
// 		free_struct(data);
// 		exit(EXIT_FAILURE);
// 	}
// 	else if (pid == 0)
// 	{
// 		if (index > 0)
// 		{
// 			dup2(pipes[index - 1][0], STDIN_FILENO);
// 			close(pipes[index - 1][0]);
// 		}
// 		if (index < cmnd_count -1 )
// 		{
// 			dup2(pipes[index][1], STDOUT_FILENO);
// 			close(pipes[index][1]);
// 		}
//         for (int j = 0; j < cmnd_count - 1; j++) {
//             close(pipes[j][0]);
//             close(pipes[j][1]);
//         }
// 		execve(data->paths[index], data->ops[index], NULL);
// 		perror("execve");
// 			exit(1);
// 	}
// }

void exec_cmnd(t_pipex *data, int index, int cmnd_count, int (*pipes)[2])
{
    int pid;
    // int tmp_fd;

	// we cannot use tmp if: we dont have a valid pwd or we create the tmp where was the last valid pwd
	// also the tmp cannot be any filename.. we have to know that this filename does not exist already inside the folder
	// handle_pwd_tmp(data, index);
    // if (data->fd == -2)
	    // tmp_fd = open(data->tmp, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	// if (tmp_fd == -1)
	// {
	// 	free_struct(data);
	// 	perror("open tmpfile:");
	// }
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		// close(tmp_fd);
		free_struct(data);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
		handle_child(data, index, pipes, cmnd_count);
	// else
		// data->input = handle_parent(data, index, pipes);
	chdir(data->cur_path);
}