/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:40:39 by mbrandao          #+#    #+#             */
/*   Updated: 2024/04/28 18:28:01 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_int_strstr_wc(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		while (to_find[j] && (str[i + j] == to_find[j]))
			j++;
		if (to_find[j] == '\0')
			return (i);
		else
		{
			j = 0;
			i++;
		}
	}
	if (to_find[j] == '\0')
		return (i);
	return (-1);
}

char	*ft_strstr_wc(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		while (to_find[j] && (str[i + j] == to_find[j]))
			j++;
		if (to_find[j] == '\0')
			return (str + i);
		else
		{
			j = 0;
			i++;
		}
	}
	if (to_find[j] == '\0')
		return (str + i);
	return (NULL);
}

int	ft_int_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return (i);
		i++;
	}
	if ((unsigned char)c == 0)
		return (i);
	else
		return (-1);
}

void	fill_ba(char **b, char **a, char *input)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	*b = ft_strdup("");
	*a = ft_strdup("");
	while (input[i] != '*')
		*b = ft_strjoin_gnl(*b, &(input[i++]));
	i++;
	while (input[i])
		*a = ft_strjoin_gnl(*a, &(input[i++]));
}

int	ft_tabchr(char **tab, char c)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (ft_strchr(tab[i], c))
			return (i);
		i++;
	}
	return (-1);
}
