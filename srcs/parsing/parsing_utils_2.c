#include "../../minishell.h"

int is_or(char *cur)
{
	if (cur[0] == '|' && cur[-1] == '|')
		return (1);
	if (cur[0] == '|' && cur[+1] == '|')
		return (1);
	return (0);
}


// int find_that_shit(char *arr, char *cur, char **list)
// {
// 	if (arr == cur)
// 	{
// 		if (list[2])
// 			return (2);
// 		return (-1);
// 	}
// 	return (0);
// }

int cmnds_start(t_pipex *data, int index)
{
	int i;

	i = -1;
	while (data->cmnds[index][++i])
	{
		if (is_red(data, index, i))
		{
			if (i == 0)
			{
				if (!data->cmnds[index][2])
					return (-1);
				return (2);
			}
			return (0);
		}
	}
	return (0);
}


// CASES

// 1. cmnd < in > out

// 2. < in cmnd > out

// 3. cmnd < in 

// 4. < in
