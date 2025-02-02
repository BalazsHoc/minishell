#include "../../../minishell.h"

int	first_invalid_in(t_pipex *data, int index_1, int index_2)
{
	int	i;
	int	fd;

	i = -1;
	fd = -1;
	while (data->l[index_1]->cmnds[index_2][++i])
	{
		if (!ft_strncmp(data->l[index_1]->cmnds[index_2][i], "<", 2)
			&& data->l[index_1]->cmnds[index_2][i + 1]
			&& data->l[index_1]->red_cmnd[index_2][i] == 0)
		{
			close_pipe(data, &fd);
			fd = open(data->l[index_1]->cmnds[index_2][i + 1], O_RDONLY);
			if (fd == -1)
				return (i + 1);
		}
	}
	close_pipe(data, &fd);
	return (0);
}

int	first_invalid_out(t_pipex *data, int index_1, int index_2)
{
	int	i;
	int	fd;

	i = -1;
	fd = -1;
	while (data->l[index_1]->cmnds[index_2][++i])
	{
		if ((!ft_strncmp(data->l[index_1]->cmnds[index_2][i], ">>", 3)
			|| !ft_strncmp(data->l[index_1]->cmnds[index_2][i], ">", 2))
			&& data->l[index_1]->cmnds[index_2][i + 1]
				&& data->l[index_1]->red_cmnd[index_2][i] == 0)
		{
			close_pipe(data, &fd);
			fd = open(data->l[index_1]->cmnds[index_2][i + 1],
					O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
				return (i + 1);
		}
	}
	close_pipe(data, &fd);
	return (i);
}

int	open_out_util_1(t_pipex *data, int index_1, int index_2)
{
	if (is_valid_in(data, index_1, index_2) == -1
		&& first_invalid_in(data, index_1, index_2)
		< first_invalid_out(data, index_1, index_2))
		return (1);
	return (0);
}

void	open_out_util_2(t_pipex *data, int index_1, int index_2, int i)
{
	printf("bash: %s: %s\n", data->l[index_1]->cmnds[index_2][i + 1],
		strerror(errno));
	exit_child(data, index_1, index_2, 1);
}

int	open_out(t_pipex *data, int index_1, int index_2)
{
	int	i;
	int	fd;

	i = -1;
	fd = -1;
	if (open_out_util_1(data, index_1, index_2))
		return (-1);
	while (data->l[index_1]->cmnds[index_2][++i])
	{
		if ((!ft_strncmp(data->l[index_1]->cmnds[index_2][i], ">>", 3)
			|| !ft_strncmp(data->l[index_1]->cmnds[index_2][i], ">", 2))
				&& data->l[index_1]->red_cmnd[index_2][i] == 0)
		{
			close_pipe(data, &fd);
			if (!ft_strncmp(data->l[index_1]->cmnds[index_2][i], ">>", 3))
				fd = open(data->l[index_1]->cmnds[index_2][i + 1],
						O_WRONLY | O_CREAT | O_APPEND, 0644);
			else
				fd = open(data->l[index_1]->cmnds[index_2][i + 1],
						O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				return (open_out_util_2(data, index_1, index_2, i), -1);
		}
	}
	return (fd);
}
