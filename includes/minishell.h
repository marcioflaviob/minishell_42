/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 22:47:28 by trimize           #+#    #+#             */
/*   Updated: 2024/03/30 23:30:49 by mbrandao         ###   ########.fr       */
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
}	t_sh;

int		get_random_number(void);
char	*get_a_line(char *filename, int line_number);
char	*get_input(void);
void	print_minishell_art(void);
char	*get_prompt(void);
void	signal_initializer(void);
void	fill_color(char **color);
void	freetab(char **tab);
char	*get_cwd(void);
int		get_type(char *path);
char	*get_curr_dir(char *path);

//Utils
int		tab_len(char **tab);
void	str_add(char *str, char *add);

//Built-in functions
void	pwd(void);
void	cd(t_sh *sh, char *folder);
void	echo(char **args);



#endif