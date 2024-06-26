/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:19:52 by trimize           #+#    #+#             */
/*   Updated: 2024/06/07 13:24:58 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	export_2(t_sh *shell, t_exp *exp, char **str)
{
	exp->str1 = get_substring_b(shell->env[exp->i], '=', shell);
	if (ft_equalstr(exp->str1, exp->str2) == 1)
	{
		if (!ft_strrchr(str[exp->y], '='))
			exp->replace = 1;
		else
		{
			free(shell->env[exp->i]);
			shell->env[exp->i] = ft_strdup(str[exp->y]);
			exp->replace = 1;
		}
	}
	exp->i++;
	free(exp->str1);
}

void	export_3(t_sh *shell, char **str, t_exp *exp)
{
	shell->last_cmd_st = 1;
	shell->bool_result = 0;
	ft_putstr_fd("minishell: export: `", 2);
	if (ft_equalstr(str[exp->y], "="))
		ft_putstr_fd("=", 2);
	ft_putstr_fd(exp->str2, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
	free(exp->str2);
}

void	export_4(t_sh *shell, t_exp *exp)
{
	shell->last_cmd_st = 1;
	shell->bool_result = 0;
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(exp->str2, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
	free(exp->str2);
}

void	export_init(t_exp *exp)
{
	exp->i = 0;
	exp->y = 0;
	exp->replace = 0;
}

void	export(t_sh *shell, char **str)
{
	t_exp	exp;

	(export_init(&exp), shell->position++);
	if (!find_sp(str, shell))
		exp.str_len = tab_len(str) - 1;
	else
		exp.str_len = find_sp(str, shell);
	while (exp.y < exp.str_len)
	{
		if (!ft_strrchr(str[exp.y], '='))
		{
			exp.str2 = ft_strdup(str[exp.y]);
			if (is_alscore_str(exp.str2))
				(free(exp.str2), exp.y++);
			else
				return (export_4(shell, &exp));
		}
		else
		{
			exp.str2 = get_substring_b(str[exp.y], '=', shell);
			if (!is_alscore_str(exp.str2) || ft_equalstr(str[exp.y], "="))
				return (export_3(shell, str, &exp));
			export_5(shell, &exp, str);
		}
	}
}
