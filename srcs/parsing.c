/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 18:55:56 by mbrandao          #+#    #+#             */
/*   Updated: 2024/05/20 13:19:53 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	arg_17(t_sh *sh)
{
	sh->inside_par++;
	if (go_af_par(&sh->args[sh->position]) > 0)
	{
		if (ft_equalstr(sh->args[check_sp_afpar(
						&sh->args[sh->position]) + sh->position], "|")
			&& !sh->pipe_par_bool)
			arg_14(sh);
		else if (ft_equalstr(sh->args[check_sp_afpar(
						&sh->args[sh->position]) + sh->position], ">"))
			arg_15(sh);
		else if (ft_equalstr(sh->args[check_sp_afpar(
						&sh->args[sh->position]) + sh->position], ">>"))
			arg_16(sh);
	}
	sh->position++;
}

void	arg(t_sh *sh)
{
	t_pars	pars;

	pars.fd = 0;
	if (sh->position == tab_len(sh->args) - 1)
		arg_2(&pars, sh);
	else
	{
		pars.special = check_special(sh->args[sh->position], sh);
		if (arg_checker(sh->args[sh->position], sh) && !pars.special)
			sh->position++;
		else if (pars.special && !sh->args[sh->position + 1])
			arg_3(sh);
		else if (pars.special && sh->args[sh->position + 1])
			arg_13(&pars, sh);
		else if (ft_equalstr(sh->args[sh->position], "("))
			arg_17(sh);
		else if (ft_equalstr(sh->args[sh->position], ")"))
		{
			sh->inside_par--;
			sh->position++;
		}
		else
			exec_cmd(&sh->args[sh->position], sh);
		arg(sh);
	}
}
