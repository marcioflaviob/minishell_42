/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:19:52 by trimize           #+#    #+#             */
/*   Updated: 2024/05/15 13:57:40 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	export_2(t_sh *shell, t_exp *exp, char **str)
{
	exp->str1 = get_substring_b(shell->env[exp->i], '=');
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

void	export(t_sh *shell, char **str)
{
	t_exp	exp;

	exp.i = 0;
	exp.y = 0;
	exp.replace = 0;
	if (!find_sp(str, shell))
		exp.str_len = tab_len(str) - 1;
	else
		exp.str_len = find_sp(str, shell);
	while (exp.y < exp.str_len)
	{
		if (!ft_strrchr(str[exp.y], '='))
		{
			exp.str2 = ft_strdup(str[exp.y]);
			if (!is_alscore_str(exp.str2))
				return (export_4(shell, &exp));
		}
		else
		{
			exp.str2 = get_substring_b(str[exp.y], '=');
			if (!is_alscore_str(exp.str2) || ft_equalstr(str[exp.y], "="))
				return (export_3(shell, str, &exp));
		}
		export_5(shell, &exp, str);
	}
}
