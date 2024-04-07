/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:54:50 by trimize           #+#    #+#             */
/*   Updated: 2024/04/06 15:02:11 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_around_dquotes(char *str, int pos)
{
	int	i;
	int	checker;

	i = 0;
	checker = 0;
	while (i < pos)
		if (str[i++] == '"')
			mod_checker(&checker);
	return (checker);
}

int	is_around_squotes(char *str, int pos)
{
	int	i;
	int	checker;

	i = 0;
	checker = 0;
	while (i < pos)
		if (str[i++] == '\'')
			mod_checker(&checker);
	if (checker)
	{
		while (str[i])
			if (str[i++] == '\'')
				return (checker);
		return (0);
	}
	return (checker);
}

int	find_first_squote_back(char *str, int pos)
{
	while (pos >= 0)
	{
		if (str[pos] == '\'')
			return (pos);
		pos--;
	}
	return (-1);
}

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		printf("%s\n", tab[i++]);
}

char	*get_curr_dir(char *path)
{
	int		i;
	int		y;
	char	*curr_dir;

	i = 0;
	y = 0;
	while (path[i])
		i++;
	while (path[i] != '/')
	{
		y++;
		i--;
	}
	i++;
	curr_dir = (char *)malloc(y * sizeof(char));
	y = 0;
	while (path[i])
		curr_dir[y++] = path[i++];
	curr_dir[y] = 0;
	return (curr_dir);
}
