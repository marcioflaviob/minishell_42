/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:37:02 by trimize           #+#    #+#             */
/*   Updated: 2024/05/15 13:54:36 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	env(t_sh *shell)
{
	print_tab(shell->env);
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
