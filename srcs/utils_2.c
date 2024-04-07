/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:23:01 by trimize           #+#    #+#             */
/*   Updated: 2024/04/03 17:26:47 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_to_tab(char ***tab, char *str)
{
	int		i;
	int		allocated;
	int		len;
	char	**tmp;

	i = 0;
	if (!(*tab))
	{
		len = 2;
		allocated = 0;
	}
	else
	{
		allocated = 1;
		while ((*tab)[i])
			i++;
		len = i + 2;
	}
	tmp = (char **)malloc(len * sizeof(char *));
	i = 0;
	if (allocated == 1)
	{
		while ((*tab)[i])
		{
			tmp[i] = ft_strdup((*tab)[i]);
			i++;
		}
	}
	tmp[i] = ft_strdup(str);
	tmp[i + 1] = NULL;
	if (allocated == 1)
		freetab(*tab);
	*tab = tmp;
}

void	rm_tab_line(char ***tab, char *line)
{
	int		i;
	int		y;
	char	**tmp_tab;

	i = 0;
	y = -1;
	while ((*tab)[i])
	{
		if (ft_equalstr((*tab)[i], line))
		{
			tmp_tab = (char **)malloc((tab_len(*tab) - 1) * sizeof(char *));
			while (++y < i)
				tmp_tab[y] = ft_strdup((*tab)[y]);
			while ((*tab)[++y])
				tmp_tab[y - 1] = ft_strdup((*tab)[y]);
			tmp_tab[y - 1] = NULL;
			freetab(*tab);
			copy_tab(tab, tmp_tab);
			freetab(tmp_tab);
			break ;
		}
		i++;
	}
	return ;
}

void	copy_tab(char ***taker, char **giver)
{
	int	i;

	i = 0;
	while (giver[i])
		i++;
	*taker = (char **)malloc((i + 1) * sizeof(char *));
	i = 0;
	while (giver[i])
	{
		(*taker)[i] = ft_strdup(giver[i]);
		i++;
	}
	(*taker)[i] = NULL;
}

char	*get_substring_b(char *str, char c)
{
	int		i;
	char	*substr;

	i = 0;
	while (str[i] != c)
		i++;
	substr = (char *)malloc((i + 1) * sizeof(char));
	i = 0;
	while (str[i] != c)
	{
		substr[i] = str[i];
		i++;
	}
	substr[i] = 0;
	return (substr);
}

char	*get_substring_a(char *str, char c)
{
	int		i;
	int		y;
	char	*substr;

	i = ft_strlen(str) - 1;
	y = 0;
	while (str[i] != c)
	{
		y++;
		i--;
	}
	i++;
	substr = (char *)malloc((y + 1) * sizeof(char));
	y = 0;
	while (str[i])
		substr[y++] = str[i++];
	substr[y] = 0;
	return (substr);
}
