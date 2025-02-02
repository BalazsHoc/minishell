#include "../../minishell.h"

int	check_open(char *line)
{
	int	open;
	int	i;

	i = -1;
	open = 0;
	while (line[++i])
	{
		if (is_quote_one(line[i]) && !open)
			open = 1;
		else if (is_q_2(line[i]) && !open)
			open = 2;
		else if (((is_quote_one(line[i]) && open == 1)
				|| (is_q_2(line[i]) && open == 2)))
			open = 0;
	}
	return (open);
}

int	syntax_check(t_pipex *data, int i, int count)
{
	int	word;
	int	open;

	word = 0;
	open = 0;
	while (data->line[++i])
	{
		handle_open(data, i, &open);
		if (!open && i == 0 && data->line[0] == '|')
			return (0);
		else if (!open && !is_real_pipe(data->line, i)
			&& !is_space(data->line[i]) && ++word)
			count = 0;
		else if (!open && is_real_pipe(data->line, i))
			count++;
		if (count >= 2)
			return (0);
	}
	return (1);
}

int	check_folder_utils_1(t_pipex *data, int index, int i)
{
	if (!data->l[index]->ops[i][0]
			|| ft_strncmp(data->l[index]->paths[i], "pathnfound", 11)
				|| data->l[index]->exit_codes[i])
		return (1);
	return (0);
}

int	check_folder_utils_2(t_pipex *data, int index, int i, int j)
{
	if (data->l[index]->ops[i][0][j] == '/'
				&& (!check_cmnd_as_dir(data, index, i)
					|| one_of_those(data, index, i)))
		return (1);
	return (0);
}

void	check_folder_utils_3(t_pipex *data, int index, int i)
{
	printf("bash: %s: Is a directory\n", data->l[index]->ops[i][0]);
	exit_child(data, index, i, 126);
}

void	check_folder_utils_4(t_pipex *data, int index, int i)
{
	printf("bash: %s: Permission denied\n", data->l[index]->ops[i][0]);
	exit_child(data, index, i, 126);
}

void	check_folder_utils_5(t_pipex *data, int index, int i)
{
	printf("bash: %s: No such file or directory\n",
		data->l[index]->ops[i][0]);
	exit_child(data, index, i, 127);
}

void	check_folder(t_pipex *data, int index, int i, int j)
{
	DIR	*ptr;

	ptr = NULL;
	while (data->l[index]->cmnds[++i])
	{
		j = -1;
		while (check_folder_utils_1(data, index, i) && i++ != INT_MIN)
		{
			if (!data->l[index]->cmnds[i])
				return ;
		}
		while (data->l[index]->ops[i][0][++j])
		{
			if (check_folder_utils_2(data, index, i, j))
			{
				ptr = opendir(data->l[index]->ops[i][0]);
				if (ptr)
					return (closedir(ptr), check_folder_utils_3(data, index, i));
				else if (errno == EACCES)
					return (check_folder_utils_4(data, index, i));
				else
					return (check_folder_utils_5(data, index, i));
			}
		}
	}
}
