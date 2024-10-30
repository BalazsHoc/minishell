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

char	*handle_parent(int *fd, int fd_2, char *input)
{
	close(fd[0]);
	close(fd_2);
	if (!input)
	{
		// if (write(fd[1], NULL, 0) == -1)
		// {
		// 	perror("write2:");
		// 	free_str(input);
		// 	close(fd[1]);
		// 	exit(EXIT_FAILURE);
		// }
	}
	else
	{
		if (write(fd[1], input, ft_strlen(input)) == -1)
		{
			perror("ERROR: write:");
			free_str(input);
			close(fd[1]);
			exit(EXIT_FAILURE);
		}
	}
	close(fd[1]);
	wait(NULL);
	return (free_str(input), input = file_read(".txt"), unlink(".txt"), input);
}

void	handle_child(int *fd, int fd_2, t_pipex *data, int index, char **env)
{
	close(fd[1]);
    if (data->input)
    {
        if (dup2(fd[0], STDIN_FILENO) == -1)
        {
            perror("ERROR: dup2 stdin");
            free_struct(data);
            close(fd[0]);
            close(fd_2);
            exit(EXIT_FAILURE);
        }
    }
    close(fd[0]);
	printf("PATH: %s | %s\n", data->paths[index], data->ops[index][0]);
	if (dup2(fd_2, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		free_struct(data);
		close(fd_2);                
		exit(EXIT_FAILURE);
	}
	close(fd_2);
	execve(data->paths[index], data->ops[index], env);
	perror("execve");
	free_struct(data);
	exit(EXIT_FAILURE);
}

char	*exec_cmnd(t_pipex *data, int index, char **env)
{
    int pid;
    int fd[2];
    int tmp_fd;

	tmp_fd = open(".txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (tmp_fd == -1)
		return (free_struct(data), perror("open tmpfile:"), NULL);
	if (pipe(fd) == -1)
	    error_code(data, data->input, 1, errno);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		close(tmp_fd);
		close(fd[0]);
		close(fd[1]);
		free_struct(data);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
		handle_child(fd, tmp_fd, data, index, env);
	else
		data->input= handle_parent(fd, tmp_fd, data->input);
	return (data->input);
}

