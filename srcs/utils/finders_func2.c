/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finders_func2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 19:10:19 by trimize           #+#    #+#             */
/*   Updated: 2024/06/07 13:41:50 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_sp(char **args, t_sh *sh)
{
	int	i;
	int	j;

	i = 0;
	j = sh->position;
	while (args[i])
	{
		if ((args[i][0] == '<' && sh->sp_bool[j] == 1)
			|| (args[i][0] == '>' && sh->sp_bool[j] == 1)
			|| (args[i][0] == '|' && sh->sp_bool[j] == 1))
			return (i);
		if ((ft_equalstr(args[i], "||") && sh->sp_bool[j] == 1)
			|| (ft_equalstr(args[i], ">>") && sh->sp_bool[j] == 1)
			|| (ft_equalstr(args[i], "<<") && sh->sp_bool[j] == 1)
			|| (ft_equalstr(args[i], "&&") && sh->sp_bool[j] == 1))
			return (i);
		i++;
		j++;
	}
	return (0);
}

int	find_sp_redir(char **args, t_sh *sh, int j)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if ((args[i][0] == '<' && sh->sp_bool[j] == 1)
			|| (args[i][0] == '>' && sh->sp_bool[j] == 1)
			|| (args[i][0] == '|' && sh->sp_bool[j] == 1))
			return (i);
		if ((ft_equalstr(args[i], "||") && sh->sp_bool[j] == 1)
			|| (ft_equalstr(args[i], ">>") && sh->sp_bool[j] == 1)
			|| (ft_equalstr(args[i], "<<") && sh->sp_bool[j] == 1)
			|| (ft_equalstr(args[i], "&&") && sh->sp_bool[j] == 1))
			return (i);
		i++;
		j++;
	}
	return (0);
}

int	find_non_redir(char **args, t_sh *sh)
{
	int	i;
	int	j;

	i = 0;
	j = sh->position;
	while (args[i])
	{
		if ((args[i][0] == '|' && sh->sp_bool[j] == 1))
			return (i);
		if ((ft_equalstr(args[i], "||") && sh->sp_bool[j] == 1)
			|| (ft_equalstr(args[i], "&&") && sh->sp_bool[j] == 1))
			return (i);
		i++;
		j++;
	}
	return (tab_len(sh->args) - 1 - sh->position);
}

int	find_sp_echo(char **args, t_sh *sh)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if ((ft_equalstr(args[i], ">") && sh->sp_bool[sh->position + i])
			|| (ft_equalstr(args[i], "|") && sh->sp_bool[sh->position + i])
			|| (ft_equalstr(args[i], "<") && sh->sp_bool[sh->position + i]))
			return (i);
		if ((ft_equalstr(args[i], "||") && sh->sp_bool[sh->position + i])
			|| (ft_equalstr(args[i], ">>") && sh->sp_bool[sh->position + i])
			|| (ft_equalstr(args[i], "<<") && sh->sp_bool[sh->position + i])
			|| (ft_equalstr(args[i], "(") && sh->sp_bool[sh->position + i])
			|| (ft_equalstr(args[i], ")") && sh->sp_bool[sh->position + i])
			|| (ft_equalstr(args[i], "&&") && sh->sp_bool[sh->position + i]))
			return (i);
		i++;
	}
	return (0);
}

int	find_sp_par(char **args, t_sh *sh)
{
	int	i;
	int	j;

	i = 0;
	j = sh->position;
	while (args[i])
	{
		if ((args[i][0] == '<' && sh->sp_bool[j] == 1)
			|| (args[i][0] == '>' && sh->sp_bool[j] == 1)
			|| (args[i][0] == '|' && sh->sp_bool[j] == 1)
			|| (args[i][0] == ')' && sh->sp_bool[j] == 1))
			return (i);
		if ((ft_equalstr(args[i], "||") && sh->sp_bool[j] == 1)
			|| (ft_equalstr(args[i], ">>") && sh->sp_bool[j] == 1)
			|| (ft_equalstr(args[i], "<<") && sh->sp_bool[j] == 1)
			|| (ft_equalstr(args[i], "&&") && sh->sp_bool[j] == 1))
			return (i);
		i++;
		j++;
	}
	return (0);
}
