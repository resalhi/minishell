/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ressalhi <ressalhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 12:53:18 by ressalhi          #+#    #+#             */
/*   Updated: 2022/08/23 19:24:36 by ressalhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <dirent.h>
# include <termios.h>
# include <fcntl.h>

# define SPLIT_TOKEN 127
# define INPUT 1
# define OUTPUT 2
# define HERDOC 3
# define APPEND 4

typedef struct s_red
{
	int		type;
	char	*file;
}		t_red;

typedef struct s_data
{
	int		fd[2];
	int		sign;
	char	*cmd;
	char	**args;
	int		num_red;
	t_red	*red;
}	t_data;

typedef struct s_parse
{
	t_data	*data;
	char	**env;
	int		num_data;
	int		dqoute;
	int		sqoute;
	int		i;
	int		j;
}		t_parse;

typedef struct pipex_bonus
{
	char	*paths;
	char	*cmd_path;
	char	*all_line;
	char	**argv;
	int		out;
	int		cmd_number;
	int		file_inpt;
	int		file_outpt;
	int		file_appnd;
	int		fd[2];
	int		hr_dc[2];
	int		save[2];
	int		in_err;
	int		out_err;
	int		*wait_id;
	int		id;
	char	*limiter;
	int		dup_hd;
	int		idx;
}		t_pipex;

typedef struct s_global
{
	int	g_herd;
	int	g_status;
	int	g_conti;
	int	g_id;
	int	g_i;
	int	g_j;
}		t_global;

t_global	g_status;

void	sig_int(int sign);
char	**ft_split(char *s, char c);
char	*ft_itoa(int n);
size_t	ft_strlen(char *s);
char	*ft_strdup(char *s1);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strjoin2(char *s1, char *s2);
char	*ft_strjoin3(char *s1, char *s2);
char	**expanding(char **tab);
char	*expand(char *str);
void	expaaaand(char *s, char *str, int *i, int *j);
void	expand_noqoute(char *s, char *str, int *i, int *j);
void	expand_sqoute(char *s, char *str, int *i, int *j);
void	expand_dqoute(char *s, char *str, int *i, int *j);
char	*expand_status(char *str);
void	ft_error(char *str);
char	**ft_env(char **env);
int		dollar(t_parse *parse, int len);
char	*dollar_hundler(char *str, t_parse *parse);
int		dollar_dqoutes2(char *s, char *str, t_parse *parse);
void	dollar_dqoutes(char *s, char *str, t_parse *parse);
void	fill_str2(char *s, char *str, t_parse *parse, char c);
char	*dollar_fill(char *str, t_parse *parse, char *s1);
void	fill_str(char *s1, char *s, t_parse *parse);
int		variable_count(char *str, t_parse *p);
void	variable_c(char *str, int *count, int *i, t_parse *p);
char	*env_cher(char *s1, char **env);
char	*remove_qoutes(char *str);
int		check_errors(char *str);
int		check_errors3(char *str, int *i);
int		check_error2(char *str, int *i);
int		check_pipes(char *str);
char	*str_to_split(char *str, char c);
char	*str_to_split2(char *str, char c);
char	**error_management(char *str, t_parse *parse);
int		parsing2(char **t, t_parse *parse, int i);
void	clean_red(t_parse *p, int i);
int		parsing(char **tab, t_parse *p);
int		parser(char *str, t_parse *parse);
int		redirections_append(t_data *data, char **tab, int i, int *j);
int		redirections_herdoc(t_data *data, char **tab, int i, int *j);
int		redirections_output(t_data *data, char **tab, int i, int *j);
int		redirections_input(t_data *data, char **tab, int i, int *j);
char	**redirections2(char **tab, char **t, t_data *data);
char	**redirections(char **tab, t_data *data);
void	remove_qoutes2(char *str, char *s, int *i, int *j);
void	remove_qoutes3(char *str, char *s, int *i, int *j);
char	*remove_qoutes(char *str);
char	**remove_qoute(char **tab);
int		remove_trash(t_parse *parse, int j);
int		count_red(char **str);
void	ft_free_tab(char **tab);
int		check_qoutes(char **tab, t_parse *parse);
int		check_qoutes2(char *str, t_parse *parse);
int		check_qoutes3(char *str, int i, t_parse *parse, char c);
int		skipping_qoutes(char *str, int *i);
void	ft_export(char **tab, t_parse *parse);
void	modify_variable(char *str, char **env, int index);
char	**add_variables(char *str, char **env);
int		get_index(char *str, char **env);
int		check_valid(char *str);
int		check_valid2(char *str);
void	add_print_declare(char **env);
void	sort_env(char **env);
void	print_tab(char **tab, int n);
void	ft_echo(char **tab);
void	ft_unset(char **tab, t_parse *parse);
char	**ft_unset2(char *str, char **env);
void	rl_replace_line(char *s, int h);
void	ft_pwd(t_parse *p);
void	print_env(t_parse *parse);
void	ft_cd(char **tab, t_parse *parse);
void	modify_oldpwd(char **env);
int		cher_home(char *s, char **env);
void	ft_exit(char **tab);
int		ft_isalnum(int c);
void	excute_builtins(char **comd, t_parse *parse);
char	*env_cher2(char *s1, char **env);
int		count_status(char *str);
void	count_status2(char *str, int *i, int *count);

/*--------------------------------------------------------------------*/

