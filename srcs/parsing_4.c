/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:30:19 by trimize           #+#    #+#             */
/*   Updated: 2024/05/21 14:07:32 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	arg_12(t_sh *sh)
{
	if (sh->bool_result == 0)
	{
		while (sh->position < tab_len(sh->args) - 1)
		{
			if (sh->args[sh->position][0] == '(')
				sh->position += go_af_par(&sh->args[sh->position]);
			if (ft_equalstr(sh->args[sh->position], "||"))
				break ;
			sh->position++;
		}
		if (sh->position == tab_len(sh->args))
			sh->position = tab_len(sh->args) - 1;
	}
	else
		sh->position++;
}

void	arg_13(t_pars *pars, t_sh *sh)
{
	if (pars->special == 1)
		arg_4(sh);
	else if (pars->special == 2)
		arg_5(sh);
	else if (pars->special == 3 && !sh->args[sh->position + 2])
		(dup2(sh->true_stdin, STDIN_FILENO),
			redir_in(sh->args[sh->position + 1], &sh->args[0], sh),
			sh->position = tab_len(sh->args) - 1);
	else if (pars->special == 3 && sh->args[sh->position + 2])
		arg_8(pars, sh);
	else if (pars->special == 4)
		arg_9(pars, sh);
	else if (pars->special == 5)
		arg_10(sh);
	else if (pars->special == 6)
		arg_11(sh);
	else if (pars->special == 7)
		arg_12(sh);
}

void	arg_14(t_sh *sh)
{
	if (pipe(sh->pipe_par) != 0)
		(perror("pipe error"), exit(EXIT_FAILURE));
	sh->op_pipe = 1;
	sh->pipe_par_bool = check_sp_afpar(
			&sh->args[sh->position]) + sh->position;
}

void	arg_15(t_sh *sh)
{
	sh->fd_output = open(sh->args[check_sp_afpar(
				&sh->args[sh->position]) + 1], O_WRONLY
			| O_CREAT | O_TRUNC, 0666);
	sh->out_par = check_sp_afpar(
			&sh->args[sh->position]) + sh->position;
}

void	arg_16(t_sh *sh)
{
	sh->fd_output = open(sh->args[check_sp_afpar(
				&sh->args[sh->position]) + 1], O_WRONLY
			| O_CREAT | O_APPEND, 0666);
	sh->out_par = check_sp_afpar(
			&sh->args[sh->position]) + sh->position;
}
