/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 19:03:47 by trimize           #+#    #+#             */
/*   Updated: 2024/05/29 17:10:44 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_cmd_6(t_sh *sh, t_exe *exe, char **args)
{
	exe->i = find_sp(args, sh);
	if (sh->out_par)
		(dup2(sh->fd_output, STDOUT_FILENO), close(sh->fd_output));
	else
		redir_out_app(args[find_sp(args, sh) + 1],
			&args[find_sp(args, sh)], sh);
	if (!find_sp(&args[find_sp(args, sh) + 1], sh))
		;
	else if (ft_equalstr(args[find_sp(&args[find_sp(args, sh) + 1],
					sh) + exe->i + 1], "|")
		&& find_sp(&args[find_sp(args, sh) + 1],
			sh) + exe->i + 1 != check_sp_afpar(args))
		exec_cmd_5(sh, exe, args);
	else if (ft_equalstr(args[find_sp(&args[find_sp(args, sh) + 1],
					sh) + exe->i + 1], "|")
		&& find_sp(&args[find_sp(args, sh) + 1],
			sh) + exe->i + 1 == check_sp_afpar(args))
		(write(sh->pipe_par[1], "", 0), close(sh->pipe_par[0]),
			close(sh->pipe_par[1]));
	if (sh->fd_input != -2)
		close(sh->fd_input);
	(close(sh->pipe[0]), close(sh->pipe[1]));
	exe->cmd = cmd_args(sh, args);
	execve(exe->cmd[0], exe->cmd, sh->env);
	(child_free(sh), exit(EXIT_FAILURE));
}

void	exec_cmd_7(t_sh *sh, t_exe *exe, char **args)
{
	if (sh->fd_input != -2)
		close(sh->fd_input);
	if (sh->fd_output != -2)
		close(sh->fd_output);
	if (sh->pipe_par_bool == find_sp(args, sh) + sh->position)
		(dup2(sh->pipe_par[1], STDOUT_FILENO),
			close(sh->pipe_par[1]), close(sh->pipe_par[0]));
	else
	{
		close(sh->pipe[0]);
		dup2(sh->pipe[1], STDOUT_FILENO);
		close(sh->pipe[1]);
	}
	exe->cmd = cmd_args(sh, args);
	if (sh->wrong_file != NULL)
		add_to_tab(&exe->cmd, sh->wrong_file);
	close(sh->true_stdin);
	close(sh->true_stdout);
	execve(exe->cmd[0], exe->cmd, sh->env);
	child_free(sh);
	exit(EXIT_FAILURE);
}

void	exec_cmd_8(t_sh *sh, t_exe *exe, char **args)
{
	if (sh->fd_input != -2)
		close(sh->fd_input);
	if (sh->pipe_par_bool)
	{
		dup2(sh->pipe_par[1], STDOUT_FILENO);
		close(sh->pipe_par[1]);
		close(sh->pipe_par[0]);
	}
	else if (sh->out_par && sh->position < sh->out_par)
		dup2(sh->fd_output, STDOUT_FILENO);
	if (sh->fd_output != -2)
		close(sh->fd_output);
	close(sh->pipe[0]);
	close(sh->pipe[1]);
	exe->cmd = cmd_args(sh, args);
	execve(exe->cmd[0], exe->cmd, sh->env);
	child_free(sh);
	exit(EXIT_FAILURE);
}

void	exec_cmd_9(t_sh *sh, t_exe *exe, char **args)
{
	if (sh->fd_input != -2)
		close(sh->fd_input);
	if (sh->pipe_par_bool)
	{
		dup2(sh->pipe_par[1], STDOUT_FILENO);
		close(sh->pipe_par[1]);
		close(sh->pipe_par[0]);
	}
	else if (sh->out_par && sh->position < sh->out_par)
		dup2(sh->fd_output, STDOUT_FILENO);
	if (sh->fd_output != -2)
		close(sh->fd_output);
	close(sh->true_stdin);
	close(sh->true_stdout);
	close(sh->pipe[0]);
	close(sh->pipe[1]);
	exe->cmd = cmd_args(sh, args);
	execve(exe->cmd[0], exe->cmd, sh->env);
	child_free(sh);
	exit(EXIT_FAILURE);
}

void	exec_cmd_10(t_sh *sh, t_exe *exe, char **args)
{
	dup2(sh->true_stdout, STDOUT_FILENO);
	close(sh->true_stdout);
	if (sh->fd_input != -2)
		close(sh->fd_input);
	if (sh->op_pipe)
	{
		close(sh->pipe_par[1]);
		close(sh->pipe_par[0]);
	}
	if (sh->out_par && sh->position < sh->out_par)
		dup2(sh->fd_output, STDOUT_FILENO);
	if (sh->fd_output != -2)
		close(sh->fd_output);
	close(sh->pipe[0]);
	close(sh->pipe[1]);
	close(sh->true_stdin);
	exe->cmd = cmd_args(sh, args);
	execve(exe->cmd[0], exe->cmd, sh->env);
	child_free(sh);
	exit(EXIT_FAILURE);
}
