#include "../../minishell.h"

int is_or(char *cur)
{
	if (cur[0] == '|' && cur[-1] == '|')
		return (1);
	if (cur[0] == '|' && cur[+1] == '|')
		return (1);
	return (0);
}

int is_red_1(char c)
{
	if (c == '>' || c == '<')
		return (1);
	return (0);
}

int is_red_clean(char *str, int index)
{
	// printf("here: %s\n", str);
	if ((index == 0 && is_red_1(str[0])
			&& ((is_red_1(str[1]) && !is_red_1(str[2])) || (!is_red_1(str[1]))))
		|| (is_red_1(str[index]) && !is_red_1(str[index - 1])
			&& ((is_red_1(str[index + 1]) && !is_red_1(str[index + 2])) || (!is_red_1(str[index + 1])))))
	{
		if ((index == 0 && !is_red_1(str[1])) || (!is_red_1(str[index + 1])))
		{
			printf("RETURN 1\n");
			return (1);
		}
		printf("RETURN 2\n");
		return (2);
	}
	// printf("RETURN 0\n");
	return (0);
}

int	real_pipe(char *line, int index)
{
	if (line[index] == '|')
	{
		if (line[index - 1] == '|'
		|| line[index - 1] == '>'
		|| line[index + 1] == '|')
			return (0);
		return (1);
	}
	return (0);
}

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