/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 19:03:47 by trimize           #+#    #+#             */
/*   Updated: 2024/05/13 19:05:47 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	exec_cmd_12(t_sh *sh, t_exe *exe, char **args)
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
	exit(ft_atoi(args[1]));
}

void	exec_cmd_13(t_sh *sh, t_exe *exe)
{
	waitpid(exe->pid, &sh->last_cmd_st, 0);
	if (sh->last_cmd_st == 131)
		write(1, "Quit (core dumped)\n", 19);
	close(sh->pipe[1]);
	close(sh->pipe[0]);
	if (sh->op_pipe)
	{
		close(sh->pipe_par[0]);
		close(sh->pipe_par[1]);
	}
	sh->position = tab_len(sh->args) - 1;
}

void	exec_cmd_14(t_sh *sh, t_exe *exe, char **args)
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
