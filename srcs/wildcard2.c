/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 18:27:24 by mbrandao          #+#    #+#             */
/*   Updated: 2024/05/13 16:40:54 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	remove_quotes(char **str)
{
	char	*src;
	char	*dst;

	src = *str;
	dst = *str;
	while (*src)
	{
		if (*src == '\\' && (*(src + 1) == '\"' || *(src + 1) == '\''))
		{
			src++;
		}
		else if (*src == '\"' || *src == '\'')
		{
			src++;
			continue ;
		}
		*dst++ = *src++;
	}
	*dst = '\0';
}

int	ft_part_len(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}
