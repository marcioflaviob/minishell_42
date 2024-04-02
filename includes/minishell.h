/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 22:47:28 by trimize           #+#    #+#             */
/*   Updated: 2024/04/02 18:07:23 by trimize          ###   ########.fr       */
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

# define RED "\033[1;31m"
# define ORANGE "\e[0;91m"
# define YELLOW "\033[1;33m"
# define GREEN "\033[1;32m"
# define BLUE "\033[1;34m"
# define INDIGO "\033[1;35m"
# define RESET "\033[0m"
# define CYAN_BACK "\033[48;5;9m"

typedef struct s_sh {
	char	*current_dir;
	char	*emoji_path;
	char	**env;
	char	**term_command;
}	t_sh;

int		get_random_number(void);
char	*get_a_line(char *filename, int line_number);
void	get_input(t_sh *sh);
void	print_minishell_art(void);
char	*get_prompt(t_sh *sh);
void	signal_initializer(void);
void	fill_color(char **color);
void	freetab(char **tab);
char	*get_cwd(void);
int		get_type(char *path);
char	*get_curr_dir(char *path);
void	builtin_dealer(t_sh *sh, char *cmd);
void	dollar_sign_dealer(char ***commands);
void	quotes_removal(char ***cmds);
void	new_terminal(t_sh *shell, char *buffer);

//Utils
int		tab_len(char **tab);
char	**ft_better_split(char const *s);
int		ft_isalnum_or_score(int c);
void	ft_strerase(char **str, int start, int num);
char	*ft_stradd(char *str, int start, char *add);
int		is_around_squotes(char *str, int pos);
int		is_around_dquotes(char *str, int pos);
int		find_first_squote_back(char *str, int pos);
void	add_to_tab(char ***tab, char *str);
void	copy_tab(char ***taker, char **giver);
char	*get_substring_b(char *str, char c);
char	*get_substring_a(char *str, char c);
void	rm_tab_line(char ***tab, char *line);
void	print_tab(char **tab);
void	mod_checker(int *checker);

//env functions
char	*get_env(char *str, t_sh *shell);
void	set_env(t_sh *shell);
void	un_set(t_sh *shell, char *str);

//Built-in functions
void	pwd(void);
void	cd(t_sh *sh, char *folder, t_sh *shell);
void	echo(char **args);



#endif