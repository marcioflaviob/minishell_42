/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 19:09:24 by trimize           #+#    #+#             */
/*   Updated: 2024/05/14 21:06:58 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redirect(t_sh *sh, char **args)
{
	int	i;
	int	y;
	int	fd_input;
	int	fd_output;
	int	tmp;
	int	error_out;
	int	error_in;

	fd_output = 0;
	fd_input = 0;
	i = 0;
	error_in = 1;
	error_out = 1;
	y = find_sp(&args[i], sh);
	while (ft_equalstr(args[y], "<") || ft_equalstr(args[y], ">") || ft_equalstr(args[y], ">>"))
	{
		tmp = i;
		if (args[y] && ft_equalstr(args[y], "<"))
		{
			i += find_sp(&args[i], sh) + 1;
			fd_input = open(args[i], O_RDONLY);
			if (fd_input == -1)
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(args[i], 2);
				ft_putstr_fd(": No such file or directory\n", 2);
				error_in = 0;
			}
		}
		if (args[y] && ft_equalstr(args[y], ">"))
		{
			i += find_sp(&args[i], sh) + 1;
			fd_output = open(args[i], O_WRONLY | O_CREAT | O_TRUNC, 0666);
			if (fd_output == -1)
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(args[i], 2);
				ft_putstr_fd(": Permission denied\n", 2);
				error_out = 0;
			}
		}
		if (args[y] && ft_equalstr(args[y], ">>"))
		{
			i += find_sp(&args[i], sh) + 1;
			fd_output = open(args[i], O_WRONLY | O_CREAT | O_APPEND, 0666);
			if (fd_output == -1)
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(args[i], 2);
				ft_putstr_fd(": Permission denied\n", 2);
				error_out = 0;
			}
		}
		sh->position += i - tmp;
		y = find_sp(&args[i], sh) + i;
	}
	if (args[y]
		&& ft_equalstr(args[y], "|") && !fd_output)
		dup2(sh->pipe[1], STDOUT_FILENO);
	else if (args[y]
		&& ft_equalstr(args[y], "|") && fd_output)
		sh->position = y;
	if (!error_in || !error_out)
		return (0);
	if (fd_output != -1)
		(dup2(fd_output, STDOUT_FILENO), close(fd_output));
	if (fd_input && fd_input != -1)
		(dup2(fd_input, STDIN_FILENO), close(fd_input));
	return (1);
}

void	echo_parent(t_sh *sh, t_exe *exe, char **args)
{
	exe->i = 0;
	if (sh->position + find_sp(args, sh) == sh->pipe_par_bool)
	{
		if (pipe(sh->pipe_par) != 0)
			(perror("pipe error"), exit(EXIT_FAILURE));
		write(sh->pipe_par[1], exe->str, ft_strlen(exe->str));
		write(sh->pipe_par[1], "\x04", 1);
		close(sh->pipe_par[1]);
	}
	else
	{
		if (pipe(sh->pipe) != 0)
			(perror("pipe error"), exit(EXIT_FAILURE));
		write(sh->pipe[1], exe->str, ft_strlen(exe->str));
		write(sh->pipe[1], "\x04", 1);
		close(sh->pipe[1]);
	}
	if (find_sp(args, sh) == 0)
		sh->position = tab_len(sh->args) - 1;
	else
		sh->position += find_sp_par(args, sh);
}

void	echo_parent_2(t_sh *sh, t_exe *exe, char **args)
{
	if (!redirect(sh, args))
	{
		sh->last_cmd_st = 1;
		sh->position += find_non_redir(&(sh->args[sh->position]), sh);
	}
	else
	{
		if (!sh->args[sh->position + 1])
		{
			write(1, exe->str, (ft_strlen(exe->str)));
			free(exe->str);
			sh->position = tab_len(sh->args) - 1;
		}
		else if (ft_equalstr(sh->args[sh->position], "|")
			|| ft_equalstr(sh->args[sh->position], "||")
			|| ft_equalstr(sh->args[sh->position], "&&"))
		{
			write(1, exe->str, (ft_strlen(exe->str)));
			free(exe->str);
		}
		else
		{
			write(1, exe->str, (ft_strlen(exe->str) - 1));
			if (exe->str && exe->str[0] != '\n')
				write(1, " ", 1);
			free(exe->str);
			echo_parent_4(sh, exe, &sh->args[(sh->position)]);
		}
	}
}

void	echo_parent_3(t_sh *sh, t_exe *exe, char **args)
{
	sh->fd_output = open(args[find_sp(args, sh) + 1],
			O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (sh->fd_output == -1)
		ft_putstr_fd("Couldn't open file.\n", 2);
	write(sh->fd_output, exe->str, ft_strlen(exe->str));
	close(sh->fd_output);
	if (find_sp(args, sh) == 0)
		sh->position = tab_len(sh->args) - 1;
	else
		sh->position += find_sp(args, sh) + 2;
}

void	echo_parent_4(t_sh *sh, t_exe *exe, char **args)
{
	if (sh->out_par)
		(dup2(sh->fd_output, STDOUT_FILENO));
	exe->str = echo(args, sh);
	sh->last_cmd_st = 0;
	sh->bool_result = 1;
	if (ft_equalstr(args[find_sp(args, sh)], "|"))
		echo_parent(sh, exe, args);
	else if (ft_equalstr(args[find_sp_echo(args)], ">")
		|| ft_equalstr(args[find_sp_echo(args)], ">>")
		|| ft_equalstr(args[find_sp_echo(args)], "<"))
		echo_parent_2(sh, exe, args);
	else
	{
		ft_putstr_fd(exe->str, 1);
		if (find_sp(args, sh) == 0)
			sh->position = tab_len(sh->args) - 1;
		else
			sh->position += find_sp_par(args, sh);
		free(exe->str);
	}
}

