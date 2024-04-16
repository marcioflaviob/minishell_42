/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 22:47:28 by trimize           #+#    #+#             */
/*   Updated: 2024/04/16 19:50:54 by mbrandao         ###   ########.fr       */
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

# define RED "\033[1;31m"
# define ORANGE "\e[0;91m"
# define YELLOW "\033[1;33m"
# define GREEN "\033[1;32m"
# define BLUE "\033[1;34m"
# define INDIGO "\033[1;35m"
# define RESET "\033[0m"
# define CYAN_BACK "\033[48;5;9m"

extern int		g_signal;

typedef struct s_wc {
	char	*segment;
	int		pos;
}	t_wc;

typedef struct s_sh {
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
	t_wc	*wc;
}	t_sh;

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
int		get_type(char *path);
char	*get_curr_dir(char *path);
//void	builtin_dealer(t_sh *sh, char *cmd);
void	dollar_sign_dealer(char ***commands, t_sh *sh);
void	quotes_removal_helper(char **str);
void	quotes_removal(char ***cmds);
void	new_terminal(t_sh *shell, char *buffer);

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
void	add_to_tab_pos(char ***tab, char *str, int pos);
void	remove_from_tab(char ***tab, int pos);
void	copy_tab(char ***taker, char **giver);
char	*get_substring_b(char *str, char c);
char	*get_substring_a(char *str, char c);
void	rm_tab_line(char ***tab, char *line);
void	print_tab(char **tab);
void	mod_checker(int *checker);
int		ft_strlen_gnl(const char *s);
char	*ft_strjoin_gnl(char *s1, char *s2);
char	*get_var_name(char *str);

//Redirection functions
void	redir_out_trunc(char *outfile, char **args, t_sh *sh);
void	redir_out_app(char *outfile, char **args, t_sh *sh);
void	redir_out_trunc_p(char *outfile, char **args, t_sh *sh);
void	redir_out_app_p(char *outfile, char **args, t_sh *sh);
void	redir_in(char *infile, char **args, t_sh *sh);
char	*redir_in_heredoc(char *delimiter);

//env functions
char	*get_env(char *str, t_sh *shell);
void	set_env(t_sh *shell);

//Parsing functions
void	arg(t_sh *sh);
int		find_sp(char **args, t_sh *sh);
int		check_sp_afpar(char **args);

//Built-in functions
void	pwd(void);
void	cd(t_sh *sh, char *folder);
void	echo(char **args, t_sh *sh);
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


#endif