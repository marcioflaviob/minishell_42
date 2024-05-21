/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 19:09:24 by trimize           #+#    #+#             */
/*   Updated: 2024/05/21 17:19:02 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	echo_parent(t_sh *sh, t_exe *exe, char **args)
{
	exe->i = 0;
	if (sh->position + find_sp(args, sh) == sh->pipe_par_bool)
	{
		if (pipe(sh->pipe_par) != 0)
			(perror("pipe error"), child_free(sh), exit(EXIT_FAILURE));
		write(sh->pipe_par[1], exe->str, ft_strlen(exe->str));
		close(sh->pipe_par[1]);
	}
	else
	{
		if (pipe(sh->pipe) != 0)
			(perror("pipe error"), child_free(sh), exit(EXIT_FAILURE));
		write(sh->pipe[1], exe->str, ft_strlen(exe->str));
		close(sh->pipe[1]);
	}
	if (find_sp(args, sh) == 0)
		sh->position = tab_len(sh->args) - 1;
	else
		sh->position += find_sp_par(args, sh);
}

void	echo_par_2_help(t_sh *sh, t_exe *exe)
{
	if (ft_equalstr(sh->args[sh->position], "|")
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
		else
			echo_par_2_help(sh, exe);
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
	dup2(sh->true_stdin, STDIN_FILENO);
	exe->str = echo(args, sh);
	sh->last_cmd_st = 0;
	sh->bool_result = 1;
	if (ft_equalstr(args[find_sp_echo(args, sh)], ">")
		|| ft_equalstr(args[find_sp_echo(args, sh)], ">>")
		|| ft_equalstr(args[find_sp_echo(args, sh)], "<")
		|| ft_equalstr(args[find_sp_echo(args, sh)], "|"))
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
