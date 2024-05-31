/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_funcs2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 19:07:09 by trimize           #+#    #+#             */
/*   Updated: 2024/05/31 20:59:11 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	env_parent_6(t_sh *sh, t_exe *exe, char **args)
{
	sh->fd_output = open(args[find_sp(args, sh) + 1],
			O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (sh->fd_output == -1)
		ft_putstr_fd("Couldn't open file.\n", 2);
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

void	env_parent_7(t_sh *sh, t_exe *exe, char **args)
{
	if (find_sp(args, sh) == 0 && args[1])
		env_parent(sh, args);
	else
	{
		if (sh->out_par)
			(dup2(sh->fd_output, STDOUT_FILENO));
		sh->bool_result = 1;
		sh->last_cmd_st = 0;
		if (ft_equalstr(args[find_sp(args, sh)], "|"))
			env_parent_4(sh, exe, args);
		else if (ft_equalstr(args[find_sp(args, sh)], ">"))
			env_parent_5(sh, exe, args);
		else if (ft_equalstr(args[find_sp(args, sh)], ">>"))
			env_parent_6(sh, exe, args);
		else
		{
			env(sh);
			if (find_sp(args, sh) == 0)
				sh->position = tab_len(sh->args) - 1;
			else
				sh->position += find_sp_par(args, sh);
		}
	}
}

void	export_5(t_sh *shell, t_exp *exp, char **str)
{
	while (shell->env[exp->i])
		export_2(shell, exp, str);
	if (exp->replace == 0)
	{
		if (!ft_strrchr(str[exp->y], '='))
			(free(str[exp->y]), str[exp->y] = ft_strjoin(exp->str2, "="));
		add_to_tab(&shell->env, str[exp->y]);
	}
	(free(exp->str2), exp->replace = 0, exp->y++);
}
