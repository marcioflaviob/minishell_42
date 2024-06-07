/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:54:50 by trimize           #+#    #+#             */
/*   Updated: 2024/05/31 20:52:40 by trimize          ###   ########.fr       */
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
	{
		if (str[i] == '"')
			checker = !checker;
		i++;
	}
	if (checker)
		return (1);
	return (0);
}

int	is_around_squotes(char *str, int pos)
{
	int	i;
	int	checker;
	int	d_quote;

	i = 0;
	checker = 0;
	d_quote = 0;
	while (i < pos)
	{
		if (str[i] == '"')
		{
			d_quote = !d_quote;
			if (!d_quote && checker)
				checker = !checker;
		}
		if (str[i] == '\'')
			checker = !checker;
		i++;
	}
	if (checker)
		return (1);
	return (0);
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
