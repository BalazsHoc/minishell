#include "../../minishell.h"

int	count_cmnds(char *line)
{
	int	count;
	int	i;

	count = 1;
	i = -1;
	while (line[++i])
	{
		if (is_real_pipe(line, i))
			count++;
	}
	return (count);
}

int	count_elem(char *line, int i, int count)
{
	int	j;
	int	k;
	int open;

	j = -1;
	k = -i;
	open = 0;
	// printf("START counting ELEMS\n");
	while (line[++j] && i >= 0)
	{
		// printf("J: %d | K: %d | I: %d\n", j, k, i);
		if (k == 0)
		{
			// printf("LINE: $%s$\n", line + j);
			if (is_real_pipe(line, j) && !open)
				break ;
			if (is_quote_one(line[j]) && !open && is_space(line[j - 1]) && count++ && printf("COUNT++++++++\n"))
				open = 1;
			else if (is_quote_two(line[j]) && !open && is_space(line[j - 1]) && count++ && printf("COUNT+++++++\n"))
				open = 2;
			else if (((is_quote_one(line[j]) && open == 1) || (is_quote_two(line[j]) && open == 2)))
				open = 0;
			else if (!open && ((j == 0 && !is_space(line[j]))
				|| (is_space(line[j - 1]) && !is_space(line[j]))
				|| (is_red_clean(line, j))
				|| (is_red_1(line[j - 1]) && !is_space(line[j]) && line[j] != '|')
				|| (line[j - 1] == '|' && !is_space(line[j]))))
				{
					// printf("COUNT+++++++++++++++++++++++++++++++++++\n");
					if (is_red_clean(line, j) == 2)
						j++;
					j += count_chars(line, j, open) - 1;
					count++;
				}
		}
		else if (is_real_pipe(line, j) && --i != INT_MIN)
			k++;
	}
	// printf("COUNT ELEM RETURN: %d\n", count);
	return (count);
}

int	count_chars(char *line, int i, int open)
{
	int count;

	count = 1;
	// printf("START COUNTING CHARS..\n");
	while (line[i])
	{
		// printf("LINE COUNT_CHARS: %s | %d\n", line + i, count);
		if (!open && (!line[i + 1] || is_space(line[i + 1]) || line[i + 1] == '\n'
			|| is_real_pipe(line, i + 1)
			|| (is_red_1(line[i]) && !is_red_1(line[i + 1]))
			|| (is_red_1(line[i + 1]) && !is_space(line[i]) && !is_red_1(line[i]))
			|| (is_space(line[i]) && is_quote(line[i + 1]))
			|| ((!line[i + 2] || is_space(line[i + 2]) || line[i + 2] == '\n') && is_quote(line[i + 1]))))
			break;
		else if ((open == 1 && is_quote_one(line[i + 1])) || (open == 2 && is_quote_two(line[i + 1])))
				break ;
		if (!(!open && i > 0 && !is_space(line[i - 1]) && (is_quote(line[i]))))
			count++;
		i++;
	}
	// printf("COUNT CHARS RETURN: %d\n", count);
	return (count);
}

void	ft_strncpy_2(char *dest, char *src, int size)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (j < size)
	{
		dest[j] = src[i];
		// printf("DEST: %c\n", dest[j]);
		i++;
		j++;
	}
}

char	**fill_cmnds(char **arr, char *line, int i, int k)
{
	int	j;
	int	index;
	int open;

	j = -1;
	index = -1;
	open = 0;
	while (line[++j] && i >= 0)
	{
		if (is_quote_one(line[j]) && is_space(line[j -1]) && !open && ++j)
			open = 1;
		else if (is_quote_two(line[j]) && is_space(line[j -1]) && !open && ++j)
			open = 2;
		else if (((is_quote_one(line[j]) && open == 1) || (is_quote_two(line[j]) && open == 2)) && ++j)
			open = 0;
		// "this is 'hi there ' last word "
		// printf("FILL_CMNDS: %s | OPEN: %d | K: %d\n", line + j, open, k);
		if (k == 0 && !is_real_pipe(line, j) && ((j == 0 && !is_space(line[j]))
				|| (is_space(line[j - 1]) && !is_space(line[j]) && !open)
				|| ((open == 1 && is_quote_one(line[j - 1])) || (open == 2 && is_quote_two(line[j - 1])))
				|| (is_red_clean(line, j) && !open)
				|| (is_red_1(line[j - 1]) && !is_space(line[j]) && line[j] != '|' && !open)
				|| (line[j - 1] == '|' && !is_space(line[j]) && !open)))
				// && (!open || ((open == 1 && is_quote_one(line[j - 1])) || (open == 2 && is_quote_two(line[j - 1])))))
		{
			// printf("TRUE!\n");
			arr[++index] = malloc(sizeof(char) * (count_chars(line, j, open) + 1));
			if (!arr[index])
				return (perror("malloc fail\n"), free(arr), NULL);
			ft_strncpy_2(arr[index], line + j, count_chars(line, j, open));
			arr[index][count_chars(line, j, open)] = 0;
			// j += count_chars(line, j, open) - 1;
		}
		// printf("I1: %d\n", i);
		if (is_real_pipe(line, j) && j > 0 && line[j - 1] != '>' && k++ != INT_MIN)
			i--;
		if (!line[j])
			break;
		// printf("I2: %d\n", i);
	}
	return (arr);
}
