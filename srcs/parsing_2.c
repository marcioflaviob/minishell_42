/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:24:32 by trimize           #+#    #+#             */
/*   Updated: 2024/05/13 16:25:12 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	arg_2(t_pars *pars, t_sh *sh)
{
	pars->buffer = ft_itoa(sh->last_cmd_st);
	pars->tmp = ft_strjoin("?=", pars->buffer);
	free(pars->buffer);
	add_env(sh, pars->tmp);
	free(pars->tmp);
	freetab(sh->args);
	free(sh->sp_bool);
	close(sh->pipe[0]);
	close(sh->pipe[1]);
	get_input(sh);
}

void	arg_3(t_sh *sh)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(sh->args[sh->position], 2);
	ft_putstr_fd("\n", 2);
	sh->position = tab_len(sh->args) - 1;
}

void	arg_4(t_sh *sh)
{
	dup2(sh->true_stdout, STDOUT_FILENO);
	redir_out_trunc_p(sh->args[sh->position + 1],
		&sh->args[sh->position], sh);
	sh->position += 2;
	exec_cmd(&sh->args[sh->position], sh);
}

void	arg_5(t_sh *sh)
{
	dup2(sh->true_stdout, STDOUT_FILENO);
	redir_out_app_p(sh->args[sh->position + 1],
		&sh->args[sh->position], sh);
	sh->position += 2;
	exec_cmd(&sh->args[sh->position], sh);
}

void	arg_6(t_sh *sh)
{
	ft_putstr_fd("minishell: no such file or directory: ", 2);
	ft_putstr_fd(sh->args[sh->position + 1], 2);
	ft_putstr_fd("\n", 2);
	sh->position = tab_len(sh->args) - 1;
}
