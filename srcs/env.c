/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:19:52 by trimize           #+#    #+#             */
/*   Updated: 2024/04/06 15:35:40 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	export(t_sh *shell, char **str)
{
	int		i;
	int		y;
	int		str_len;
	char	*str1;
	char	*str2;

	i = 0;
	y = 0;
	if (!find_sp(str))
		str_len = tab_len(str) - 1;
	else
		str_len = find_sp(str);
	while (y < str_len)
	{
		while (shell->env[i])
		{
			str1 = get_substring_b(shell->env[i], '=');
			str2 = get_substring_b(str[y], '=');
			if (ft_equalstr(str1, str2) == 1)
			{
				free(str1);
				free(str2);
				free(shell->env[i]);
				shell->env[i] = ft_strdup(str[y]);
				return ;
			}
			i++;
			free(str1);
			free(str2);
		}
		add_to_tab(&shell->env, str[y]);
		y++;
	}	
}

char	*get_env(char *str, t_sh *shell)
{
	int		i;
	char	*tmp;

	i = 0;
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
	return (NULL);
}

void	set_env(t_sh *shell)
{
	copy_tab(&shell->env, __environ);
}

void	un_set(t_sh *shell, char **str)
{
	int		i;
	int		y;
	int		str_len;
	char	*tmp_subchar;

	i = 0;
	y = 0;
	if (!find_sp(str))
		str_len = tab_len(str) - 1;
	else
		str_len = find_sp(str);
	while (y < str_len)
	{
		while (shell->env[i])
		{
			tmp_subchar = get_substring_b(shell->env[i], '=');
			if (ft_equalstr(tmp_subchar, str[y]) == 1)
			{
				free(tmp_subchar);
				rm_tab_line(&shell->env, shell->env[i]);
				break ;
			}
			free(tmp_subchar);
			i++;
		}
		y++;
	}
	return ;
}

void	env(t_sh *shell)
{
	print_tab(shell->env);
}
