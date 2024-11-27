#include "../../minishell.h"

int	count_cmnds(char *line)
{
	int	count;
	int	i;
	int open;

	count = 1;
	i = -1;
	while (line[++i])
	{
		if (is_quote_one(line[i]) && is_space(line[i -1]) && !open && ++i)
			open = 1;
		else if (is_quote_two(line[i]) && is_space(line[i -1]) && !open && ++i)
			open = 2;
		else if (((is_quote_one(line[i]) && open == 1) || (is_quote_two(line[i]) && open == 2)) && ++i)
			open = 0;
		if (is_real_pipe(line, i) && !open)
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
	printf("START counting ELEMS\n");
	while (line[++j] && i >= 0)
	{
		// printf("J: %d | K: %d | I: %d\n", j, k, i);
		if (k == 0)
		{
			printf("LINE: $%s$ OPEN: %d\n", line + j, open);
			if (is_real_pipe(line, j) && !open)
				break ;
			if (is_quote_one(line[j]) && !open && is_space(line[j - 1]) && count++ && printf("COUNT++++++++\n"))
				open = 1;
			else if (is_quote_two(line[j]) && !open && is_space(line[j - 1]) && count++ && printf("COUNT+++++++\n"))
				open = 2;
			else if (((is_quote_one(line[j]) && open == 1) || (is_quote_two(line[j]) && open == 2)))
				open = 0;
			else if (!open && line[j] && ((j == 0 && !is_space(line[j]))
				|| (is_space(line[j - 1]) && !is_space(line[j]))
				|| (is_red_clean(line, j) && !is_red_clean(line, j - 1))
				|| ((is_red_in(line[j - 1]) && is_red_out(line[j])) || (is_red_out(line[j - 1]) && is_red_in(line[j])))
				|| (is_red_1(line[j - 1]) && !is_space(line[j]) && line[j] != '|' && !is_red_1(line[j]))
				|| (is_real_pipe(line, j - 1) && !is_space(line[j]))))
				{
					printf("COUNT+++++++++++++++++++++++++++++++++++\n");
					// j += count_chars(line, j, open) - 1;
					// if (is_red_clean(line, j) == 2)
						// j++;
					count++;
				}
		}
		else if (is_real_pipe(line, j) && --i != INT_MIN)
			k++;
	}
	printf("COUNT ELEM RETURN: %d\n", count);
	return (count);
}

int	count_chars(char *line, int i, int open)
{
	int count;

	count = 1;
	printf("START COUNTING CHARS..\n");
	while (line[i])
	{
		if (is_quote_one(line[i]) && is_space(line[i - 1]) && !open && ++i)
			open = 1;
		else if (is_quote_two(line[i]) && is_space(line[i - 1]) && !open && ++i)
			open = 2;
		else if (((is_quote_one(line[i]) && open == 1) || (is_quote_two(line[i]) && open == 2)) && ++i)
			open = 0;
		printf("LINE COUNT_CHARS: %s | OPEN: %d | COUNT: %d\n", line + i, open,count);
		if (!open && (!line[i + 1] || is_space(line[i + 1]) || line[i + 1] == '\n'
			|| is_real_pipe(line, i + 1)
			|| (is_quote(line[i + 1]) && is_space(line[i - 1]))
			|| (is_red_1(line[i]) && !is_red_1(line[i + 1]))
			|| ((is_red_in(line[i + 1]) && is_red_out(line[i])) || (is_red_out(line[i + 1]) && is_red_in(line[i])))
			|| (is_red_1(line[i + 1]) && !is_space(line[i]) && !is_red_1(line[i]))))
			// || ((!line[i + 2] || is_space(line[i + 2]) || line[i + 2] == '\n') && is_quote(line[i + 1]))))
			break;
		else if ((!line[i + 2] || (line[i + 2] && (is_space(line[i + 2]) || line[i + 2] == '\n' || line[i + 2] == '|' || is_red_clean(line, i + 2))))
			&& ((is_quote(line[i + 1]) && open == 1) || (is_quote_two(line[i + 1]) && open == 2) || (is_quote(line[i + 1]) && !open)))
				break ;
		// else if (((line[i + 2] && (is_space(line[i + 2]) || line[i + 2] == '\n' || line[i + 2] == '|' || is_red_clean(line, i + 2)))
		// 	&& ((open == 1 && is_quote_one(line[i + 1])) || (open == 2 && is_quote_two(line[i + 1])))))
		// 		break ;
		if (!(!open && i > 0 && !is_space(line[i - 1]) && (is_quote(line[i]))))
			count++;
		i++;
	}
	printf("COUNT CHARS RETURN: %d\n", count);
	return (count);
}