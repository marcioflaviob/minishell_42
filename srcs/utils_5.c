/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 18:37:46 by mbrandao          #+#    #+#             */
/*   Updated: 2024/04/28 18:39:25 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*sorted_tab(char **tab)
{
	int		n;
	int		i;
	char	*str;

	n = tab_len(tab) - 1;
	i = 0;
	str = 0;
	sort_strings_by_first_char(tab, n);
	while (tab[i])
	{
		str = ft_strjoin_gnl(str, tab[i++]);
		str = ft_strjoin_gnl(str, "\n");
	}
	return (str);
}

char	*get_substring_b(char *str, char c)
{
	int		i;
	char	*substr;

	i = 0;
	while (str[i] != c)
		i++;
	substr = (char *)malloc((i + 1) * sizeof(char));
	if (!substr)
		(ft_putstr_fd("Malloc error getting substring\n", 2),
			exit(EXIT_FAILURE));
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
	if (!substr)
		(ft_putstr_fd("Malloc error getting substring\n", 2),
			exit(EXIT_FAILURE));
	y = 0;
	while (str[i])
		substr[y++] = str[i++];
	substr[y] = 0;
	return (substr);
}