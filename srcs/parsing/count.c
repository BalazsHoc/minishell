#include "../../minishell.h"

int	count_cmnds(char *line)
{
	int	count;
	int	i;
	int open;

	count = 1;
	i = -1;
	open = 0;
	if (!line || !*line)
		return (0);
	while (line && line[++i])
	{
		// printf("COUNT _ CMNDS : %s\n", line + i);
		if (is_quote_one(line[i]) && ((i > 0 && is_space(line[i - 1])) || i == 0) && !open && ++i)
			open = 1;
		else if (is_quote_two(line[i]) && ((i > 0 && is_space(line[i - 1])) || i == 0) && !open && ++i)
			open = 2;
		else if (((is_quote_one(line[i]) && open == 1) || (is_quote_two(line[i]) && open == 2)) && ++i)
			open = 0;
		if (is_real_pipe(line, i) && !open)
			count++;
		if (!line[i])
			break;
	}
	// printf("COUNT CMNDS: %d\n", count);
	return (count);
}

int	count_elem(t_pipex *data, int i, int count)
{
	int	j;
	int	k;
	int open;

	j = -1;
	k = -i;
	open = 0;
	// printf("START counting ELEMS\n");
	while (data->line[++j] && i >= 0)
	{
		// printf("J: %d | K: %d | I: %d\n", j, k, i);
		if (k == 0)
		{
			// printf("LINE: $%s$ COUNT: %d OPEN: %d\n", data->line + j, count, open);
			if (is_real_pipe(data->line, j) && !open)
				break ;
			if (is_quote_one(data->line[j]) && !open && (is_space(data->line[j - 1]) || is_real_pipe(data->line, j -1) || is_red_clean(data->line, j - 1)) && count++)
				open = 1;
			else if (is_quote_two(data->line[j]) && !open && (is_space(data->line[j - 1]) || is_real_pipe(data->line, j -1) || is_red_clean(data->line, j - 1)) && count++)
				open = 2;
			else if (is_quote_one(data->line[j]) && !open && !is_space(data->line[j - 1]))
				open = 1;
			else if (is_quote_two(data->line[j]) && !open && !is_space(data->line[j - 1]))
				open = 2;
			else if (((is_quote_one(data->line[j]) && open == 1) || (is_quote_two(data->line[j]) && open == 2)))
				open = 0;
			else if (!open && data->line[j] && ((dollar_in(data->line, j, open) >= 0 && count_expansion(data, j, open, data->cur_env)) || dollar_in(data->line, j, open) == -1) && ((j == 0 && !is_space(data->line[j]))
				|| (is_space(data->line[j - 1]) && !is_space(data->line[j]))
				|| (is_red_clean(data->line, j) && !is_red_clean(data->line, j - 1))
				|| ((is_red_in(data->line[j - 1]) && is_red_out(data->line[j])) || (is_red_out(data->line[j - 1]) && is_red_in(data->line[j])))
				|| (is_red_1(data->line[j - 1]) && !is_space(data->line[j]) && data->line[j] != '|' && !is_red_1(data->line[j]))
				|| ((is_real_pipe(data->line, j - 1)
					|| (data->line[j - 1] == '|' && data->line[j - 2] == '>')) && !is_space(data->line[j]))))
				{
					// printf("COUNT+++++++++++++++++++++++++++++++++++\n");
					// j += count_chars(line, j, open) - 1;
					// if (is_red_clean(line, j) == 2)
						// j++;
					count++;
				}
		}
		else if (is_real_pipe(data->line, j) && --i != INT_MIN)
			k++;
	}
	// printf("COUNT ELEM RETURN: %d\n", count);
	return (count);
}

int	count_chars(char *line, int i, int open)
{
	int count;

	count = 1;
	// printf("START COUNTING CHARS.. | OPEN %d\n", open);
	while (line[i])
	{
		// printf("LINE COUNT_CHARS 1 1 1: %s | OPEN: %d | COUNT: %d\n", line + i, open,count);
		if (is_quote_one(line[i]) && is_space(line[i - 1]) && !open && ++i)
			open = 1;
		else if (is_quote_two(line[i]) && is_space(line[i - 1]) && !open && ++i)
			open = 2;
		else if (is_quote_one(line[i]) && !open && !is_space(line[i - 1]))
			open = 1;
		else if (is_quote_two(line[i]) && !open && !is_space(line[i - 1]))
			open = 2;
		else if (is_space(line[i + 1]) && ((is_quote_one(line[i]) && open == 1) || (is_quote_two(line[i]) && open == 2)))
			break;
		// printf("LINE COUNT_CHARS 2 2 2: %s | OPEN: %d | COUNT: %d\n", line + i, open,count);
		if (!open && (!line[i + 1] || is_space(line[i + 1]) || line[i + 1] == '\n'
			|| is_real_pipe(line, i + 1)
			|| (is_red_1(line[i]) && !is_red_1(line[i + 1]))
			|| ((is_red_in(line[i + 1]) && is_red_out(line[i])) || (is_red_out(line[i + 1]) && is_red_in(line[i])))
			|| (is_red_1(line[i + 1]) && !is_space(line[i]) && !is_red_1(line[i]))))
			// || ((!line[i + 2] || is_space(line[i + 2]) || line[i + 2] == '\n') && is_quote(line[i + 1]))))
			break;
		else if ((!line[i + 2] || (line[i + 2] && (is_space(line[i + 2]) || line[i + 2] == '\n' || line[i + 2] == '|' || is_red_clean(line, i + 2))))
			&& ((is_quote_one(line[i + 1]) && open == 1) || (is_quote_two(line[i + 1]) && open == 2) || (is_quote(line[i + 1]) && !open)))
				break ;
		// else if (((line[i + 2] && (is_space(line[i + 2]) || line[i + 2] == '\n' || line[i + 2] == '|' || is_red_clean(line, i + 2)))
		// 	&& ((open == 1 && is_quote_one(line[i + 1])) || (open == 2 && is_quote_two(line[i + 1])))))
		// 		break ;
		// if (!(!open && i > 0 && !is_space(line[i - 1]) && (is_quote(line[i]))))
		if (line[i + 1] && ((!is_quote(line[i + 1])) || ((open == 1 && is_quote_two(line[i + 1])) || (open == 2 && is_quote_one(line[i + 1])))))
			count++;
		i++;
	}
	// printf("COUNT CHARS RETURN: %d\n", count);
	return (count);
}