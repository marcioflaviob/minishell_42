/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_removal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 00:27:17 by mbrandao          #+#    #+#             */
/*   Updated: 2024/04/02 00:41:31 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//TODO Fix quote removal

void	quotes_removal_helper(char **str)
{
	int	i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\'')
		{
			if (is_around_squotes(*str, i))
			{
				ft_strerase(str, i, 1);
				while ((*str)[i++] != '\'')
					;
				ft_strerase(str, i, 1);
			}
		}
		if ((*str)[i] == '\"')
		{
			if (is_around_dquotes(*str, i))
			{
				ft_strerase(str, i, 1);
				while ((*str)[i++] != '\"')
					;
				ft_strerase(str, i, 1);
			}
		}
		i++;
	}
}

void	quotes_removal(char ***cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
	{
		quotes_removal_helper(&((*cmds)[i]));
		i++;
	}
}