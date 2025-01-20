/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:41:53 by bhocsak           #+#    #+#             */
/*   Updated: 2024/10/11 15:41:55 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// TAKE THAT OUT
void	print_that_shit(t_pipex *data, int index_1)
{
	int	i;
	int	j;

	i = -1;
	printf("|\n");
	while (data->lines[index_1]->cmnds[++i])
	{
		j = -1;
		// printf("data->lines[%d]->cmnds[%d]\n", index_1, i);
		while (data->lines[index_1]->cmnds[i][++j])
		{
			if (data->lines[index_1]->cmnds[i][j])
				printf("ELEM: %d:%d | |%s| ", i, j, data->lines[index_1]->cmnds[i][j]);
			if (data->lines[index_1]->red_cmnd[i][j])
				printf("FLAG");
			printf("\n");
		}
		j = -1;
		if (data->lines[index_1]->ops && data->lines[index_1]->ops[i])
		{
			while (data->lines[index_1]->ops[i][++j])
				printf("OP:   %d:%d | |%s|\n", i, j, data->lines[index_1]->ops[i][j]);
		}
		printf("PATH: |%s|\n", data->lines[index_1]->paths[i]);
	}
	// i = -1;
	// while (data->mini_env[++i])
	// 	printf("ENV[%d]: %s\n", i, data->mini_env[i]);
}

void	init_exit_codes(t_pipex *data, int cmnd_count, int index)
{
	data->lines[index]->exit_codes = ft_calloc(sizeof(int), (cmnd_count), data);
}

void	init_ops(t_pipex *data, int index_1)
{
    int i;
	int j;

    i = -1;
    data->lines[index_1]->ops = ft_calloc(sizeof(char **), (data->lines[index_1]->cmnd_count + 1), data);
    while (data->lines[index_1]->cmnds[++i])
    {
		j = count_ops(data, index_1, i);
		if (j != -1)
		{
			// if (echo_exit_code(data->cmnds[i]))
			// 	j = 3;
			data->lines[index_1]->ops[i] = ft_calloc(sizeof(char *), (j + 1), data);
			// if (!data->lines[index_1]->ops[i])
				// return (perror("malloc fail!\n"), error_code(data));
			data->lines[index_1]->ops[i][j] = 0;
			// if (echo_exit_code(data->cmnds[i]))
			// 	fill_echo_exit(data, i);
			// else
			if (j > 0)
				fill_ops(data, index_1, i);
		}
    }
}

void	init_cmnds(t_pipex *data, int index_1, int i)
{
	data->lines[index_1]->cmnds = ft_calloc(sizeof(char **), (data->lines[index_1]->cmnd_count + 1), data);
	// if (!data->lines[index_1]->cmnds)
		// return (perror("malloc fail!\n"), error_code(data));
	data->lines[index_1]->cmnds[data->lines[index_1]->cmnd_count] = NULL;
	while (++i < data->lines[index_1]->cmnd_count)
	{
		if (!count_elem(data, index_1, i, data->here_2 - 1) && dollar_in(data, 0, 0) != -1)
		{
			// printf("MALLOC FOR NOT FOUND DOLLAR IN\n");
			data->lines[index_1]->cmnds[i] = ft_calloc(sizeof(char *), (1 + 1), data);
			// if (!data->lines[index_1]->cmnds[i])
				// return (perror("malloc fail!\n"), error_code(data));
			// data->lines[index_1]->cmnds[i][1] = NULL;
			data->lines[index_1]->cmnds[i][0] = malloc_str(1, data);
			// data->lines[index_1]->cmnds[i][0][0] = 0;
		}
		else
		{
			data->lines[index_1]->cmnds[i] = ft_calloc(sizeof(char *), (count_elem(data, index_1, i, data->here_2 - 1) + 1), data);
			// if (!data->lines[index_1]->cmnds[i])
				// return (perror("malloc fail!\n"), error_code(data));
			// data->lines[index_1]->cmnds[i][count_elem(data, index_1, i, data->here_2 - 1)] = NULL;
			fill_cmnds(data, index_1, i, data->here_2 - 1);
		}
	}
}
int one_of_those_2(t_pipex *data, int index_1, int index_2, int i)
{
	if (data->lines[index_1]->ops[index_2][0][i + 1] && !one_of_those_2(data, index_1, index_2, i + 1))
		return (0);
	else if (!data->lines[index_1]->ops[index_2][0][i] || data->lines[index_1]->ops[index_2][0][i] == '.' || data->lines[index_1]->ops[index_2][0][i] == '/')
		return (1);
	else 
		return (0);
}

int	one_of_those(t_pipex *data, int index_1, int index_2)
{
	if (!ft_strncmp(data->lines[index_1]->ops[index_2][0], "/", 2) || !ft_strncmp(data->lines[index_1]->ops[index_2][0], ".", 2)
		|| (!ft_strncmp(data->lines[index_1]->ops[index_2][0], "/usr", 4) && one_of_those_2(data, index_1, index_2, 4))
		|| (!ft_strncmp(data->lines[index_1]->ops[index_2][0], "/bin", 4) && one_of_those_2(data, index_1, index_2, 4))
		|| (!ft_strncmp(data->lines[index_1]->ops[index_2][0], "/sbin", 5) && one_of_those_2(data, index_1, index_2, 5))
		|| (!ft_strncmp(data->lines[index_1]->ops[index_2][0], "/snap", 5) && one_of_those_2(data, index_1, index_2, 5)))
		return (1);
	return (0);
}

void	init_paths(t_pipex *data, int index_1, int index_2)
{
	data->lines[index_1]->paths = ft_calloc(sizeof(char *), (data->lines[index_1]->cmnd_count + 1), data);
	// if (!data->lines[index_1]->paths)
		// return (perror("malloc fail!\n"), error_code(data));
	// data->lines[index_1]->paths[data->lines[index_1]->cmnd_count] = NULL;
	while (++index_2 < data->lines[index_1]->cmnd_count)
	{
		if (is_mini(data, index_1, index_2))
			data->lines[index_1]->paths[index_2] = ft_strdup(data, "minicmnds");
		else if (!ft_strncmp(data->lines[index_1]->ops[index_2][0], "echo", 5))
			data->lines[index_1]->paths[index_2] = ft_strdup(data, "/usr/bin/echo");
		else if (data->lines[index_1]->ops[index_2] && data->lines[index_1]->ops[index_2][0] 
			&& !one_of_those(data, index_1, index_2))
		{
			data->lines[index_1]->paths[index_2] = find_path(data, data->lines[index_1]->ops[index_2][0]);
			if (!data->lines[index_1]->paths[index_2])
				data->lines[index_1]->paths[index_2] = ft_strdup(data, "pathnfound");
		}
		else
			data->lines[index_1]->paths[index_2] = ft_strdup(data, "pathnfound");
		// if (!data->lines[index_1]->paths[index_2])
			// return (perror("malloc fail!\n"), error_code(data));
	}
}

void	init_lines(t_pipex *data)
{
	int i;

	i = -1;
	data->lines = ft_calloc(sizeof(t_lines *), (data->line_count + 1), data);
	// if (!data->lines)
		// return (perror("malloc failed!"), error_code(data));
	// data->lines[data->line_count] = NULL;
	while (++i < data->line_count)
	{
		data->lines[i] = ft_calloc(sizeof(t_lines), 1, data);
		// if (!data->lines[i])
			// return (perror("malloc failed!"), error_code(data));
		data->lines[i]->cmnds = NULL;
		data->lines[i]->ops = NULL;
		data->lines[i]->paths = NULL;
		data->lines[i]->red_cmnd = NULL;
		data->lines[i]->pos_in_line = NULL;
		data->lines[i]->pipes = NULL;
		data->lines[i]->exit_codes = NULL;
		data->lines[i]->cmnd_count = 0;
	}
}

// void	init_lines_2(t_pipex *data, int index_1)
// {
// 	int i;
// 	int j;

// 	i = data->here_2;
// 	j = 0;
// 	while (data->line[i + j] && data->line[i + j] != '\n')
// 		j++;
// 	data->lines[index_1]->cur_line = malloc(sizeof(char) * (j + 1));
// 	if (!data->lines[index_1]->cur_line)
// 		return (perror("malloc failed!"), error_code(data));
// 	data->lines[index_1]->cur_line[j] = 0;
// 	j = -1;
// 	while (data->line[i + ++j] && data->line[i + j] != '\n')
// 		data->lines[index_1]->cur_line[j] = data->line[i + j];
// 	printf("ADD: %s\n", data->lines[index_1]->cur_line);
// 	add_history(data->lines[index_1]->cur_line);
// }

void	init_red_cmnds(t_pipex *data, int index_1)
{
	int j;
	int count;

	j = -1;
	data->lines[index_1]->red_cmnd = ft_calloc(sizeof(int *), (data->lines[index_1]->cmnd_count + 1), data);
	// if (!data->lines[index_1]->red_cmnd)
		// return (perror("malloc failed!"), error_code(data));
	// data->lines[index_1]->red_cmnd[data->lines[index_1]->cmnd_count] = 0;
	while (++j < data->lines[index_1]->cmnd_count)
	{
		count = 0;
		while (count < count_elem(data, index_1, j, data->here_2 - 1))
			count++;
		data->lines[index_1]->red_cmnd[j] = ft_calloc(sizeof(int), (count), data);
		// if (!data->lines[index_1]->red_cmnd[j])
			// return (perror("malloc failed!"), error_code(data));
		// count = 0;
		// while (count < count_elem(data, index_1, j, data->here_2 - 1))
			// data->lines[index_1]->red_cmnd[j][count++] = 0;
	}
}

void	init_pos_in_line(t_pipex *data, int index_1)
{
	int j;
	int count;

	j = -1;
	data->lines[index_1]->pos_in_line = ft_calloc(sizeof(int *), (data->lines[index_1]->cmnd_count + 1), data);
	// if (!data->lines[index_1]->pos_in_line)
		// return (perror("malloc failed!"), error_code(data));
	// data->lines[index_1]->pos_in_line[data->lines[index_1]->cmnd_count] = 0;
	while (++j < data->lines[index_1]->cmnd_count)
	{
		count = 0;
		while (count < count_elem(data, index_1, j, data->here_2 - 1))
			count++;
		data->lines[index_1]->pos_in_line[j] = ft_calloc(sizeof(int), (count), data);
		// if (!data->lines[index_1]->pos_in_line[j])
			// return (perror("malloc failed!"), error_code(data));
		// count = 0;
		// while (count < count_elem(data, index_1, j, data->here_2 - 1))
			// data->lines[index_1]->pos_in_line[j][count++] = 0;
	}
}

void init_fds(t_pipex *data, int index)
{
	int i;

	i = -1;
	while (++i < data->lines[index]->cmnd_count)
		data->lines[index]->fd_infiles[i] = 0;
	i = -1;
	while (++i < data->lines[index]->cmnd_count)
		data->lines[index]->fd_outfiles[i] = 0;
}

void	init_pipes_pids(t_pipex *data, int index)
{
	data->lines[index]->fd_infiles = ft_calloc(sizeof(int), data->lines[index]->cmnd_count, data);
	data->lines[index]->fd_outfiles = ft_calloc(sizeof(int), data->lines[index]->cmnd_count, data);
	init_fds(data, index);
	data->lines[index]->pipes = ft_calloc(sizeof(int[2]), (data->lines[index]->cmnd_count), data);
	data->lines[index]->buf_pipes = ft_calloc(sizeof(int[2]), (data->lines[index]->cmnd_count), data);
	// if (!data->lines[index]->pipes)
		// return (perror("malloc failed"), error_code(data));
    create_pipes(data, index);
	if (data->pid)
	{
		free(data->pid);
		data->pid = NULL;
	}
    data->pid = ft_calloc(sizeof(pid_t), data->lines[index]->cmnd_count, data);
	// if (!data->pid)
		// return (perror("malloc failed"), error_code(data));
}

int	count_nl(t_pipex *data)
{
	int i;

	i = 0;
	// printf("COUNT NL: here_2: %d\n", data->here_2);
	while (data->line[i + data->here_2] && data->line[i + data->here_2] != '\n')
		i++;
	return (i);
}

void	init_lines_2_continue(t_pipex *data, int i)
{
	char *new;
	int j;

	data->buf_int = 0;
	if (i == 0)
	{
		i = count_nl(data);
		data->buf_int = data->here_2_old;
	}
	if (i == data->buf_int)
		data->buf_int = 0;
	// printf("I: %d data->here_2: %d \n", i, (data->buf_int));
    new = ft_calloc(sizeof(char), (i + 1), data);
    // if (!new)
        // return (perror("malloc failed!"), error_code(data));
    // new[i] = 0;
	j = -1;
    while (++j < i)
	{
		new[j] = data->line[data->buf_int + j];
	}
	add_history(new);
    // printf("NEW LINE: %s\n", new);
	free(new);
	new = NULL;
}

void set_old(t_pipex *data, int index_1, int index_2, int index_3)
{
	int k;
	k = 0;

	// printf("PENIS %d | \n", data->line[data->lines[index_1]->pos_in_line[index_2][index_3]]);
	while (data->line[data->lines[index_1]->pos_in_line[index_2][index_3] + k] && data->line[data->lines[index_1]->pos_in_line[index_2][index_3] + k] != '\n')
		k++;
	if (data->line[data->lines[index_1]->pos_in_line[index_2][index_3] + k] == '\n')
		k++;
	// printf("SET OLD TO: %d\n", data->lines[index_1]->pos_in_line[index_2][index_3] + k);
	data->here_2_old = data->lines[index_1]->pos_in_line[index_2][index_3] + k;
}

void init_lines_2(t_pipex *data, int index_1, int i, int j) // this one should find a heredoc; if yes read line till heredoc key if not read till end of line
{
	int check;
	int check_2;

	check = -1;
	check_2 = -1;
    while (data->lines[index_1]->cmnds[++i])
    {
        j = -1;
        while (data->lines[index_1]->cmnds[i][++j])
        {
            // if (check_2 < 0 && !ft_strncmp(data->lines[index_1]->cmnds[i][j], "<<", 3) && !data->lines[index_1]->red_cmnd[i][j])
				// check_2 = j;
            if (!ft_strncmp(data->lines[index_1]->cmnds[i][j], "<<", 3) && !data->lines[index_1]->red_cmnd[i][j])
			{
				check = j;
				check_2 = i;
			}
        }
    }
	if (check < 0)
		init_lines_2_continue(data, 0);
	else
	{
		data->buf_int = data->here_2_old;
		// printf("init_lines_2() SET HERE TO: CALL FOR SETTING the NEWLINE: I: %d | J: %d\n", i , (-j) + 1);
		set_old(data, index_1, check_2, check);
		find_key(data, index_1, check_2, check + 1);
		i = data->here_2 - data->buf_int - 1;
		init_lines_2_continue(data, i + 1);
		data->buf_int = 0;
		// find_key(data, index_1, i, (-j) + 1);
	}
	// printf("I: %d\n", i);
}


void	init_inputs(t_pipex *data, int index)
{
	data->lines[index]->input = ft_calloc(sizeof(char *), data->lines[index]->cmnd_count + 1, data);
	// data->lines[index]->input[data->lines[index]->cmnd_count] = NULL;
}

void	parsing(t_pipex *data)
{
	int i;

	i = -1;
	set_line_count(data);
	init_lines(data);
	if (!syntax_check(data, -1, 0))
		return (write(2, "bash: syntax error near unexpected token `|'\n", 46), data->last_exit_status = 2, add_history(data->line), free_lines(data));
	if (check_open(data->line))
		return (write(2, "bash: syntax error: open quotes \n", 34), data->last_exit_status = 2, add_history(data->line), free_lines(data));
	while (data->lines[++i] && data->here_2_old < data->chars_in_line)
	{
		signal_change(2);
		data->lines[i]->cmnd_count = count_cmnds(data->line + data->here_2, i);
		// printf("CMND COUNT %d\n", data->lines[i]->cmnd_count);
		init_exit_codes(data, data->lines[i]->cmnd_count, i);
		init_red_cmnds(data, i);
		init_inputs(data, i);
		init_pos_in_line(data, i);
		init_cmnds(data, i, -1);
		// print_that_shit(data, i);
		init_lines_2(data, i, -1, 0);
		init_pipes_pids(data, i);
		if (!check_reds(data, i, -1, -1))
			return (free_lines(data));
		init_ops(data, i);
		init_paths(data, i, -1);
		check_folder(data, i);
		set_cur_path(data);
		start_exec(data, i, -1, 0);
	}
	free_lines(data);
}
