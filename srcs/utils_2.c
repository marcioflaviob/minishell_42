/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:28:48 by trimize           #+#    #+#             */
/*   Updated: 2024/03/16 14:35:56 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h" //ko

void	pipe_init(t_tmp *tmp, char **argv, int argc)
{
	int	i;
	int	err;

	i = 2;
	err = 0;
	tmp->fd_input = open(argv[1], O_RDONLY);
	if (tmp->fd_input == -1)
		(ft_printf("no such file or directory: %s\n", argv[1]), err = 1);
	open_files(tmp, argv, argc);
	while (i < argc - 1)
	{
		if (err == 1)
			(file_1_f(tmp, argv), err = 0);
		else
		{
			tmp->cmd = (char **)malloc((nb_arg(argv[i]) + 1) * sizeof(char *));
			fill_cmd(tmp->cmd, argv[i], tmp);
		}
		piping(i, tmp, argc);
		i++;
		freetab(tmp->cmd);
	}
	i = 0;
	while (i < argc - 3)
		waitpid(tmp->pid[i++], &tmp->status, 0);
}

void	piping(int i, t_tmp *tmp, int argc)
{
	if (pipe(tmp->pipe_fd) == -1)
		(ft_putstr_fd("pipe error", 2), free_exit(tmp, 0));
	tmp->pid[i - 2] = fork();
	if (tmp->pid[i - 2] == -1)
		(ft_printf("Fork error"), free_exit(tmp, 0));
	if (tmp->pid[i - 2])
		piping_ex(tmp);
	else if (!tmp->pid[i - 2])
	{
		if (tmp->fd_input != -1)
			close(tmp->fd_input);
		close(tmp->pipe_fd[0]);
		if (i == argc - 2)
			dup2(tmp->fd_output, STDOUT_FILENO);
		else
			dup2(tmp->pipe_fd[1], STDOUT_FILENO);
		dup2(tmp->fd_error, STDERR_FILENO);
		close(tmp->fd_error);
		close(tmp->fd_output);
		close(tmp->pipe_fd[1]);
		tmp->str = find_path(tmp->cmd[0]);
		execve(tmp->str, tmp->cmd, tmp->env);
		free(tmp->str);
		free_exit(tmp, 0);
	}
}

void	file_1_f(t_tmp *tmp, char **argv)
{
	int	i;
	int	y;
	int	size;

	size = 0;
	i = 0;
	y = 0;
	tmp->cmd = (char **)malloc(3 * sizeof(char *));
	tmp->cmd[1] = ft_strdup(argv[1]);
	while (argv[2][i] != ' ' && argv[2][i])
		i++;
	while (argv[2][i - 1] != '/' && argv[2][i])
	{
		i--;
		size++;
	}
	tmp->cmd[0] = (char *)malloc((size + 1) * sizeof(char));
	while (argv[2][i])
		tmp->cmd[0][y++] = argv[2][i++];
	tmp->cmd[0][y] = 0;
	tmp->cmd[2] = NULL;
}

void	here_doc_piping4(t_tmp *tmp, char **argv, int argc, int pos)
{
	tmp->cmd = (char **)malloc((nb_arg(argv[pos]) + 1) * sizeof(char *));
	fill_cmd(tmp->cmd, argv[pos], tmp);
	tmp->fd_output = open(argv[argc - 1], O_WRONLY
			| O_CREAT | O_TRUNC, 0666);
	if (tmp->fd_output == -1)
		(ft_putstr_fd("Error creating output file\n", 2), free_here_doc(tmp));
	tmp->pid_here2 = fork();
	if (tmp->pid_here2 == -1)
		(ft_printf("Fork error"), free_here_doc(tmp));
	else if (!tmp->pid_here2)
	{
		dup2(tmp->pipe_fd2[0], STDIN_FILENO);
		close(tmp->pipe_fd2[0]);
		dup2(tmp->fd_output, STDOUT_FILENO);
		(close(tmp->fd_output), close(tmp->pipe_fd[1]));
		(close(tmp->pipe_fd[0]), close(tmp->pipe_fd2[1]));
		tmp->str = find_path(tmp->cmd[0]);
		execve(tmp->str, tmp->cmd, tmp->env);
		(free(tmp->str), freetab(tmp->env));
		(freetab(tmp->cmd), free(tmp->pid));
		exit(EXIT_FAILURE);
	}
	(close(tmp->pipe_fd2[1]), close(tmp->pipe_fd[0]));
	(close(tmp->pipe_fd2[0]), close(tmp->fd_output));
	freetab(tmp->cmd);
}
