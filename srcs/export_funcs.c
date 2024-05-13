/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 19:08:05 by trimize           #+#    #+#             */
/*   Updated: 2024/05/13 19:08:36 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	export_parent(t_sh *sh, t_exe *exe, char **args)
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
	sh->position += find_sp(args, sh);
}

void	export_parent_2(t_sh *sh, t_exe *exe, char **args)
{
	exe->str = sorted_tab(sh->env);
	if (ft_equalstr(args[find_sp(args, sh)], "|"))
		export_parent(sh, exe, args);
	else if (ft_equalstr(args[find_sp(args, sh)], ">"))
	{
		sh->fd_output = open(args[find_sp(args, sh) + 1],
				O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (sh->fd_output == -1)
			ft_putstr_fd("Couldn't open file->\n", 2);
		exe->i = -1;
		write(sh->fd_output, exe->str, ft_strlen(exe->str));
		close(sh->fd_output);
		sh->position += find_sp(args, sh) + 2;
	}
	else if (ft_equalstr(args[find_sp(args, sh)], ">>"))
	{
		sh->fd_output = open(args[find_sp(args, sh) + 1],
				O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (sh->fd_output == -1)
			ft_putstr_fd("Couldn't open file->\n", 2);
		write(sh->fd_output, exe->str, ft_strlen(exe->str));
		(write(sh->fd_output, "\n", 1), close(sh->fd_output));
		sh->position += find_sp(args, sh) + 2;
	}
	free(exe->str);
}

void	export_parent_3(t_sh *sh, char **args)
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
	sh->position += find_sp_par(args, sh);
}

void	export_parent_4(t_sh *sh, t_exe *exe, char **args)
{
	sh->last_cmd_st = 0;
	sh->bool_result = 1;
	if ((find_sp(args, sh) == 0 && !args[1])
		|| (find_sp(args, sh) == 1))
		export_parent_2(sh, exe, args);
	else if (ft_equalstr(args[find_sp(args, sh)], "|"))
		export_parent_3(sh, args);
	else
	{
		export(sh, &args[1]);
		if (find_sp(args, sh) == 0)
			sh->position = tab_len(sh->args) - 1;
		else
			sh->position += find_sp_par(args, sh);
	}
}
