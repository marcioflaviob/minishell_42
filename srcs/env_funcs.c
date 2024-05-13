/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 19:07:09 by trimize           #+#    #+#             */
/*   Updated: 2024/05/13 19:07:40 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	env_parent(t_sh *sh, char **args)
{
	ft_putstr_fd("env: \'", 2);
	ft_putstr_fd(args[1], 2);
	ft_putstr_fd("\': No such file or directory\n", 2);
	sh->position = tab_len(sh->args) - 1;
	sh->bool_result = 0;
	sh->last_cmd_st = 1;
}

void	env_parent_2(t_sh *sh, t_exe *exe)
{
	if (pipe(sh->pipe_par) != 0)
		(perror("pipe error"), exit(EXIT_FAILURE));
	while (sh->env[exe->i])
	{
		ft_putstr_fd(sh->env[exe->i++], sh->pipe_par[1]);
		write(sh->pipe_par[1], "\n", 1);
	}
	write(sh->pipe_par[1], "\x04", 1);
	close(sh->pipe_par[1]);
}

void	env_parent_3(t_sh *sh, t_exe *exe)
{
	if (pipe(sh->pipe) != 0)
		(perror("pipe error"), exit(EXIT_FAILURE));
	while (sh->env[exe->i])
	{
		ft_putstr_fd(sh->env[exe->i++], sh->pipe[1]);
		write(sh->pipe[1], "\n", 1);
	}
	write(sh->pipe[1], "\x04", 1);
	close(sh->pipe[1]);
}

void	env_parent_4(t_sh *sh, t_exe *exe, char **args)
{
	exe->i = 0;
	if (sh->position + find_sp(args, sh)
		== sh->pipe_par_bool)
		env_parent_2(sh, exe);
	else
		env_parent_3(sh, exe);
	if (find_sp(args, sh) == 0)
		sh->position = tab_len(sh->args) - 1;
	else
		sh->position += find_sp_par(args, sh);
}

void	env_parent_5(t_sh *sh, t_exe *exe, char **args)
{
	sh->fd_output = open(args[find_sp(args, sh) + 1],
			O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (sh->fd_output == -1)
		ft_putstr_fd("Couldn't open file.\n", 2);
	exe->i = -1;
	while (sh->env[++exe->i] != NULL)
	{
		write(sh->fd_output, sh->env[exe->i],
			ft_strlen(sh->env[exe->i]));
		write(sh->fd_output, "\n", 1);
	}
	close(sh->fd_output);
	if (find_sp(args, sh) == 0)
		sh->position = tab_len(sh->args) - 1;
	else
		sh->position += find_sp(args, sh) + 2;
}
