/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:31:48 by trimize           #+#    #+#             */
/*   Updated: 2024/05/14 16:08:15 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_find_first(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return (i);
		i++;
	}
	return (0);
}

int	arg_checker(char *str)
{
	char	*sub;

	if (!ft_find_first(str, '='))
		return (0);
	sub = get_substring_b(str, '=');
	if (ft_find_first(sub, '\'') || ft_find_first(sub, '"'))
		return (0);
	return (1);
}

int	check_special(char *str, t_sh *sh)
{
	if (ft_equalstr(str, ">") && sh->sp_bool[sh->position] == 1)
		return (1);
	else if (ft_equalstr(str, ">>") && sh->sp_bool[sh->position] == 1)
		return (2);
	else if (ft_equalstr(str, "<") && sh->sp_bool[sh->position] == 1)
		return (3);
	else if (ft_equalstr(str, "<<") && sh->sp_bool[sh->position] == 1)
		return (4);
	else if (ft_equalstr(str, "|") && sh->sp_bool[sh->position] == 1)
		return (5);
	else if (ft_equalstr(str, "||") && sh->sp_bool[sh->position] == 1)
		return (6);
	else if (ft_equalstr(str, "&&") && sh->sp_bool[sh->position] == 1)
		return (7);
	return (0);
}

int	check_special_redirect(char *str)
{
	if (ft_equalstr(str, ">"))
		return (1);
	else if (ft_equalstr(str, ">>"))
		return (2);
	else if (ft_equalstr(str, "<"))
		return (3);
	else if (ft_equalstr(str, "<<"))
		return (4);
	else if (ft_equalstr(str, "|"))
		return (5);
	else if (ft_equalstr(str, "||"))
		return (6);
	else if (ft_equalstr(str, "&&"))
		return (7);
	return (0);
}

int	check_sp_afpar(char **args)
{
	int	i;
	int	par;

	i = 1;
	par = 1;
	while (par != 0 && args[i])
	{
		if (args[i][0] == '(')
			par++;
		else if (args[i][0] == ')')
			par--;
		i++;
	}
	while (args[i] && args[i][0] == ')')
		i++;
	if (ft_equalstr(args[i], "|") || ft_equalstr(args[i], ">")
		|| ft_equalstr(args[i], ">>") || ft_equalstr(args[i], "||")
		|| ft_equalstr(args[i], "&&"))
		return (i);
	return (0);
}

int	go_af_par(char **args)
{
	int	i;
	int	par;

	i = 1;
	par = 1;
	while (par != 0 && args[i])
	{
		if (args[i][0] == '(')
			par++;
		else if (args[i][0] == ')')
			par--;
		i++;
	}
	if (args[i - 1][0] != ')')
		return (0);
	return (i);
}
