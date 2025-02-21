/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhocsak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:13:34 by bhocsak           #+#    #+#             */
/*   Updated: 2024/10/08 10:13:39 by bhocsak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdint.h>
# include <limits.h>
# include <signal.h>
# include <errno.h>
# include <dirent.h>
# include <sys/wait.h>
# include <sys/ioctl.h>

typedef struct lines_s
{
	char	***cmnds;
	char	***ops;

	char	**paths;
	char	**input;

	int		**red_cmnd;
	int		**pos;

	pid_t	(*pipes)[2];
	pid_t	(*buf_pipes)[2];

	int		*exit_codes;
	int		*binary;
	int		*fd_infiles;
	int		*fd_ou;

	int		cmnd_count;
	int		ex;
	int		limit;

}	t_lines;

typedef struct pipex_s
{
	struct lines_s		**l;
	char				**cur_env;
	char				**export;
	char				**buf_array;

	char				*line;
	char				*buf_str;

	int					line_count;
	int					chars_in_line;
	int					here_2;
	int					here_2_old;
	int					last_exit_status;
	int					fd_in;
	int					fd_out;
	int					buf_int;
	int					count_elem;
	int					open;
	int					k;
	int					i_2;
	int					fd_in_2;
	int					fd_out_2;

	pid_t				*pid;

}	t_pipex;

extern int	g_signal;

int			main(int argc, char **argv, char **env);
void	print_that_shit(t_pipex *data, int index_1);

//								srcs/

//						exit/

//	close_1.c

void		close_everything(t_pipex *data, int index_1);
void		create_buf_pipe(t_pipex *data, int index_1, int index_2);
void		create_pipes(t_pipex *data, int index);
void		close_childs_p_a(t_pipex *data, int index_1);

int			cl_chi_pipes(t_pipex *data, int index_1, int index_2);

//	close_2.c

void		close_pipe(t_pipex *data, int *fd);
void		close_pipes(t_pipex *data, int index_1, int index_2);
void		close_parent_pipe(t_pipex *data, int *fd);
void		close_children_pipe(t_pipex *data, int *fd);
void		close_pipes_array(t_pipex *data, int index_1);

//	exit_clean.c

void		exit_child(t_pipex *data, int index_1, int index_2, int errnum);
void		er_c(t_pipex *data);

//	free_1.c

void		free_str(char **str);
void		free_line(t_pipex *data, int index);
void		free_lines(t_pipex *data);
void		free_struct(t_pipex *data);

//	free_2.c

void		free_list_list(char ***arr);
void		free_list(char **arr);
void		free_list_int(int **arr, int cmnd_count);

int			free_this(char **str);

//						parsing/

//					init_cmnds/

//	init_cmnds.c

void		fill_cmnds(t_pipex *data, int i, int index_1, int here);
void		ft_strncpy(char *dest, char *src, int size);
void		ft_strncpy_2(char *dest, char *src, int size, t_pipex *data);

int			ft_strlen_2(char *s);

//	init_cmnds_exp_1.c

int			expand_it_1(t_pipex *data, int i, int open, char **new);

//	init_cmnds_exp_2.c

int			check_home(t_pipex *data, int *i, int i_1, int i_2);
int			ex_1_4(t_pipex *data, int i);
int			ex_1_5(t_pipex *data, int i, int open);
int			ex_1_6(t_pipex *data, int i, int open);

//	init_cmnds_exp_3.c

int			expand_it_2(t_pipex *d, int i_1, int i_2, int i_3);

//	init_cmnds_exp_count_1.c

char		*get_pid(t_pipex *data);

int			count_ex(t_pipex *data, int i, int open, int count);

//	init_cmnds_exp_count_2.c

void		c_e_3(t_pipex *data, char **str, int *i);
void		c_e_4(char **elem, int *count);

int			count_elem_spaces(t_pipex *data, char *elem);
int			c_e_5(t_pipex *data, int i, int open);
int			c_e_6(t_pipex *data, int i, int open);

//	init_cmnds_utils_1.c

int			if_1(t_pipex *data, int *j);
int			if_2(t_pipex *data, int j);
int			if_3(t_pipex *data, int j, int i_1, int i);
int			if_4(t_pipex *data, int j);
int			if_5(t_pipex *data, int i, int i_1);

//	init_cmnds_utils_2.c

int			if_6(t_pipex *data, int j, int open);
int			if_7(t_pipex *data, int index_1, int index_2, int i);
int			if_8(t_pipex *data, int index_1, int i);
int			if_9(t_pipex *data, int j);

//	init_cmnds_utils_3.c

int			check_for_empty(t_pipex *data, int i);
int			is_d_b(char *line, int i, int open);
int			is_delim_front(char *line, int i);
int			d_in(t_pipex *data, int j, int open);

//	init_cmnds_utils_4.c

char		*fill_normal(t_pipex *data, int index, int open);
void		fill_for_empty(t_pipex *data, int i_1, int index_2, int index_3);

int			handle_open(t_pipex *data, int j, int *open);
int			flag_empty(int *this, int pos);
int			set_pos(int *to_set, int pos);

//	count_utils.c

int			if_count_elem_1(t_pipex *data, int j);
int			count_chars_utils_2(t_pipex *data, int i, int open, int count);
int			count_chars_utils_1(t_pipex *data, int i, int open, int count);

//	count.c

int			count_cmnds(char *line, int limit);
int			count_elem(t_pipex *data, int i_1, int i, int j);
int			count_chars(t_pipex *data, int i, int open, int count);
int			count_chars_2(t_pipex *data, int i);

//	init_1.c

void		init_cmnds(t_pipex *data, int index_1, int i);
void		init_pipes_pids(t_pipex *data, int index);
void		init_fds(t_pipex *data, int index);
void		init_pos_in_line(t_pipex *data, int index_1);
void		init_red_cmnds(t_pipex *data, int index_1);

//	init_ops.c

void		fill_ops(t_pipex *data, int index_1, int index_2);

int			count_env(char **env);
int			count_reds(t_pipex *data, int index_1, int index_2);
int			count_ops(t_pipex *data, int index_1, int index_2);

//	init_paths.c

char		*find_path(t_pipex *data, char *cmnd);

int			is_mini(t_pipex *data, int index_1, int index_2);
int			is_mini_2(t_pipex *data, int index_1, int index_2);
int			slash_in_cmnd(char *str);

//	make_history.c

void		handle_here(t_pipex *data, int index_1, int i, int j);
void		make_history(t_pipex *data);

int			count_nl(t_pipex *data, int i);

//	one_of_those.c

int			one_of_those(char *str);
int			one_of_those_2(char *str, int count);
int			one_of_those_3(char *str);

//	parsing_utils_1.c

int			is_or(char *cur);
int			is_q_2(char c);
int			is_quote_one(char c);
int			is_quote(char c);
int			is_space(char c);

//	parsing_utils_2.c

int			is_red_in(char *str, int index);
int			is_red_out(char *str, int index);
int			is_red(t_pipex *data, int index_1, int index_2, int index_3);
int			is_red_basic(t_pipex *data, int index_1, int index_2, int index_3);
int			is_red_1(char c);

//	parsing_utils_3.c

int			is_char(char c);
int			check_executable(t_pipex *data, int index_1, int index_2);
int			is_executable(t_pipex *data, int index_1, int index_2);
int			is_red_clean(char *str, int index);

//	parsing_utils_4.c

void		init_rest(t_pipex *data, int i);
void		init_paths_2(t_pipex *data, int i);
void		init_paths_3(t_pipex *data, int i, int j, int k);

int			set_err_old(t_pipex *data);

//	parsing_utils_5.c

int			elem_spaces(t_pipex *data, int i);

//	parsing.c

void		parsing(t_pipex *data, int i);
void		init_ops(t_pipex *data, int index_1);
void		init_paths(t_pipex *d, int i_1, int i_2);

//	util_checks.c

void		check_folder(t_pipex *data, int index, int i, int j);
int			check_folder_utils_1(t_pipex *data, int index, int i);
int			check_folder_utils_2(t_pipex *data, int index, int i, int j);
void		check_folder_utils_3(t_pipex *data, int index, int i);

int			is_real_pipe(char *line, int index);
int			check_reds(t_pipex *data, int index_1, int i, int j);
int			check_open(t_pipex *data, char *line);
int			syntax_check(t_pipex *data, int i, int count);

//						execute/

//				exec_mini/

//	mini_cd_1.c

void		cd_cmnd(char **argv, t_pipex *data, int index_1, int index_2);
void		print_cd_err(int errnum, char *str);
void		update_env_2(t_pipex *data, int index_1, int index_2);

char		*get_pwd(t_pipex *data);

//	mini_cd_2.c

void		update_env(t_pipex *data, int index_1, int index_2);
char		*get_path(t_pipex *data);
char		*get_old(t_pipex *data, int index_1, int index_2);
char		*get_home(t_pipex *data);

//	mini_exit_1.c

void		exit_cmnd_child(t_pipex *data, int index_1, int index_2);
void		exit_cmnd(t_pipex *data, int index_1, int index_2);

//	mini_exit_2.c

void		mini_exit_close_childs(t_pipex *d, int i_1, int i_2);

int			is_overflow(t_pipex *data, int index_1, int index_2);
int			is_overflow_continue(char *str, int sign);
int			only_dec(char *str);

//	mini_export_1.c

void		export_update(t_pipex *data, int index_1, int index_2, int i);

//	mini_export_2.c

void		update_export(t_pipex *data, int index_1, int index_2, int count);

char		*malloc_cpy_export(t_pipex *data, char *str, int track, int i);

//	mini_export_3.c

void		export_env(t_pipex *data, int index_1, int index_2, int count);

//	mini_export_4.c

int			has_equal(char *str);
int			is_it_last(t_pipex *data, int index_1, int index_2, int i);
int			is_there_2(t_pipex *data, char *str);
int			already_there(t_pipex *data, char *str);
int			env_count(t_pipex *data);

//	mini_export_5.c

void		set_rest(t_pipex *data, char **buf);

//	mini_unset_1.c

void		unset_cmnd(t_pipex *data, int index_1, int index_2, int i);

//	mini_unset_2.c

char		*key_this(t_pipex *data, char *s);
char		**malloc_unset(t_pipex *data, int index_1, int index_2);
char		**malloc_unset_export(t_pipex *data, int index_1, int index_2);


//	start_mini_exec_1.c

void		mini_child(t_pipex *data, int index_1, int index_2);
void		parent_child(t_pipex *data, int index_1, int index_2);
void		mini_parent(t_pipex *data, int index_1, int index_2);

int			is_valid_cwd(t_pipex *data);

//	start_mini_exec_2.c

void		export_display(t_pipex *data);
void		print_list(char **arr);
void		print_pwd(t_pipex *data);

int			bigger_one(char *s1, char *s2);

//				start_exec/

//	start_exec_utils_1.c

int			find_key(t_pipex *data, int index_1, int index_2, int index_3);

char		*get_val(t_pipex *data, char *cur);
char		*join_this(char *s1, char *s2, t_pipex *data);
char		*get_input(t_pipex *data, int index_1, int index_2, int index_3);

//	start_exec_utils_2.c

int			here_doc(t_pipex *data, int index_1, int index_2, int i);
int			if_th(t_pipex *data, int index_1, int index_2, int i);

//	start_exec_utils_3.c

void		exec_cmnds_util_3(t_pipex *data, int index, int i);
void		exec_cmnds(t_pipex *data, int index, int i);

int			exec_cmnds_util_1(t_pipex *data, int index, int i);
int			exec_cmnds_util_2(t_pipex *data, int index, int i);

//	start_exec_utils_4.c

int			set_here(t_pipex *data, int index_1);

int			last_one(char **arr);

//	start_exec_utils_5.c

int			open_out(t_pipex *data, int index_1, int index_2);
int			first_invalid_out(t_pipex *data, int index_1, int index_2);
int			first_invalid_in(t_pipex *data, int index_1, int index_2);

//	start_exec_utils_6.c

int			bigger_one_2(int j, int i);
int			check_key(t_pipex *data, char *cur);
int			check_cmnd_as_dir(t_pipex *data, int index, int i);
int			is_valid_in(t_pipex *data, int index_1, int index_2);
int			is_red_inline(t_pipex *data, int index_1, int index_2);

//	start_exec_utils_7.c

int			get_input_2(t_pipex *data, int index_1, int i);

//	start_exec_utils_7.c

int			skip_nl(t_pipex *data);

//	start_exec.c

void		start_exec(t_pipex *data, int index, int i, int status);

//	exec.c

void		exec_cmnd(t_pipex *data, int index_1, int index_2);
void		exec_mini(t_pipex *data, int index_1, int index_2);

int			check_here_doc(t_pipex *data, int index_1, int index_2);

//	exec_utils_1.c

int			open_this_write(t_pipex *data, char *str);
int			open_this_read(t_pipex *data, char *str);
int			is_in_inline(t_pipex *data, int index_1, int index_2);
int			check_here_doc(t_pipex *data, int index_1, int index_2);
int			check_infile(t_pipex *data, int index_1, int index_2);

//	exec_utils_2.c

void		close_in_out_2(t_pipex *d);

int			handle_mini_child_u_2(t_pipex *d, int i_1, int i_2);
int			check_cat_inline(t_pipex *data, int i_1);

//						libft/

//	utils_libft_01.c

void		ft_bzero(void *s, size_t n);

size_t		ft_strlen(const char *str);

char		*ft_strtrim(char *s1, char const *set, t_pipex *data);
char		*ft_strtrim_2(char *s1, t_pipex *data);
char		*ft_strdup_2(t_pipex *data, const char *s);
char		*ft_strdup(t_pipex *data, const char *s);

//	utils_libft_02.c

char		*ft_strchr(const char *s, int c);
char		*ft_strjoin(char const *s1, char const *s2, t_pipex *data);
char		*ft_substr(char *s, unsigned int start, size_t len, t_pipex *data);

int			ft_strcmp_2(char *s1, char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);

//	utils_libft_03.c

void		*ft_calloc(size_t nmemb, size_t size, t_pipex *data);
void		*ft_memcpy(void *dest, const void *src, size_t n);

char		*ft_itoa(int n, t_pipex *data);

size_t		ft_digit_count(long int n);

long long	ft_atoi(const char *nptr);

//	utils_libft_04.c

char		**ft_split(const char *s1, char c);

//	signal_handling_1.c

void		signal_exec_cmnd(int sig);
void		signal_mini_commands(int sig);
void		signal_main(int sig);

//	signal_handling_2.c

void		signal_change(t_pipex *data, int flag);

#endif