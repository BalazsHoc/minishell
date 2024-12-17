#include "../../minishell.h"


void	ft_strncpy_2(char *dest, char *src, int size, int open)
{
	int i;
	int j;

	i = 0;
	j = 0;
	// printf("OPEN : %d\n", open);
	while (j < size)
	{
		while (((!open && is_quote(src[i]))
			|| (open == 1 && is_quote_one(src[i]))
			|| (open == 2 && is_quote_two(src[i])))
			 && !is_space(src[i - 1]))
			i++;
		dest[j] = src[i];
		// printf("DEST: %c\n", dest[j]);
		i++;
		j++;
	}
}

int	count_key(char *line, int j, int open)
{
	int k;
	int check;

	k = 0;
	check = 0;
	while (line[j])
	{
		// printf("COUNT KEY POS: %s CHECK: %d\n", line + j, check);
		if (check && open == 2 && (is_space(line[j]) || line[j] == '\n' || is_quote(line[j])))
			break;
		if (check && !open && (!line[j] || is_space(line[j]) || line[j] == '\n'
			|| is_real_pipe(line, j)
			|| is_red_clean(line, j)
			|| is_quote(line[j])))
			break;
		if (check)
			k++;
		// printf("KEY ______ %d\n", k);
		if (line[j] == '$')
			check = 1;
		if (check && !k && line[j + 1] == '?')
			return (1);
		j++;
	}
	return (k);
}

char *extract_key(t_pipex *data, int j, int open, int check)
{
	int k;
	char *key;

	key = malloc(sizeof(char) * (count_key(data->line, j, open) + 1));
	if (!key)
		return (error_code(data), NULL);
	key[count_key(data->line, j, open)] = 0;
	k = 0;
	while (data->line[j])
	{
		// printf("OPEN: %d at %s\n", open, line + j);
		if (check && open == 2 && (is_space(data->line[j]) || data->line[j] == '\n' || is_quote(data->line[j])))
			break;
		if (check && !open && (!data->line[j] || is_space(data->line[j]) || data->line[j] == '\n'
			|| is_real_pipe(data->line, j)
			|| is_red_clean(data->line, j)
			|| is_quote(data->line[j])))
			break;
		if (check)
			key[k++] = data->line[j];
		if (data->line[j] == '$')
			check = 1;
		if (check && !k && data->line[j + 1] == '?')
			return (ft_strcpy("?", key), key);
		j++;
	}
	return (key);
}

char *fill_key(t_pipex *data, char *str)
{
	int i;
	char *new;

	new = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new)
		return (error_code(data), NULL);
	new[ft_strlen(str)] = 0;
	i = -1;
	while (str[++i])
		new[i] = str[i];
	return (new);
}

char *find_elem(t_pipex *data, int i, int open, char **env)
{
	char	*elem;
	char	*key;
	int		j;

	j = -1;
	key = extract_key(data, i, open, 0);
	// printf("KEY: %s\n", key);
	elem = NULL;
	while (env[++j])
	{
		if (!ft_strncmp(key, env[j], ft_strlen(key)) && env[j][ft_strlen(key)] == '=')
			elem = fill_key(data, env[j] + (count_key(data->line, i, open) + 1));
	}
	free_str(key);
	key = NULL;
	// printf("FOUND ELEM :%s$\n", elem);
	return (elem);
}

int	count_expansion(t_pipex *data, int i, int open, char **env)
{
	int count;
	char *elem;

	count = 0;
	// printf("COUNT ELEM: %d\n", count);
	elem = NULL;
	while (data->line[i])
	{
		// if (line[i] == '$' && elem)
		// 	i += ft_strlen(elem) - 2;
		// printf("POS1: %s\n", line + i);
		if (data->line[i] == '$' && data->line[i + 1] && data->line[i + 1] != '?')
		{
			elem = find_elem(data, i, open, env);
			i += count_chars(data->line, i, 0);
		}
		else if (data->line[i] == '$')
		{
			i += 2;
			elem = ft_itoa(data->last_exit_status);
		}
		if (elem)
		{
			count += ft_strlen(elem);
			free(elem);
			elem = NULL;
		}
		// printf("POS2: %s\n", line + i);
		if (!data->line[i])
			break;
		if (open == 2 && is_quote_two(data->line[i]))
			break;
		if (!open && (!data->line[i] || is_space(data->line[i]) || data->line[i] == '\n'
			|| is_real_pipe(data->line, i)
			|| is_red_clean(data->line, i)
			|| (is_space(data->line[i]) && is_quote(data->line[i + 1]))
			|| ((!data->line[i + 2] || is_space(data->line[i + 2]) || data->line[i + 2] == '\n') && is_quote(data->line[i + 1]))))
			break;
		count++;
		i++;
	}
	// printf("COUNT EXPANSION: %d\n", count);
	return (count);
}


