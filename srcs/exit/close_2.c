#include "../../minishell.h"

void	close_children_pipes(t_pipex *data, int index_1, int index_2)
{
	close_pipes_array(data, index_1);
	close_pipes(data, index_1, index_2);
	close_pipe(data, &data->fd_in);
}

void	close_pipes(t_pipex *data, int index_1, int index_2)
{
	close_pipe(data, &data->l[index_1]->fd_infiles[index_2]);
	close_pipe(data, &data->l[index_1]->fd_outfiles[index_2]);
}

void	close_pipes_array(t_pipex *data, int index_1)
{
	int	i;

	i = -1;
	while (++i < data->l[index_1]->cmnd_count)
	{
		if (data->l[index_1]->pipes[i][0] > 0)
			close_pipe(data, &data->l[index_1]->pipes[i][0]);
		if (data->l[index_1]->pipes[i][1] > 0)
			close_pipe(data, &data->l[index_1]->pipes[i][1]);
		if (data->l[index_1]->buf_pipes[i][0] > 0)
			close_pipe(data, &data->l[index_1]->buf_pipes[i][0]);
		if (data->l[index_1]->buf_pipes[i][1] > 0)
			close_pipe(data, &data->l[index_1]->buf_pipes[i][1]);
	}
}

void	close_children_pipe(t_pipex *data, int *fd)
{
	if (*fd >= 0 && close(*fd) == -1)
	{
		perror("close");
		error_code(data);
	}
	*fd = -1;
}

void	close_pipe(t_pipex *data, int *fd)
{
	if (*fd > 0 && close(*fd) == -1)
	{
		perror("close");
		error_code(data);
	}
	*fd = -1;
}
