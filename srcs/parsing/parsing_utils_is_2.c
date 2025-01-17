#include "../../minishell.h"

// int is_or(char *cur)
// {
// 	if (cur[0] == '|' && cur[-1] == '|')
// 		return (1);
// 	if (cur[0] == '|' && cur[+1] == '|')
// 		return (1);
// 	return (0);
// }

// int is_red_in(t_pipex *data, int i, int j)
// {
// 	if (!ft_strncmp(data->cmnds[i][j], "<", 2) || !ft_strncmp(data->cmnds[i][j], "<<", 3))
// 		return (1);
// 	return (0);
// }

// int is_red_out(t_pipex *data, int i, int j)
// {
// 	if (!ft_strncmp(data->cmnds[i][j], ">", 2) || !ft_strncmp(data->cmnds[i][j], ">>", 3))
// 		return (1);
// 	return (0);
// }

int is_red_in(char *str, int index)
{
	// printf("c: %c\n", c);
	if (!ft_strncmp(str + index, "<", 1) || !ft_strncmp(str + index, "<<", 2))
		return (1);
	return (0);
}

int is_red_out(char *str, int index)
{
	if (!ft_strncmp(str + index, ">", 1) || !ft_strncmp(str + index, ">>", 2))
		return (1);
	return (0);
}

int is_red(t_pipex *data, int index_1, int index_2, int index_3)
{
	// printf("Data1: %d | %d \n", index_1, index_2);
	// printf("Data: %s\n", data->lines[index_1]->cmnds[index_2][index_3]);
	if (index_2 < 0 || !data->lines[index_1]->cmnds[index_2] || !data->lines[index_1]->cmnds[index_2][index_3])
		return (0);
    if ((!ft_strncmp(data->lines[index_1]->cmnds[index_2][index_3], "<<", 3)
        || !ft_strncmp(data->lines[index_1]->cmnds[index_2][index_3], ">", 2)
        || !ft_strncmp(data->lines[index_1]->cmnds[index_2][index_3], "<", 2)
        || !ft_strncmp(data->lines[index_1]->cmnds[index_2][index_3], ">>", 3))
		&& data->lines[index_1]->red_cmnd[index_2][index_3] == 0)
        return (1);
    return (0);
}

int is_red_basic(t_pipex *data, int index_1, int index_2, int index_3)
{
	// printf("Data1: %d | %d \n", index_1, index_2);
	if (index_3 < 0 || !data->lines[index_1] || !data->lines[index_1]->cmnds[index_2] || !data->lines[index_1]->cmnds[index_2][index_3])
		return (0);
	// printf("index 2: %d | index 3: %d\n", index_2, index_3);
	// printf("Data: %s\n", data->lines[index_1]->cmnds[index_2][index_3]);
    if ((!ft_strncmp(data->lines[index_1]->cmnds[index_2][index_3], "<<", 3)
        || !ft_strncmp(data->lines[index_1]->cmnds[index_2][index_3], ">", 2)
        || !ft_strncmp(data->lines[index_1]->cmnds[index_2][index_3], "<", 2)
        || !ft_strncmp(data->lines[index_1]->cmnds[index_2][index_3], ">>", 3)))
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
	// printf("CHECK RED CLEAN %s\n", str + index);
	if ((index == 0 && is_red_1(str[0])
			&& ((is_red_1(str[1]) && !is_red_1(str[2])) || (!is_red_1(str[1]))))
		|| (is_red_1(str[index]) && !is_red_1(str[index - 1])
			&& ((is_red_1(str[index + 1]) && !is_red_1(str[index + 2])) || (!is_red_1(str[index + 1])))))
		// || (index > 1 && is_red_1(str[index]) && is_red_1(str[index - 1]) && !is_red_1(str[index - 2])
		// 	&& ((is_red_1(str[index + 1]) && !is_red_1(str[index + 2])) || (!is_red_1(str[index + 1])))))
	{
		// printf("IS RED CLEAN\n");
		if ((index == 0 && !is_red_1(str[1])) || (!is_red_1(str[index + 1])))
			return (1);
		return (2);
	}
	return (0);
}