char	*expand_it(t_pipex *data, int i, int open, char **env)
{
	int j;
	char *elem;
	char *new;

	elem = NULL;
	new = malloc(sizeof(char) * (count_expansion(data, i, open, env) + 1));
	if (!new)
		return (printf("malloc fail\n"), free_str(elem), error_code(data), NULL);
	new[count_expansion(data, i, open, env)] = 0;
	j = 0;
	while (data->line[i])
	{
		// printf("START EXPANSION: #%s# | I: %d | OPEN: %d\n", data->line + i, i ,open);
		if (data->line[i] == '$' && (data->line[i + 1] == '?'))
		{
			elem = ft_itoa(data->last_exit_status);
			ft_strncpy_2(new + j, elem, ft_strlen(elem), open);
			i += 2;
		}
		else if (data->line[i] == '$')
		{
			elem = find_elem(data, i++, open, env);
			ft_strncpy_2(new + j, elem, ft_strlen(elem), 0);
			i += count_chars(data->line, i, 0);
		}
		if (elem)
		{
			j += ft_strlen(elem);
			free(elem);
			elem = NULL;
		}
		// printf("i: %d\n", i);
		if (open && is_quote_two(data->line[i]))
			break;
		if (!open && (!data->line[i] || is_space(data->line[i]) || data->line[i] == '\n'
			|| is_real_pipe(data->line, i)
			|| is_red_clean(data->line, i)
			|| is_quote(data->line[i])))
			// || ((!line[i + 2] || is_space(line[i + 2]) || line[i + 2] == '\n') && is_quote(line[i + 1]))))
			break;
		new[j] = data->line[i++];
		// printf("POS NEW: %s$\n", data->line + i);
		j++;
	}
	// printf("NEW: $%s$\n", new);
	return (new);
}

char *fill_normal(t_pipex *data, int j, int open)
{
	char *new;

	new = malloc(sizeof(char) * (count_chars(data->line, j, open) + 1));
	if (!new)
		return (perror("malloc fail\n"), error_code(data), NULL);
	new[count_chars(data->line, j, open)] = 0;
	ft_strncpy_2(new, data->line + j, count_chars(data->line, j, open), open);
	return (new);
}

int dollar_in(char *line, int j, int open)
{
	while (line[j])
	{
		if (open == 2 && is_quote_two(line[j]))
			break;
		if (!open && (!line[j + 1] || is_space(line[j + 1]) || line[j + 1] == '\n'
			|| is_real_pipe(line, j + 1)
			|| (is_red_1(line[j]) && !is_red_1(line[j + 1]))
			|| (is_red_1(line[j + 1]) && !is_space(line[j]) && !is_red_1(line[j]))
			|| (is_space(line[j]) && is_quote(line[j + 1]))
			|| ((!line[j + 2] || is_space(line[j + 2]) || line[j + 2] == '\n') && is_quote(line[j + 1]))))
			break;
		if (line[j] == '$' && line[j + 1] && (!is_space(line[j + 1]) && !(open == 2 && is_quote_two(line[j + 1]))))
			return (j);
		j++;
	}
	return (-1);
}

int		is_delim(char *str, int i)
{
	if (is_space(str[i - 1])
		|| (i >= 3 && ((is_quote_one(str[i - 1]) && is_quote_one(str[i - 2]) && is_space(str[i - 3])) || (is_quote_two(str[i - 1]) && is_quote_two(str[i - 2]) && is_space(str[i - 3])))))
		return (1);
	return (0);
}

