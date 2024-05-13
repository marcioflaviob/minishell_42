/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:19:52 by trimize           #+#    #+#             */
/*   Updated: 2024/05/13 22:42:28 by mbrandao         ###   ########.fr       */
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
			{
				shell->last_cmd_st = 1;
				shell->bool_result = 0;
				ft_putstr_fd("minishell: export: `", 2);
				ft_putstr_fd(exp.str2, 2);
				ft_putstr_fd("\': not a valid identifier\n", 2);
				free(exp.str2);
				return ;
			}
		}
		else
		{
			exp.str2 = get_substring_b(str[exp.y], '=');
			if (!is_alscore_str(exp.str2) || ft_equalstr(str[exp.y], "="))
			{
				shell->last_cmd_st = 1;
				shell->bool_result = 0;
				ft_putstr_fd("minishell: export: `", 2);
				if (ft_equalstr(str[exp.y], "="))
					ft_putstr_fd("=", 2);
				ft_putstr_fd(exp.str2, 2);
				ft_putstr_fd("\': not a valid identifier\n", 2);
				free(exp.str2);
				return ;
			}
		}
		while (shell->env[exp.i])
			export_2(shell, &exp, str);
		if (exp.replace == 0)
		{
			if (!ft_strrchr(str[exp.y], '='))
				(free(str[exp.y]), str[exp.y] = ft_strjoin(exp.str2, "="));
			add_to_tab(&shell->env, str[exp.y]);
		}
		(free(exp.str2), exp.replace = 0, exp.y++);
	}	
}

char	*get_env(char *str, t_sh *shell)
{
	int		i;
	int		y;
	char	*t;

	i = 0;
	y = 0;
	while (shell->variables[y])
	{
		t = get_substring_b(shell->variables[y], '=');
		if (ft_equalstr(t, str) == 1)
			return (free(t), t = get_substring_a(shell->variables[y], '='), t);
		y++;
	}
	if (shell->variables[y] == NULL)
	{
		while (shell->env[i])
		{
			t = get_substring_b(shell->env[i], '=');
			if (ft_equalstr(t, str) == 1)
				return (free(t), t = get_substring_a(shell->env[i], '='), t);
			(free(t), i++);
		}
	}
	return (NULL);
}

void	set_env(t_sh *shell)
{
	copy_tab(&shell->env, __environ);
	shell->variables = (char **)malloc(2 * sizeof(char *));
	if (!shell->variables)
		return ;
	shell->variables[0] = ft_strdup("?=0");
	shell->variables[1] = NULL;
}

void	un_set(t_sh *shell, char **str)
{
	int		i;
	int		y;
	int		str_len;
	char	*tmp_subchar;

	i = 0;
	y = 0;
	if (!find_sp(str, shell))
		str_len = tab_len(str) - 1;
	else
		str_len = find_sp(str, shell);
	while (y < str_len)
	{
		while (shell->env[i])
		{
			tmp_subchar = get_substring_b(shell->env[i], '=');
			if (ft_equalstr(tmp_subchar, str[y]) == 1)
			{
				(free(tmp_subchar), rm_tab_line(&shell->env, shell->env[i]));
				break ;
			}
			(free(tmp_subchar), i++);
		}
		y++;
	}
}
