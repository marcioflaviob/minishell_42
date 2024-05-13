/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 19:03:47 by trimize           #+#    #+#             */
/*   Updated: 2024/05/13 19:04:45 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin(char *str)
{
	if (ft_equalstr(str, "echo"))
		return (1);
	else if (ft_equalstr(str, "cd"))
		return (1);
	else if (ft_equalstr(str, "pwd"))
		return (1);
	else if (ft_equalstr(str, "export"))
		return (1);
	else if (ft_equalstr(str, "unset"))
		return (1);
	else if (ft_equalstr(str, "env"))
		return (1);
	else if (ft_equalstr(str, "exit"))
		return (1);
	else
		return (0);
}

void	exec_cmd_2(t_sh *sh, char **args)
{
	rm_tab_line(&sh->args, sh->args[find_sp(args, sh)]);
	rm_tab_line(&sh->args, sh->args[find_sp(args, sh) + 1]);
	if (sh->fd_input != -2)
		close(sh->fd_input);
	if (sh->fd_output != -2)
		close(sh->fd_output);
	close(sh->pipe[0]);
	close(sh->pipe[1]);
	exit(0);
}

void	exec_cmd_3(t_sh *sh, t_exe *exe, char **args)
{
	exe->pid2 = fork();
	if (exe->pid2 == -1)
		(perror("fork error"), exit(EXIT_FAILURE));
	if (exe->pid2 == 0)
	{
		dup2(sh->true_stdout, STDOUT_FILENO);
		dup2(sh->pipe[1], STDOUT_FILENO);
		if (sh->fd_input != -2)
			close(sh->fd_input);
		close(sh->pipe[0]);
		close(sh->pipe[1]);
		exe->cmd = cmd_args(sh, args);
		execve(exe->cmd[0], exe->cmd, NULL);
		exit(EXIT_FAILURE);
	}
	else
		waitpid(exe->pid2, &sh->last_cmd_st, 0);
}

void	exec_cmd_4(t_sh *sh, t_exe *exe, char **args)
{
	exe->i = find_sp(args, sh);
	if (sh->out_par)
		(dup2(sh->fd_output, STDOUT_FILENO), close(sh->fd_output));
	else
		redir_out_trunc(args[find_sp(args, sh) + 1],
			&args[find_sp(args, sh)], sh);
	if (!find_sp(&args[find_sp(args, sh) + 1], sh))
		;
	else if (ft_equalstr(args[find_sp(&args[find_sp(args, sh) + 1],
					sh) + exe->i + 1], "|")
		&& find_sp(&args[find_sp(args, sh) + 1],
			sh) + exe->i + 1 != check_sp_afpar(args))
		exec_cmd_3(sh, exe, args);
	if (sh->fd_input != -2)
		close(sh->fd_input);
	close(sh->pipe[0]);
	close(sh->pipe[1]);
	close(sh->true_stdin);
	close(sh->true_stdout);
	exe->cmd = cmd_args(sh, args);
	execve(exe->cmd[0], exe->cmd, NULL);
	exit(EXIT_FAILURE);
}

void	exec_cmd_5(t_sh *sh, t_exe *exe, char **args)
{
	exe->pid2 = fork();
	if (exe->pid2 == -1)
		(perror("fork error"), exit(EXIT_FAILURE));
	if (exe->pid2 == 0)
	{
		dup2(sh->true_stdout, STDOUT_FILENO);
		dup2(sh->pipe[1], STDOUT_FILENO);
		if (sh->fd_input != -2)
			close(sh->fd_input);
		close(sh->pipe[0]);
		close(sh->pipe[1]);
		exe->cmd = cmd_args(sh, args);
		execve(exe->cmd[0], exe->cmd, NULL);
		exit(EXIT_FAILURE);
	}
	else
		waitpid(exe->pid2, &sh->last_cmd_st, 0);
}
