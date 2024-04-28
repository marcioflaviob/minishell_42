/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:54:50 by trimize           #+#    #+#             */
/*   Updated: 2024/04/28 18:38:57 by mbrandao         ###   ########.fr       */
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
	{
		ft_putstr_fd(tab[i++], 1);
		ft_putstr_fd("\n", 1);
	}
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
	if (!curr_dir)
		(ft_putstr_fd("Malloc error getting the current dir\n", 2),
			exit(EXIT_FAILURE));
	y = 0;
	while (path[i])
		curr_dir[y++] = path[i++];
	curr_dir[y] = 0;
	return (curr_dir);
}
