#include "../minishell.h"

char *find_path_2(char **arr, char *cmnd)
{
	int i;
	char *full_path;

	i = -1;
	cmnd = ft_strjoin("/", cmnd);
	while (arr[++i])
	{
		full_path = ft_strjoin(arr[i], cmnd);
		if (!access(full_path, X_OK))
			return (free_list(arr), full_path);
		free(full_path);
	}
	return (free_list(arr), NULL);
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
	while (i < 100 && env[i])
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