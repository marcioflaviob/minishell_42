/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 13:48:28 by trimize           #+#    #+#             */
/*   Updated: 2024/03/16 14:36:02 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	check_commands(int argc, char **argv, t_tmp *tmp)
{
	int		i;
	char	*str;

	i = 0;
	while (i < argc - 3)
	{
		tmp->cmd = (char **)malloc((nb_arg(argv[i + 2]) + 1) * sizeof(char *));
		fill_cmd(tmp->cmd, argv[i + 2], tmp);
		str = find_path(tmp->cmd[0]);
		if (str)
			;
		else
		{
			ft_putstr_fd("command not found: ", 2);
			ft_putstr_fd(argv[i + 2], 2);
			ft_putstr_fd("\n", 2);
		}
		freetab(tmp->cmd);
		free(str);
		i++;
	}
}

void	piping_ex(t_tmp *tmp)
{
	close(tmp->pipe_fd[1]);
	dup2(tmp->pipe_fd[0], STDIN_FILENO);
	close(tmp->pipe_fd[0]);
}

void	open_files(t_tmp *tmp, char **argv, int argc)
{
	tmp->fd_output = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (tmp->fd_output == -1)
		(ft_putstr_fd("Error creating output file\n", 2), free_exit(tmp, 0));
	tmp->fd_error = open("/dev/null", O_WRONLY);
	if (tmp->fd_error == -1)
		(ft_putstr_fd("Trouble redirecting error\n", 2), free_exit(tmp, 0));
	dup2(tmp->fd_input, STDIN_FILENO);
}

void	here_doc_init(t_tmp *tmp, char **argv, int argc)
{
	char	*temp;

	tmp->buffer = ft_strdup("");
	while (1)
	{
		tmp->str_temp = get_next_line(STDIN_FILENO);
		if (ft_strncmp(tmp->str_temp, argv[2], ft_strlen(argv[2])) == 0
			&& tmp->str_temp[ft_strlen(argv[2])] == '\n')
		{
			(free(tmp->str_temp));
			break ;
		}
		temp = ft_strjoin(tmp->buffer, tmp->str_temp);
		free(tmp->buffer);
		tmp->buffer = ft_strdup(temp);
		free(temp);
		free(tmp->str_temp);
	}
	here_doc_piping3(tmp, argv, 3);
	here_doc_piping4(tmp, argv, argc, 4);
	waitpid(tmp->pid_here1, NULL, 0);
	waitpid(tmp->pid_here2, NULL, 0);
	freetab(tmp->env);
	free(tmp->pid);
}

void	here_doc_piping3(t_tmp *tmp, char **argv, int pos)
{
	if (pipe(tmp->pipe_fd) == -1)
		(ft_putstr_fd("pipe error", 2), free_here_doc(tmp));
	if (pipe(tmp->pipe_fd2) == -1)
		(ft_putstr_fd("pipe error", 2), free_here_doc(tmp));
	write(tmp->pipe_fd[1], tmp->buffer, ft_strlen(tmp->buffer));
	(free(tmp->buffer), close(tmp->pipe_fd[1]));
	tmp->cmd = (char **)malloc((nb_arg(argv[pos]) + 1) * sizeof(char *));
	fill_cmd(tmp->cmd, argv[pos], tmp);
	tmp->pid_here1 = fork();
	if (tmp->pid_here1 == -1)
		(ft_printf("Fork error"), free_here_doc(tmp));
	if (!tmp->pid_here1)
	{
		dup2(tmp->pipe_fd[0], STDIN_FILENO);
		(close(tmp->pipe_fd[0]), dup2(tmp->pipe_fd2[1], STDOUT_FILENO));
		(close(tmp->pipe_fd2[1]), close(tmp->pipe_fd2[0]));
		close(tmp->pipe_fd[1]);
		tmp->str = find_path(tmp->cmd[0]);
		execve(tmp->str, tmp->cmd, tmp->env);
		(free(tmp->str), freetab(tmp->env));
		(freetab(tmp->cmd), free(tmp->pid));
		exit(EXIT_FAILURE);
	}
	else
		freetab(tmp->cmd);
}
