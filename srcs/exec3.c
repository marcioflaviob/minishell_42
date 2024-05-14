/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 19:03:47 by trimize           #+#    #+#             */
/*   Updated: 2024/05/14 21:24:42 by trimize          ###   ########.fr       */
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
	int	a;

	a = ft_atoi(args[1]);
	write(2, "exit", ft_strlen("exit"));
	if (args[1] && !is_num_str(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		a = 2;
	}
	else if (ft_strchr(args[1], '-'))
		a = ft_atoi(args[1]);
	else if (ft_strchr(args[1], '+'))
		a = ft_atoi(args[1]);
	if (find_sp(args, sh) > 2 || (tab_len(args) - 1) > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		sh->bool_result = 0;
		sh->last_cmd_st = 1;
		return ;
	}
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
	exit(a);
}

void	exec_cmd_13(t_sh *sh, t_exe *exe)
{
	waitpid(exe->pid, &sh->last_cmd_st, 0);
	sh->last_cmd_st = WEXITSTATUS(sh->last_cmd_st);
	if (sh->last_cmd_st == 131)
		write(2, "Quit (core dumped)\n", 19);
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
	int	i;
	int	y;
	int	tmp;

	i = 0;
	y = find_sp(&args[i], sh);
	while (ft_equalstr(args[y], "<") || ft_equalstr(args[y], ">") || ft_equalstr(args[y], ">>"))
	{
		tmp = i;
		if (args[y] && ft_equalstr(args[y], "<"))
			i += find_sp(&args[i], sh) + 1;
		else if (args[y] && ft_equalstr(args[y], ">"))
			i += find_sp(&args[i], sh) + 1;
		else if (args[y] && ft_equalstr(args[y], ">>"))
			i += find_sp(&args[i], sh) + 1;
		sh->position += i - tmp;
		y = find_sp(&args[i], sh) + i;
	}
	if (ft_equalstr(args[y], "|"))
		close(sh->pipe[1]);
	else
	{
		waitpid(exe->pid, &sh->last_cmd_st, 0);
		sh->last_cmd_st = WEXITSTATUS(sh->last_cmd_st);
	}
	if (args[y])
		sh->position++;
	else
		sh->position = tab_len(sh->args) - 1;
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
