/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:24:32 by trimize           #+#    #+#             */
/*   Updated: 2024/05/29 13:29:39 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	arg_2(t_pars *pars, t_sh *sh)
{
	if (ft_equalstr(sh->args[0], "|"))
	{
		sh->last_cmd_st = 2;
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
	}
	pars->buffer = ft_itoa(sh->last_cmd_st);
	pars->tmp = ft_strjoin("?=", pars->buffer);
	free(pars->buffer);
	add_env(sh, pars->tmp);
	free(pars->tmp);
	freetab(sh->args);
	free(sh->sp_bool);
	free(sh->pid);
	close(sh->pipe[0]);
	close(sh->pipe[1]);
	sh->pid = (pid_t *)malloc(sizeof(pid_t));
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
	if (check_special(sh->args[sh->position], sh))
	{
		if (ft_equalstr(sh->args[sh->position], "|"))
			if (pipe(sh->pipe) != 0)
				(perror("pipe error"), child_free(sh), exit(EXIT_FAILURE));
		close(sh->pipe[1]);
	}
	else if (sh->position != tab_len(sh->args) - 1)
		exec_cmd(&sh->args[sh->position], sh);
}

void	arg_5(t_sh *sh)
{
	dup2(sh->true_stdout, STDOUT_FILENO);
	redir_out_app_p(sh->args[sh->position + 1],
		&sh->args[sh->position], sh);
	sh->position += 2;
	if (check_special(sh->args[sh->position], sh))
	{
		if (ft_equalstr(sh->args[sh->position], "|"))
			if (pipe(sh->pipe) != 0)
				(perror("pipe error"), child_free(sh), exit(EXIT_FAILURE));
		close(sh->pipe[1]);
	}
	else if (sh->position != tab_len(sh->args) - 1)
		exec_cmd(&sh->args[sh->position], sh);
}

void	arg_6(t_sh *sh)
{
	ft_putstr_fd("minishell: no such file or directory: ", 2);
	ft_putstr_fd(sh->args[sh->position + 1], 2);
	ft_putstr_fd("\n", 2);
	sh->last_cmd_st = 1;
	sh->position = tab_len(sh->args) - 1;
}
