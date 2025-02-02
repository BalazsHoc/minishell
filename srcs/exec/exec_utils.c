#include "../../minishell.h"

int	check_here_doc(t_pipex *data, int index_1, int index_2)
{
	if ((is_red_inline(data, index_1, index_2) != -1
			&& !data->l[index_1]->red_cmnd[index_2][
			is_red_inline(data, index_1, index_2)]
		&& !ft_strncmp(data->l[index_1]->cmnds[index_2][
			is_red_inline(data, index_1, index_2)], "<<", 3)))
		return (1);
	return (0);
}

int	is_in_inline(t_pipex *data, int index_1, int index_2)
{
	int	i;
	int	check;

	i = -1;
	check = -1;
	while (data->l[index_1]->cmnds[index_2]
		&& data->l[index_1]->cmnds[index_2][++i])
	{
		if (!ft_strncmp(data->l[index_1]->cmnds[index_2][i], "<", 2))
			check = i;
	}
	return (check);
}

int	open_this_read(t_pipex *data, char *str)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		error_code(data);
	}
	return (fd);
}

int	open_this_write(t_pipex *data, char *str)
{
	int	fd;

	fd = open(str, O_WRONLY);
	if (fd == -1)
	{
		perror("open");
		error_code(data);
	}
	return (fd);
}
