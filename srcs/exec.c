/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 19:03:47 by trimize           #+#    #+#             */
/*   Updated: 2024/05/15 14:44:36 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_helper(t_sh *sh, t_h *hp, char **args)
{
	if (args[hp->y]
		&& ft_equalstr(args[hp->y], "|") && !hp->fd_output)
		dup2(sh->pipe[1], STDOUT_FILENO);
	if (hp->fd_input == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(args[hp->i], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(1);
	}
	if (hp->fd_output && hp->fd_output != -1)
		(dup2(hp->fd_output, STDOUT_FILENO), close(hp->fd_output));
	if (hp->fd_output == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(args[hp->i], 2);
		ft_putstr_fd(": Permission denied\n", 2);
		exit(1);
	}
	if (hp->fd_input && hp->fd_input != -1)
		(dup2(hp->fd_input, STDIN_FILENO), close(hp->fd_input));
	if (sh->fd_input != -2)
		close(sh->fd_input);
	if (sh->fd_output != -2)
		close(sh->fd_output);
}

int	exec_helper2(t_sh *sh, t_h *hp, char **args)
{
	if (args[hp->y] && ft_equalstr(args[hp->y], "<"))
	{
		hp->i += find_sp_redir(&args[hp->i], sh, hp->position) + 1;
		while (args[hp->i + 1] && !check_special_redirect(args[hp->i + 1]))
			hp->i++;
		hp->fd_input = open(args[hp->i], O_RDONLY);
		if (hp->fd_input == -1)
			return (1);
	}
	if (args[hp->y] && ft_equalstr(args[hp->y], ">"))
	{
		hp->i += find_sp_redir(&args[hp->i], sh, hp->position) + 1;
		while (args[hp->i + 1] && !check_special_redirect(args[hp->i + 1]))
			hp->i++;
		hp->fd_output = open(args[hp->i], O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (hp->fd_output == -1)
			return (1);
	}
	return (0);
}

int	exec_helper3(t_sh *sh, t_h *hp, char **args)
{
	if (args[hp->y] && ft_equalstr(args[hp->y], ">>"))
	{
		hp->i += find_sp_redir(&args[hp->i], sh, hp->position) + 1;
		while (args[hp->i + 1] && !check_special_redirect(args[hp->i + 1]))
			hp->i++;
		hp->fd_output = open(args[hp->i],
				O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (hp->fd_output == -1)
			return (1);
	}
	return (0);
}

void	exec_cmd_2(t_sh *sh, t_exe *exe, char **args)
{
	t_h	hp;

	hp.fd_output = 0;
	hp.fd_input = 0;
	hp.i = 0;
	hp.position = hp.i;
	hp.y = find_sp(&args[hp.i], sh);
	while (ft_equalstr(args[hp.y], "<")
		|| ft_equalstr(args[hp.y], ">") || ft_equalstr(args[hp.y], ">>"))
	{
		if (exec_helper2(sh, &hp, args))
			break ;
		if (exec_helper3(sh, &hp, args))
			break ;
		hp.position = hp.i;
		hp.y = find_sp_redir(&args[hp.i], sh, hp.position) + hp.i;
	}
	(exec_helper(sh, &hp, args), close(sh->pipe[0]));
	(close(sh->pipe[1]), exe->cmd = cmd_args(sh, args));
	if (hp.fd_input && hp.fd_input == -1)
		(add_to_tab(&exe->cmd, args[hp.i]));
	(execve(exe->cmd[0], exe->cmd, sh->env), exit(EXIT_FAILURE));
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
		execve(exe->cmd[0], exe->cmd, sh->env);
		exit(EXIT_FAILURE);
	}
	else
		waitpid(exe->pid2, &sh->last_cmd_st, 0);
}