int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin_p(char *s1, char *s2);
char	**ft_paths(char **env);
size_t	ft_strlcpy(char *dst, const char *src, size_t len);
char	*get_next_line(int fd);
char	*ft_substr(char *s, int start, int len);
char	*find_nl(char *buffer);
char	**join_args(t_parse *parse, int i);
int		count_args(t_parse *parse, int i);
int		here_doc(t_parse *parse, char *limiter, int i);
void	ft_begin(t_parse *parse, t_pipex *t_pipe);
void	start(t_parse *parse, int i, t_pipex *t_pipe, char **env);
void	do_command(t_parse *parse, int i, char **comd);
void	commands(t_parse *parse, t_pipex *t_pipe);
char	*join_data(char *s1, char *s2);
void	h_d(t_parse *parse);
int		count_h_d(t_parse *parse);
void	open_files(t_parse *parse);
int		check_red(t_parse *parse, t_pipex *t_pipe, int i);
void	close_extra_files(t_pipex *t_pipe);
int		check_for_builtins(t_parse *parse, t_pipex *t_pipe);
int		find_here_d(t_parse *parse, int i);
void	wait_cmd(t_pipex *t_pipe, t_parse *parse);
void	set_red(t_parse *parse, t_pipex *t_pipe, int i);
int		not_builtins(t_parse *parse, int i);
void	input_file(t_parse *parse, t_pipex *t_pipe, int i, int c);
void	output_file(t_parse *parse, t_pipex *t_pipe, int i, int c);
void	append_file(t_parse *parse, t_pipex *t_pipe, int i, int c);
void	child_else(t_parse *parse, t_pipex *t_pipe, int i, char **comd);
void	ft_pattern(t_parse *parse, int i);
void	ft_parent(t_pipex *t_pipe, t_parse *parse, int i);
void	protection(char *comd);
void	check_child_built(t_parse *parse, char **comd);
void	first_last(t_parse *parse, t_pipex *t_pipe, int i);
void	ft_free2(char **cmd);
void	input_permission(t_parse *parse, t_pipex *t_pipe, int i, int c);
void	initializing(t_pipex *t_pipe, t_parse *parse, char **env);
void	ft_default(t_pipex *t_pipe);
void	childs_room(t_pipex *t_pipe);
int		hd_duty(t_parse *parse, int i, int c);
int		check_space(char *str);
int		check(char *str);
void	cher_home_err(void);

#endif
