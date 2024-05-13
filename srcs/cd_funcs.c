/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_funcs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 19:09:50 by trimize           #+#    #+#             */
/*   Updated: 2024/05/13 22:47:21 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cd_parent(t_sh *sh, char **args)
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

void	cd_parent_2(t_sh *sh, char **args)
{
	if (find_sp(args, sh) > 2 || (tab_len(args) - 1) > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		sh->bool_result = 0;
		sh->last_cmd_st = 1;
	}
	else if (!ft_equalstr(args[find_sp(args, sh)], "|"))
	{
		sh->bool_result = cd(sh, args[1]);
		if (sh->bool_result)
			sh->last_cmd_st = 0;
		else
			sh->last_cmd_st = 1;
	}
	else
		cd_parent(sh, args);
	if (find_sp(args, sh) == 0)
		sh->position = tab_len(sh->args) - 1;
	else
		sh->position += find_sp_par(args, sh);
}
