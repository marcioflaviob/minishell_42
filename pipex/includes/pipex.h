/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 13:40:18 by teorimize         #+#    #+#             */
/*   Updated: 2024/04/03 18:39:46 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../../libft/libft.h"
# include "../../get_next_line/get_next_line.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>
# include <stdint.h>
# include <stdio.h>

typedef struct s_tmp
{
	int		fill_y;
	int		fill_z;
	int		fill_i;
	int		fd_input;
	int		fd_output;
	int		fd_error;
	int		pipe_fd[2];
	int		pipe_fd2[2];
	int		status;
	char	*buffer;
	char	**cmd;
	char	**env;
	char	*lang;
	char	*lcall;
	char	*str;
	char	*str_temp;
	pid_t	*pid;
	pid_t	pid_here1;
	pid_t	pid_here2;
}	t_tmp;

/*int		nb_arg(char *str);
int		ispath(char *command);
void	ft_firstpipe(t_tmp *tmp, char **argv);
void	is_builtin(t_tmp *tmp);
void	ft_strcpy(char *dest, const char *src);
void	ft_strcat(char *dest, const char *src);
void	add_line(char ***strs, char *buffer, int *size);
void	ft_pipe(t_tmp *tmp, int argc, char **argv);
void	find_path2(t_tmp *tmp);
char	**here_doc(char **argv, t_tmp *tmp);
char	*find_path(char *command, t_tmp *tmp);
char	*find_path1(t_tmp *tmp, char *command);
void	emulate_here_doc1(t_tmp *tmp, char **argv);
void	emulate_here_doc(char **input, char **argv, t_tmp *tmp);
void	emulate_here_doc2(t_tmp *tmp, char **argv);
void	emulate_here_doc3(t_tmp *tmp, char **input);
void	fill_cmd(char **cmd, char *str, t_tmp *tmp);
void	ft_pipe1(t_tmp *tmp, char **argv);
void	ft_pipe2(t_tmp *tmp, char **argv, int argc);
void	freestringarray(char **array);*/
int		nb_arg(char *str);
char	*find_path(char *command);
void	free_exit(t_tmp *tmp, int finish);
void	fill_cmd_ex(char **cmd, char *str, t_tmp *tmp);
void	fill_cmd(char **cmd, char *str, t_tmp *tmp);
void	freetab(char **array);
void	pipe_init(t_tmp *tmp, char **argv, int argc);
void	piping(int i, t_tmp *tmp, int argc);
void	file_1_f(t_tmp *tmp, char **argv);
void	free_exit_main(t_tmp *tmp);
void	check_commands(int argc, char **argv, t_tmp *tmp);
void	piping_ex(t_tmp *tmp);
void	open_files(t_tmp *tmp, char **argv, int argc);
void	here_doc_init(t_tmp *tmp, char **argv, int argc);
void	here_doc_piping3(t_tmp *tmp, char **argv, int pos);
void	here_doc_piping4(t_tmp *tmp, char **argv, int argc, int pos);
void	free_here_doc(t_tmp *tmp);

#endif