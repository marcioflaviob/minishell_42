/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:19:52 by trimize           #+#    #+#             */
/*   Updated: 2024/04/06 23:13:40 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	export(t_sh *shell, char *str)
{
	int		i;
	int		y;
	char	*str1;
	char	*str2;

	i = 0;
	y = 0;
	while (shell->env[i])
	{
		str1 = get_substring_b(shell->env[i], '=');
		str2 = get_substring_b(str, '=');
		if (ft_equalstr(str1, str2) == 1)
		{
			free(str1);
			free(str2);
			free(shell->env[i]);
			shell->env[i] = ft_strdup(str);
			return ;
		}
		i++;
		free(str1);
		free(str2);
	}
	add_to_tab(&shell->env, str);
}

char	*get_env(char *str, t_sh *shell)
{
	int		i;
	int		y;
	char	*tmp;

	i = 0;
	y = 0;
	while (shell->variables[y])
	{
		tmp = get_substring_b(shell->variables[y], '=');
		if (ft_equalstr(tmp, str) == 1)
		{
			free(tmp);
			tmp = get_substring_a(shell->variables[y], '=');
			return (tmp);
		}
		y++;
	}
	if (shell->variables[y] == NULL)
	{
		while (shell->env[i])
		{
			tmp = get_substring_b(shell->env[i], '=');
			if (ft_equalstr(tmp, str) == 1)
			{
				free(tmp);
				tmp = get_substring_a(shell->env[i], '=');
				return (tmp);
			}
			free(tmp);
			i++;
		}
	}
	return (NULL);
}

void	set_env(t_sh *shell)
{
	copy_tab(&shell->env, __environ);
	shell->variables = malloc(sizeof(char *));
	shell->variables[0] = NULL;
}

void	un_set(t_sh *shell, char *str)
{
	int		i;
	char	*tmp_subchar;

	i = 0;
	while (shell->env[i])
	{
		tmp_subchar = get_substring_b(shell->env[i], '=');
		if (ft_equalstr(tmp_subchar, str) == 1)
		{
			free(tmp_subchar);
			rm_tab_line(&shell->env, shell->env[i]);
			break ;
		}
		free(tmp_subchar);
		i++;
	}
	return ;
}

void	env(t_sh *shell)
{
	print_tab(shell->env);
}
