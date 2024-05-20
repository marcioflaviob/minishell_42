/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 22:47:28 by trimize           #+#    #+#             */
/*   Updated: 2024/05/20 12:47:19 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include <signal.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <dirent.h>
# include <wait.h>
# include <errno.h>

# define RED "\033[1;31m"
# define ORANGE "\e[0;91m"
# define YELLOW "\033[1;33m"
# define GREEN "\033[1;32m"
# define BLUE "\033[1;34m"
# define INDIGO "\033[1;35m"
# define RESET "\033[0m"
# define CYAN_BACK "\033[48;5;9m"

extern int		g_signal;

typedef struct e_h
{
	int	fd_input;
	int	fd_output;
	int	i;
	int	y;
	int	position;
}	t_h;

typedef struct redir
{
	int	i;
	int	y;
	int	fd_input;
	int	fd_output;
	int	tmp;
	int	error_out;
	int	error_in;
}	t_redir;

typedef struct exe
{
	pid_t	pid;
	pid_t	pid2;
	int		i;
	char	*str;
	char	**cmd;
}	t_exe;

typedef struct pars
{
	int		special;
	int		fd;
	char	*buffer;
	char	*tmp;

}	t_pars;

typedef struct exp
{
	int		i;
	int		y;
	int		str_len;
	int		replace;
	char	*str1;
	char	*str2;
}	t_exp;

typedef struct c_args
{
	int	i;
	int	args;
	int	quote_flag;
}	t_c_args;

typedef struct s_wc
{
	char	*segment;
	char	*found_position;
	char	*current_position;
	int		pos;
}	t_wc;

typedef struct s_segfill
{
	int		i;
	int		j;
	int		x;
	int		seg_count;
	int		in_quotes;
	char	quote_char;
}	t_segfill;

typedef struct s_segcheck
{
	int		fd[2];
	int		i;
	int		pos;
	int		char_pos;
	pid_t	pid;
	char	**result;
	char	*buffer;
	char	*tmp;
	char	**cmd;
	t_wc	*wc;
}	t_segcheck;

typedef struct s_sh
{
	int		echo_i;
	int		echo_y;
	int		pipe[2];
	int		pipe_par[2];
	int		inside_par;
	int		out_par;
	int		pipe_par_bool;
	int		position;
	int		fd_input;
	int		fd_output;
	int		true_stdin;
	int		true_stdout;
	int		pipe_pos;
	int		last_cmd_st;
	int		refresh;
	int		bool_result;
	int		op_pipe;
	char	*wrong_file;
	int		pipe_read[2];
	int		pipe_write[2];
	int		*sp_bool;
	char	*current_dir;
	char	*emoji_path;
	char	**args;
	char	**env;
	char	**variables;
	char	**term_command;
	pid_t	parent_pid;
	t_wc	*wc;
}	t_sh;

void	before_command(void);

int		get_random_number(void);
char	*get_a_line(char *filename, int line_number);
void	get_input(t_sh *sh);
void	print_minishell_art(void);
char	*get_prompt(t_sh *sh);
void	signal_initializer(void);
void	fill_color(char **color);
char	*find_path(char *command, t_sh *sh);
void	freetab(char **tab);
char	*get_cwd(void);
void	segment_fill_2(char *input, t_segfill *s);
void	segment_fill(t_wc **wc, char *input, t_sh *sh);
void	wildcard_finder(char ***tab, t_wc *wc, t_sh *sh);
int		get_type(char *path);
char	*get_curr_dir(char *path);
//void	builtin_dealer(t_sh *sh, char *cmd);
void	dollar_sign_dealer(char ***commands, t_sh *sh);
void	quotes_removal_helper(char **str);
void	quotes_removal(char ***cmds);
void	new_terminal(t_sh *shell, char *buffer);
void	initialize(int *i, int *j);
//Utils
int		tab_len(char **tab);
char	**ft_better_split(char *s);
int		ft_isalnum_or_score(int c);
void	ft_strerase(char **str, int start, int num);
char	*ft_stradd(char *str, int start, char *add);
int		is_around_squotes(char *str, int pos);
int		is_around_dquotes(char *str, int pos);
int		is_quoted(char *str, int i);
void	space_adder(char **str);
int		find_first_squote_back(char *str, int pos);
void	add_to_tab(char ***tab, char *str);
void	add_to_tab_pos(char ***tab, char *str, int pos, t_sh *sh);
void	remove_from_tab(char ***tab, int pos, t_sh *sh);
void	copy_tab(char ***taker, char **giver);
char	*get_substring_b(char *str, char c, t_sh *sh);
char	*get_substring_a(char *str, char c, t_sh *sh);
void	rm_tab_line(char ***tab, char *line, t_sh *sh);
int		ft_part_len(char *str, char c);
int		is_alscore_str(char *str);
int		is_num_str(char *str);
void	print_tab(char **tab);
void	mod_checker(int *checker);
int		ft_strlen_gnl(const char *s);
char	*ft_strjoin_gnl(char *s1, char *s2);
char	*get_var_name(char *str);
char	*sorted_tab(char **tab);
void	sort_strings_by_first_char(char **arr, int n);
int		check_special_redirect(char *str);

int		find_sp_redir(char **args, t_sh *sh, int j);
int		find_sp_echo(char **args);
int		find_non_redir(char **args, t_sh *sh);

int		redirect(t_sh *sh, char **args);

void	exec_cmd_3(t_sh *sh, t_exe *exe, char **args);
void	exec_cmd_2(t_sh *sh, t_exe *exe, char **args);
void	exec_cmd_4(t_sh *sh, t_exe *exe, char **args);
void	exec_cmd_5(t_sh *sh, t_exe *exe, char **args);
void	exec_cmd_6(t_sh *sh, t_exe *exe, char **args);
void	exec_cmd_7(t_sh *sh, t_exe *exe, char **args);
void	exec_cmd_8(t_sh *sh, t_exe *exe, char **args);
void	exec_cmd_9(t_sh *sh, t_exe *exe, char **args);
void	exec_cmd_10(t_sh *sh, t_exe *exe, char **args);
void	exec_cmd_11(t_sh *sh, t_exe *exe);
void	exec_cmd_12(t_sh *sh, t_exe *exe, char **args);
void	exec_cmd_13(t_sh *sh, t_exe *exe);
void	exec_cmd_14(t_sh *sh, t_exe *exe, char **args);
void	exec_cmd_15(t_sh *sh, t_exe *exe, char **args);
void	exec_cmd_18(t_sh *sh, t_exe *exe, char **args);
void	echo_parent_4(t_sh *sh, t_exe *exe, char **args);
void	pwd_parent_5(t_sh *sh, t_exe *exe, char **args);
void	env_parent(t_sh *sh, char **args);
void	env_parent_4(t_sh *sh, t_exe *exe, char **args);
void	env_parent_5(t_sh *sh, t_exe *exe, char **args);
void	env_parent_7(t_sh *sh, t_exe *exe, char **args);
void	export_parent_4(t_sh *sh, t_exe *exe, char **args);
void	exit_parent(t_sh *sh, t_exe *exe, char **args);
void	unset_parent(t_sh *sh, char **args);
void	child_cmd_handler(t_sh *sh, t_exe *exe, char **args);
void	cd_parent_2(t_sh *sh, char **args);
int		is_builtin(char *str);
char	**cmd_args(t_sh *sh, char **args);
void	child_free(t_sh *sh);

//Redirection functions
void	redir_out_trunc(char *outfile, char **args, t_sh *sh);
void	redir_out_app(char *outfile, char **args, t_sh *sh);
void	redir_out_trunc_p(char *outfile, char **args, t_sh *sh);
void	redir_out_app_p(char *outfile, char **args, t_sh *sh);
void	redir_in(char *infile, char **args, t_sh *sh);
char	*redir_in_heredoc(char *delimiter, t_sh *sh);
int		ft_tabchr(char **tab, char c);
char	*ft_strstr_wc(char *str, char *to_find);
void	clean_gnl(int fd);

//env functions
char	*get_env(char *str, t_sh *shell);
void	set_env(t_sh *shell);
void	add_env(t_sh *sh, char *variable);

//Parsing functions
void	arg(t_sh *sh);
void	arg_2(t_pars *pars, t_sh *sh);
void	arg_3(t_sh *sh);
void	arg_4(t_sh *sh);
void	arg_5(t_sh *sh);
void	arg_6(t_sh *sh);
void	arg_7(t_pars *pars, t_sh *sh);
void	arg_8(t_pars *pars, t_sh *sh);
void	arg_9(t_pars *pars, t_sh *sh);
void	arg_10(t_sh *sh);
void	arg_11(t_sh *sh);
void	arg_12(t_sh *sh);
void	arg_13(t_pars *pars, t_sh *sh);
void	arg_14(t_sh *sh);
void	arg_15(t_sh *sh);
void	arg_16(t_sh *sh);
int		go_af_par(char **args);
int		check_sp_afpar(char **args);
int		check_special(char *str, t_sh *sh);
int		arg_checker(char *str, t_sh *sh);
int		ft_find_first(const char *s, int c);
int		count_args(char const *str);
int		find_sp(char **args, t_sh *sh);
int		check_sp_afpar(char **args);
int		find_sp_par(char **args, t_sh *sh);
int		par_check_all(char **str, t_sh *sh);

//Built-in functions
void	pwd(void);
int		cd(t_sh *sh, char *folder);
char	*echo(char **args, t_sh *sh);
void	export(t_sh *shell, char **str);
void	un_set(t_sh *shell, char **str);
void	env(t_sh *shell);

//Command functions
void	exec_cmd(char **args, t_sh *sh);
int		wildcard(t_sh *sh);
int		ft_int_strchr(const char *s, int c);
void	replace_env(char **str, t_sh *sh);
int		ft_int_strstr_wc(char *str, char *to_find);
int		find_sp_str(char *str);
void	replace_var(t_sh *sh, char ***tab);
void	set_sp_bool(t_sh *sh);

// Term config
void	term_config(void);
void	term_reset(void);

#endif