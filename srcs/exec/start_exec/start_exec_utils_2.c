#include "../../../minishell.h"

int	here_doc_util_1(t_pipex *data, int index_1, int index_2, int i)
{
	if (!ft_strncmp(data->l[index_1]->cmnds[index_2][i], "<<", 3)
		&& !data->l[index_1]->red_cmnd[index_2][i]
				&& find_key(data, index_1, index_2, i + 1) == data->here_2_old)
		return (1);
	return (0);
}

int	here_doc_util_2(t_pipex *data, int index_1, int index_2, int i)
{
	if (((!ft_strncmp(data->l[index_1]->paths[index_2], "pathnfound", 11)
				|| (is_valid_in(data, index_1, index_2) == -1))
			&& i == is_red_inline(data, index_1, index_2))
		|| i != is_red_inline(data, index_1, index_2))
		return (1);
	return (0);
}

int	here_doc_util_3(t_pipex *data, int index_1, int index_2, int i)
{
	if (!ft_strncmp(data->l[index_1]->cmnds[index_2][i], "<<", 3)
				&& (!ft_strncmp(data->l[index_1]->paths[index_2],
					"pathnfound", 11)
					|| i != is_red_inline(data, index_1, index_2))
						&& find_key(data, index_1, index_2, i + 1))
		return (1);
	return (0);
}

int	here_doc(t_pipex *data, int index_1, int index_2, int i)
{
	char	*infile;

	signal_change(1);
	infile = NULL;
	while (data->l[index_1]->cmnds[++index_2])
	{
		i = -1;
		while (data->l[index_1]->cmnds[index_2][++i])
		{
			if (here_doc_util_1(data, index_1, index_2, i))
			{
				infile = get_input(data, index_1, index_2, i);
				if (!infile)
					break ;
				if (here_doc_util_2(data, index_1, index_2, i))
					free_str(&infile);
				else
					data->l[index_1]->input[index_2] = infile;
				infile = NULL;
			}
			else if (here_doc_util_3(data, index_1, index_2, i))
				data->here_2_old = find_key(data, index_1, index_2, i + 1);
		}
	}
	return (signal_change(2), 1);
}
