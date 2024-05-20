/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:27:46 by trimize           #+#    #+#             */
/*   Updated: 2024/05/20 12:45:44 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	arg_7(t_pars *pars, t_sh *sh)
{
	if (pars->fd != -1)
		close(pars->fd);
	redir_in(sh->args[sh->position + 1],
		&sh->args[sh->position], sh);
	sh->position += 2;
	exec_cmd(&sh->args[sh->position], sh);
	free(sh->wrong_file);
	sh->wrong_file = NULL;
}

void	arg_8(t_pars *pars, t_sh *sh)
{
	dup2(sh->true_stdin, STDIN_FILENO);
	pars->fd = open(sh->args[sh->position + 1], O_RDONLY);
	if ((!find_sp(&sh->args[sh->position + 1], sh)
			|| !ft_equalstr(sh->args[find_sp(
						&sh->args[sh->position + 1], sh) + 1], "|"))
		&& (pars->fd == -1))
		arg_6(sh);
	else
		arg_7(pars, sh);
}

void	arg_9(t_pars *pars, t_sh *sh)
{
	dup2(sh->true_stdin, STDIN_FILENO);
	dup2(sh->true_stdout, STDOUT_FILENO);
	if (pipe(sh->pipe) != 0)
		(perror("pipe error"), child_free(sh), exit(EXIT_FAILURE));
	pars->buffer = redir_in_heredoc(sh->args[sh->position + 1], sh);
	if (!pars->buffer && g_signal)
	{
		close(sh->pipe[0]);
		close(sh->pipe[1]);
		freetab(sh->args);
		free(sh->sp_bool);
		get_input(sh);
	}
	write(sh->pipe[1], pars->buffer, ft_strlen(pars->buffer));
	close(sh->pipe[1]);
	free(pars->buffer);
	dup2(sh->pipe[0], STDIN_FILENO);
	close(sh->pipe[0]);
	sh->position += 2;
	exec_cmd(&sh->args[sh->position], sh);
}

void	arg_10(t_sh *sh)
{
	dup2(sh->true_stdin, STDIN_FILENO);
	dup2(sh->true_stdout, STDOUT_FILENO);
	if (sh->position == sh->pipe_par_bool)
	{
		sh->pipe_par_bool = 0;
		close(sh->pipe_par[1]);
		dup2(sh->pipe_par[0], STDIN_FILENO);
		close(sh->pipe_par[0]);
	}
	else
	{
		dup2(sh->pipe[0], STDIN_FILENO);
		close(sh->pipe[0]);
	}
	sh->position++;
}

void	arg_11(t_sh *sh)
{
	if (sh->bool_result == 1)
	{
		if (find_sp(&sh->args[sh->position + 1], sh) == 0)
			sh->position = tab_len(sh->args) - 1;
		else
		{
			if (sh->args[sh->position + 1][0] == '(')
				sh->position += check_sp_afpar(
						&sh->args[sh->position + 1]);
			else
				sh->position += find_sp(
						&sh->args[sh->position + 1], sh) + 1;
		}
	}
	else
		sh->position++;
}
