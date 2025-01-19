#include "../../minishell.h"

void set_cur_path(t_pipex *data)
{
	int i;
	int check;

	check = 0;
	i = -1;
	while (data->cur_env[++i])
	{
		if (!check && !ft_strncmp(data->cur_env[i], "PWD=", 4))
		{
			data->cur_path = data->cur_env[i] + 4;
			check = 1;
		}
	}
}

int is_mini(t_pipex *data, int index_1, int index_2)
{
	if (data->lines[index_1]->ops[index_2] && data->lines[index_1]->ops[index_2][0] && (!ft_strncmp(data->lines[index_1]->ops[index_2][0], "env", 4) || !ft_strncmp(data->lines[index_1]->ops[index_2][0], "export", 7)
		|| !ft_strncmp(data->lines[index_1]->ops[index_2][0], "cd", 3) || !ft_strncmp(data->lines[index_1]->ops[index_2][0], "unset", 6)
		|| !ft_strncmp(data->lines[index_1]->ops[index_2][0], "pwd", 4) || !ft_strncmp(data->lines[index_1]->ops[index_2][0], "exit", 5)
		|| (!ft_strncmp(data->lines[index_1]->ops[index_2][0], "ls", 3) && !is_valid_cwd(data))))
		return (1);
	return (0);
}

int	slash_in_cmnd(char *str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '/')
			return (1);
	}
	return (0);
}

char *find_path_2(t_pipex* data, char **arr, char *cmnd)
{
	int i;
	char *full_path;
	char *new;

	i = -1;
	new = NULL;
	if (!slash_in_cmnd(cmnd))
		new = ft_strjoin("/", cmnd, data);
	while (arr[++i])
	{
		if (!slash_in_cmnd(cmnd))
			full_path = ft_strjoin(arr[i], new, data);
		else
			full_path = ft_strdup(data, cmnd);
		if (!access(full_path, X_OK))
			return (free_list((void *)arr), free_str(&new), full_path);
		free_str(&full_path);
	}
	return (free_list((void *)arr), free(new), NULL);
}

char *find_path(t_pipex *data, char *cmnd)
{
	int i;
	char *path;
	char **arr;

	i = 0;
	path = NULL;
	if (!cmnd || !data->cur_env || !data->cur_env[0])
		return (NULL);
	while (data->cur_env[i] && i < 100)
	{
		if (!ft_strncmp("PATH=", (const char *)data->cur_env[i], 5))
		{
			path = data->cur_env[i] + 5;
			break ;
		}
		i++;
	}
	if (!path || !*path)
		return (NULL);
	arr = ft_split(path, ':');
	if (!arr || !*arr)
		return (NULL);
	return (find_path_2(data, arr, cmnd));
}