/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:40:56 by mbrandao          #+#    #+#             */
/*   Updated: 2024/04/06 23:34:16 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_sp_bool(t_sh *sh)
{
	int	*result;
	int	i;
	int	tmp;

	i = 0;
	result = malloc((tab_len(sh->args) - 1) * sizeof(int));
	while (sh->args[i])
	{
		tmp = find_sp_str(sh->args[i]);
		if (tmp != -1 && !is_quoted(sh->args[i], tmp))
			result[i++] = 1;
		else
			result[i++] = 0;
	}
	sh->sp_bool = result;
}

int	is_quoted(char *str, int i)
{
	if (is_around_dquotes(str, i) || is_around_squotes(str, i))
		return (1);
	return (0);
}

void	space_adder(char **str)
{
	int		i;

	i = 0;
	while ((*str)[i])
	{
		if (is_quoted(*str, i))
			i++;
		else if ((*str)[i] == '>' && (*str)[i + 1] && (*str)[i + 1] != '>')
		{
			*str = ft_stradd(*str, i++, " ");
			*str = ft_stradd(*str, ++i, " ");
		}
		else if ((*str)[i] == '<' && (*str)[i + 1] && (*str)[i + 1] != '<')
		{
			*str = ft_stradd(*str, i++, " ");
			*str = ft_stradd(*str, ++i, " ");
		}
		else if ((*str)[i] == '|' && (*str)[i + 1] && (*str)[i + 1] != '|')
		{
			*str = ft_stradd(*str, i++, " ");
			*str = ft_stradd(*str, ++i, " ");
		}
		else if ((*str)[i] == '>' && (*str)[i + 1] && (*str)[i + 1] == '>')
		{
			*str = ft_stradd(*str, i++, " ");
			*str = ft_stradd(*str, ++i, " ");
		}
		else if ((*str)[i] == '<' && (*str)[i + 1] && (*str)[i + 1] == '<')
		{
			*str = ft_stradd(*str, i++, " ");
			*str = ft_stradd(*str, ++i, " ");
		}
		else if ((*str)[i] == '|' && (*str)[i + 1] && (*str)[i + 1] == '|')
		{
			*str = ft_stradd(*str, i++, " ");
			*str = ft_stradd(*str, ++i, " ");
		}
		else if ((*str)[i] == '&' && (*str)[i + 1] && (*str)[i + 1] == '&')
		{
			*str = ft_stradd(*str, i++, " ");
			*str = ft_stradd(*str, ++i, " ");
		}
		else
			i++;
	}
}
