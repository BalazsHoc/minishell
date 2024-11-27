#include "../../minishell.h"

void set_cur_path(t_pipex *data)
{
	int i;
	int check;

	// char *new;
	check = 0;
	i = -1;
	while (data->cur_env[++i])
	{
		// printf("ENV:: %s\n", (*data->cur_env)[i]);
		if (!check && !ft_strncmp(data->cur_env[i], "PWD=", 4))
		{
			data->cur_path = data->cur_env[i] + 4;
			check = 1;
		}
	}
	// printf("LENGTH ENV: %d\n", i);
	// // // i = 0;
	// // // while (data->cur_path[i])
	// // // 	i++;
	// // // new = malloc(sizeof(char) * (i + 1));
	// // // if (!new)
	// // // 	return (printf("malloc fail\n"), error_code(data, NULL, 1, 1), NULL);
	// // // new[i] = 0;
	// // i = -1;
	// // while (data->cur_path[++i])
	// // 	new[i] = data->cur_path[i];
	// data->cur_path = new;
}

int is_mini(t_pipex *data, int i)
{
	if (data->ops[i] && data->ops[i][0] && (!ft_strncmp(data->ops[i][0], "env", 4) || !ft_strncmp(data->ops[i][0], "export", 7)
		|| !ft_strncmp(data->ops[i][0], "cd", 3) || !ft_strncmp(data->ops[i][0], "unset", 6)
		|| !ft_strncmp(data->ops[i][0], "pwd", 4) || !ft_strncmp(data->ops[i][0], "exit", 5)
		|| (!ft_strncmp(data->ops[i][0], "ls", 3) && !is_valid_cwd(data))))
		return (1);
	return (0);
}

char *find_path_2(char **arr, char *cmnd)
{
	int i;
	char *full_path;
	char *new;

	i = -1;
	new = ft_strjoin("/", cmnd);
	while (arr[++i])
	{
		full_path = ft_strjoin(arr[i], new);
		if (!access(full_path, X_OK))
			return (free_list(arr), free(new), full_path);
		free(full_path);
	}
	return (free_list(arr), free(new), NULL);
}

char *find_path(char **env, char *cmnd)
{
	int i;
	char *path;
	char **arr;

	i = 0;
	path = NULL;
	if (!cmnd || !env || !*env)
		return (perror("path not found"), NULL);
	while (env[i] && i < 100)
	{
		if (!ft_strncmp("PATH=", (const char *)env[i], 5))
		{
			path = env[i] + 5;
			break ;
		}
		i++;
	}
	if (!path || !*path)
		return (perror("path not found"), NULL);
	arr = ft_split(path, ':');
	if (!arr || !*arr)
		return (perror("path not found"), NULL);
	return (find_path_2(arr, cmnd));
}