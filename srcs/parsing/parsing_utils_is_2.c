#include "../../minishell.h"

// int is_or(char *cur)
// {
// 	if (cur[0] == '|' && cur[-1] == '|')
// 		return (1);
// 	if (cur[0] == '|' && cur[+1] == '|')
// 		return (1);
// 	return (0);
// }

int is_red(t_pipex *data, int index_1, int index_2)
{
	// printf("Data1:\n");
	// printf("Data: %s\n", data->cmnds[index_1][index_2]);
	if (!data->cmnds[index_1][index_2])
		return (0);
    if (!ft_strncmp(data->cmnds[index_1][index_2], "<<", 3)
        || !ft_strncmp(data->cmnds[index_1][index_2], ">", 2)
        || !ft_strncmp(data->cmnds[index_1][index_2], "<", 2)
        || !ft_strncmp(data->cmnds[index_1][index_2], ">>", 3))
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
	if ((index == 0 && is_red_1(str[0])
			&& ((is_red_1(str[1]) && !is_red_1(str[2])) || (!is_red_1(str[1]))))
		|| (is_red_1(str[index]) && !is_red_1(str[index - 1])
			&& ((is_red_1(str[index + 1]) && !is_red_1(str[index + 2])) || (!is_red_1(str[index + 1])))))
	{
		if ((index == 0 && !is_red_1(str[1])) || (!is_red_1(str[index + 1])))
			return (1);
		return (2);
	}
	return (0);
}

int	is_real_pipe(char *line, int index)
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