char	**fill_cmnds(char **arr, t_pipex *data, int i, char **env)
{
	int	j;
	int k;
	int	index;
	int open;

	j = -1;
	index = -1;
	open = 0;
	k = -i;
	while (data->line[++j] && i >= 0)
	{
		if (is_quote_one(data->line[j]) && !open && (is_space(data->line[j - 1]) || is_real_pipe(data->line, j -1) || is_red_clean(data->line, j - 1)))
			open = 1;
		else if (is_quote_two(data->line[j]) && !open && (is_space(data->line[j - 1]) || is_real_pipe(data->line, j -1) || is_red_clean(data->line, j - 1)))
			open = 2;
		else if (is_quote_one(data->line[j]) && !open && !is_space(data->line[j - 1]))
			open = 1;
		else if (is_quote_two(data->line[j]) && !open && !is_space(data->line[j - 1]))
			open = 2;
		else if (((is_quote_one(data->line[j]) && open == 1) || (is_quote_two(data->line[j]) && open == 2)) && ++j)
			open = 0;
		// // "this is 'hi there ' last word "
		// printf("FILL_CMNDS: %s | OPEN: %d | K: %d | INDEX: %d \n", data->line + j, open, k, index);
		if (k == 0 && data->line[j] && !is_real_pipe(data->line, j) && ((dollar_in(data->line, j, open) >= 0 && count_expansion(data, j, open, data->cur_env)) || dollar_in(data->line, j, open) == -1) && ((j == 0 && !is_space(data->line[j]))
				|| (is_delim(data->line, j) && !is_space(data->line[j]) && !open)
				// || (is_space(data->line[j - 1]) && !is_space(data->line[j]) && !open)
				|| (((j > 1 && (is_space(data->line[j - 2]) || is_real_pipe(data->line, j - 2) || is_red_clean(data->line, j - 2))) || j < 2) 
					&& ((open == 1 && is_quote_one(data->line[j - 1])) || (open == 2 && is_quote_two(data->line[j - 1]))))
				|| (is_red_clean(data->line, j) && !open)
				|| ((is_red_in(data->line[j - 1]) && is_red_out(data->line[j])) || (is_red_out(data->line[j - 1]) && is_red_in(data->line[j])))
				|| (is_red_1(data->line[j - 1]) && !is_red_1(data->line[j]) && !is_space(data->line[j]) && data->line[j] != '|' && !open)
				|| ((is_real_pipe(data->line, j - 1)
					|| (data->line[j - 1] == '|' && data->line[j - 2] == '>')) && !is_space(data->line[j]))))
				// && (!open || ((open == 1 && is_quote_one(line[j - 1])) || (open == 2 && is_quote_two(line[j - 1])))))
		{
			// printf("TRUE!\n");
			if (dollar_in(data->line, j, open) >= 0 && open != 1
				&& (index == -1 || (index >= 0 && ft_strncmp(arr[index], "<<", 3))))
				arr[++index] = expand_it(data, j, open, env);
			// else if (line[dollar_in(line, j, open) + 1] != '?')
			// 	arr[++index] = echo_exit_code();
			else
				arr[++index] = fill_normal(data, j, open);
			if (!arr[index])
				error_code(data);
			// j += count_chars(data->line, j, open);
		}//   single quotes: 																// we have the beginning of the sandwich														// or the end of the sandwich
		if ((open == 1 && is_quote_one(data->line[j]) && is_quote_one(data->line[j + 1]) && !((j > 0 && !is_space(data->line[j - 1])) || (data->line[j + 2] && !is_space(data->line[j + 2]))))
			|| (open == 2 && is_quote_two(data->line[j]) && is_quote_two(data->line[j + 1]) && !((j > 0 && !is_space(data->line[j - 1])) || (data->line[j + 2] && !is_space(data->line[j + 2])))))
		// if ((open == 1 && is_quote_one(data->line[j]) && is_quote_one(data->line[j + 1]) && (((j == 0 || is_space(data->line[j - 1])) && data->line[j + 2] && !is_space(data->line[j + 2])) || (!is_space(data->line[j - 1]) && (!data->line[j + 2] || is_space(data->line[j + 2])))))
		// 	|| (open == 2 && is_quote_two(data->line[j]) && is_quote_two(data->line[j + 1]) && (((j == 0 || is_space(data->line[j - 1])) && data->line[j + 2] && !is_space(data->line[j + 2])) || (!is_space(data->line[j - 1]) && (!data->line[j + 2] || is_space(data->line[j + 2]))))))
		{
			// printf("FILL NULL\n");
			arr[++index] = malloc(sizeof(char) * (1));
			arr[index][0] = 0;
		}
		// printf("I1: %d\n", i);
		if (is_real_pipe(data->line, j) && j > 0 && !is_red_1(data->line[j - 1]) && k++ != INT_MIN)
			i--;
		if (!data->line[j])
			break;
		// printf("I2: %d\n", i);
	}
	return (arr);
}
