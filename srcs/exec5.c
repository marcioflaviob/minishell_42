/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:42:24 by mbrandao          #+#    #+#             */
/*   Updated: 2024/05/15 15:59:17 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	execve(exe->cmd[0], exe->cmd, sh->env);
	child_free(sh);
	exit(EXIT_FAILURE);
}

void	exec_cmd_5(t_sh *sh, t_exe *exe, char **args)
{
	exe->pid2 = fork();
	if (exe->pid2 == -1)
		(perror("fork error"), child_free(sh), exit(EXIT_FAILURE));
	if (exe->pid2 == 0)
	{
		dup2(sh->true_stdout, STDOUT_FILENO);
		dup2(sh->pipe[1], STDOUT_FILENO);
		if (sh->fd_input != -2)
			close(sh->fd_input);
		close(sh->pipe[0]);
		close(sh->pipe[1]);
		exe->cmd = cmd_args(sh, args);
		execve(exe->cmd[0], exe->cmd, sh->env);
		child_free(sh);
		exit(EXIT_FAILURE);
	}
	else
		waitpid(exe->pid2, &sh->last_cmd_st, 0);
}

void	exec_cmd_11(t_sh *sh, t_exe *exe)
{
	write(1, "exit", ft_strlen("exit"));
	freetab(sh->env);
	free(sh->sp_bool);
	freetab(sh->args);
	free(sh->current_dir);
	freetab(sh->variables);
	close(sh->pipe[0]);
	close(sh->pipe[1]);
	exe->i = open(sh->emoji_path, O_RDONLY);
	get_next_line(exe->i, 1);
	close(exe->i);
	free(sh->emoji_path);
	if (sh->op_pipe)
	{
		close(sh->pipe_par[0]);
		close(sh->pipe_par[1]);
	}
	close(sh->true_stdin);
	close(sh->true_stdout);
	exit(0);
}

void	exec_cmd_15(t_sh *sh, t_exe *exe, char **args)
{
	if (ft_equalstr(args[find_sp(&args[find_sp(args, sh) + 1],
					sh) + exe->i + 1], "|"))
	{
		sh->position += find_sp(&args[find_sp(args, sh) + 1], sh) + exe->i + 1;
		close(sh->pipe[1]);
		if (sh->pipe_par_bool)
			close(sh->pipe_par[1]);
	}
	else
	{
		waitpid(exe->pid, &sh->last_cmd_st, 0);
		close(sh->pipe[0]);
		close(sh->pipe[1]);
		if (sh->last_cmd_st != 0)
			sh->bool_result = 0;
		else if (sh->last_cmd_st == 0)
			sh->bool_result = 1;
		if (sh->position + find_sp(args, sh) == sh->out_par)
			(close(sh->fd_output), sh->out_par = 0);
		if (find_sp(&args[2], sh) == 0)
			sh->position = tab_len(sh->args) - 1;
		else
			sh->position += find_sp(args, sh) + 2;
	}
}
