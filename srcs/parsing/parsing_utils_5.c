#include "../../minishell.h"


int elem_spaces_util_1(t_pipex *data, int j, int open)
{
	if (handle_open(data, j, &open) && data->line[j]
	&& ((j == 0 && !is_quote(data->line[j])) || (j > 0 && (
				(is_red_clean(data->line, j) && !open)
				|| (!open && j > 1 && is_d_b(data->line, j - 1, 0)
					&& !is_d_b(data->line, j, 0))
				|| (((j > 1 && is_d_b(data->line, j - 2, 0)) || j < 2)
					&& ((open == 1 && is_quote_one(data->line[j - 1])
							&& !is_quote_one(data->line[j]))
						|| (open == 2 && is_q_2(data->line[j - 1])
							&& !is_q_2(data->line[j]))))
				|| (!open && !is_real_pipe(data->line, j)
					&& !is_real_pipe(data->line, j)
					// && data->line[j] != '|'
					&& !is_quote(data->line[j]) && !is_space(data->line[j])
					&& is_d_b(data->line, j - 1, 0)
					&& !is_red_1(data->line[j]))
				|| (is_red_1(data->line[j - 1]) && !is_red_1(data->line[j])
					&& !is_space(data->line[j]) && data->line[j] != '|'
					&& !open)
				|| (!open && is_real_pipe(data->line, j - 1)
					&& !is_space(data->line[j])))))
	&& ((d_in(data, j, open) >= 0
			&& count_ex(data, j, open, 0))
		|| d_in(data, j, open) == -1))
		return (1);
	return (0);
}

int	elem_spaces(t_pipex *data, int i)
{
	char *elem;
	int check;

	check = i;
	while (data->count_elem && check
		&& (is_space(data->line[check]) || is_quote(data->line[check])))
		check--;
	if (check > 1 && data->line[check] == '<' && data->line[check - 1] == '<')
		check = 0;
	else
		check = 1;
	elem = NULL;
	if (elem_spaces_util_1(data, i, data->open) && d_in(data, i, 0) >= 0
		&& (!data->count_elem || (data->count_elem && check)))
	{
		data->count_elem++;
		expand_it_1(data, i, data->open, &elem);
		count_elem_spaces(data, elem);
	}
	free_str(&elem);
	return (0);
}