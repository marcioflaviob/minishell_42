/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 19:03:47 by trimize           #+#    #+#             */
/*   Updated: 2024/05/29 13:20:56 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_cmd_16(t_sh *sh, char **args)
{
	waitpid(sh->pid[sh->nb_cmd - 1], &sh->last_cmd_st, 0);
	close(sh->pipe[0]);
	close(sh->pipe[1]);
	if (sh->last_cmd_st != 0)
	{
		sh->bool_result = 0;
		sh->position += find_sp_par(args, sh);
	}
	else
	{
		sh->bool_result = 1;
		sh->position += find_sp_par(args, sh);
	}
}

void	exec_cmd_17(t_sh *sh, char **args)
{
	waitpid(sh->pid[sh->nb_cmd - 1], &sh->last_cmd_st, 0);
	close(sh->pipe[0]);
	close(sh->pipe[1]);
	if (sh->last_cmd_st != 0)
	{
		sh->bool_result = 0;
		sh->position += find_sp_par(args, sh);
	}
	else
	{
		sh->bool_result = 1;
		sh->position += find_sp_par(args, sh);
	}
}

void	exec_cmd_18(t_sh *sh, char **args)
{
	if (ft_equalstr(args[find_sp(args, sh)], ">")
		|| ft_equalstr(args[find_sp(args, sh)], ">>")
		|| ft_equalstr(args[find_sp(args, sh)], "<"))
		exec_cmd_14(sh, args);
	else if (ft_equalstr(args[find_sp(args, sh)], "|"))
	{
		close(sh->pipe[1]);
		if (sh->position + find_sp(args, sh) == sh->pipe_par_bool)
			close(sh->pipe_par[1]);
		sh->position += find_sp(args, sh);
	}
	else if (ft_equalstr(args[find_sp(args, sh)], "||"))
		exec_cmd_16(sh, args);
	else if (ft_equalstr(args[find_sp(args, sh)], "&&"))
	{
		exec_cmd_17(sh, args);
	}
}

void	exit_parent(t_sh *sh, t_exe *exe, char **args)
{
	if (!args[1])
		exec_cmd_11(sh, exe);
	else
		exec_cmd_12(sh, exe, args);
	if (ft_equalstr(args[find_sp(args, sh)], "|"))
	{
		if (sh->position + find_sp(args, sh) == sh->pipe_par_bool)
		{
			if (pipe(sh->pipe_par) != 0)
				(perror("pipe error"), child_free(sh), exit(EXIT_FAILURE));
			write(sh->pipe_par[1], "\x04", 1);
			close(sh->pipe_par[1]);
		}
		else
		{
			if (pipe(sh->pipe) != 0)
				(perror("pipe error"), child_free(sh), exit(EXIT_FAILURE));
			write(sh->pipe[1], "\x04", 1);
			close(sh->pipe[1]);
		}
	}
	if (find_sp(args, sh) == 0)
		sh->position = tab_len(sh->args) - 1;
	else
		sh->position += find_sp_par(args, sh);
}

void	unset_parent(t_sh *sh, char **args)
{
	sh->last_cmd_st = 0;
	sh->bool_result = 1;
	un_set(sh, &args[1]);
	if (ft_equalstr(args[find_sp(args, sh)], "|"))
	{
		if (sh->position + find_sp(args, sh) == sh->pipe_par_bool)
		{
			if (pipe(sh->pipe_par) != 0)
				(perror("pipe error"), exit(EXIT_FAILURE));
			write(sh->pipe_par[1], "\x04", 1);
			close(sh->pipe_par[1]);
		}
		else
		{
			if (pipe(sh->pipe) != 0)
				(perror("pipe error"), exit(EXIT_FAILURE));
			write(sh->pipe[1], "\x04", 1);
			close(sh->pipe[1]);
		}
	}
	if (find_sp(args, sh) == 0)
		sh->position = tab_len(sh->args) - 1;
	else
		sh->position += find_sp_par(args, sh);
}
