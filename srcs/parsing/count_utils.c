#include "../../minishell.h"

int	if_count_elem_1(t_pipex *data, int j, int *open)
{
	if (handle_open(data, j, &*open) && data->line[j]
		&& ((d_in(data, j, *open) >= 0 && count_ex(data, j, *open, 0))
			|| d_in(data, j, *open) == -1)
		&& ((j == 0 && !is_quote(data->line[j])) || (j > 0 && (
					(is_red_clean(data->line, j) && !*open)
					|| (!*open && j > 1 && is_d_b(data->line, j - 1, 0)
						&& !is_d_b(data->line, j, 0))
					|| (((j >= 2 && is_d_b(data->line, j - 2, 0)
								&& is_quote(data->line[j - 1])) || (j < 2))
						&& ((*open == 1 && is_quote_one(data->line[j - 1])
								&& !is_quote_one(data->line[j])) || (*open == 2
								&& is_q_2(data->line[j - 1])
								&& !is_q_2(data->line[j]))))
					|| (!*open && data->line[j] != '|'
						&& !is_real_pipe(data->line, j)
						&& !is_quote(data->line[j]) && !is_space(data->line[j])
						&& is_d_b(data->line, j - 1, 0)
						&& !is_red_1(data->line[j]))
					|| (is_red_1(data->line[j - 1]) && !is_red_1(data->line[j])
						&& !is_space(data->line[j]) && data->line[j] != '|'
						&& !*open)
					|| (!*open && is_real_pipe(data->line, j - 1)
						&& !is_space(data->line[j]))))))
		return (1);
	return (0);
}

int	count_chars_utils_2(t_pipex *data, int i, int open, int count)
{
	if (!open && count > 0
		&& (is_delim_front(data->line, i)
			|| (count > 0 && is_red_clean(data->line, i))
			|| (count > 0 && i > 0 && is_red_1(data->line[i - 1])
				&& !is_red_1(data->line[i]))
			|| (count > 0 && i > 0 && is_red_clean(data->line, i - count)
				&& ((is_red_in(data->line, i - count)
						&& is_red_out(data->line, i))
					|| (is_red_out(data->line, i - count)
						&& is_red_in(data->line, i)) || count == 2))))
		return (1);
	return (0);
}

count_chars_utils_1(t_pipex *data, int i, int open, int count)
{
	if (count > 0 && is_q_2(data->line[i]) && open == 2 && ((data->line[i + 1]
			&& is_delim_front(data->line, i + 1)) || !data->line[i + 1]))
		return (1);
	return (0);
}