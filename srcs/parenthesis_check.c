/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 23:04:12 by mbrandao          #+#    #+#             */
/*   Updated: 2024/04/22 23:39:14 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	parenthesis_check(char **str)
{
	int		i;
	int		parenthesis;

	i = 0;
	parenthesis = 0;
	while (str[i])
	{
		if (str[i][0] == '(')
			parenthesis++;
		else if (str[i][0] == ')')
			parenthesis--;
		i++;
	}
	if (parenthesis < 0)
	{
		printf("minishell: parse error near `)'\n");
		return (1);
	}
	else if (parenthesis > 0)
	{
		printf("minishell: parse error near `('\n");
		return (1);
	}
	return (0);
}

int	parenthesis_check2(char **str)
{
	int	i;
	int	error;

	i = 0;
	error = 0;
	while (str[i])
	{
		if (str[i][0] == '(' && str[i + 1] && str[i + 1][0] == '(')
			error = 1;
		else if (str[i][0] == ')' && str[i + 1] && str[i + 1][0] != ')')
			error = 0;
		else if (error == 1 && str[i][0] == ')'
			&& str[i + 1] && str[i + 1][0] == ')')
			return (1);
		i++;
	}
	return (0);
}

int	parenthesis_check3(char **str)
{
	int	i;
	int	sp;

	i = 0;
	while (str[i])
	{
		if (str[i][0] == ')')
		{
			if (str[i + 1])
				sp = find_sp_str(str[i + 1]);
			else
				return (0);
			if (sp == -1 || (sp == 0 && str[i + 1][0] == '('))
			{
				printf("minishell: parse error near `%s\'\n", str[i + 1]);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	par_check_all(char **str, t_sh *sh)
{
	if (parenthesis_check(str))
		return (sh->last_cmd_st = 1, 1);
	if (parenthesis_check2(str))
		return (sh->last_cmd_st = 1, 1);
	if (parenthesis_check3(str))
		return (sh->last_cmd_st = 1, 1);
	return (0);
}