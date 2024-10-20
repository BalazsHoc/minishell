#include "../minishell.h"

int is_or(char *cur)
{
	if (cur[0] == '|' && cur[-1] == '|')
		return (1);
	if (cur[0] == '|' && cur[+1] == '|')
		return (1);
	return (0);
}


int find_that_shit(char *arr, char *cur, char **list)
{
	int i;

	i = 0;

	if (arr == cur)
	{
		if (list[2])
			return (2);
		return (-1);
	}
	return (0);
}

int cmnds_start(char **arr)
{
	int i;

	i = -1;
	while (arr[++i])
	{
		if (!ft_strncmp(arr[i], "<", 2))
		{
			while (arr[i])
				i++;
			return (--i);
		}
		if (!ft_strncmp(arr[i], ">", 2) || !ft_strncmp(arr[i], ">>", 3))
			return (0);
		if (!ft_strncmp(arr[i], "<<", 3))
			return (find_that_shit(arr[0], arr[i], arr));
	}
	return (0);
}
