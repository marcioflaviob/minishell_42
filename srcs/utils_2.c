/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:23:01 by trimize           #+#    #+#             */
/*   Updated: 2024/04/28 18:40:20 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	remove_from_tab(char ***tab, int pos)
{
	int		i;
	int		y;
	char	**tmp_tab;

	i = 0;
	y = -1;
	tmp_tab = (char **)malloc((tab_len(*tab)) * sizeof(char *));
	if (!tmp_tab)
		(ft_putstr_fd("Malloc error remove_from_tab\n", 2), exit(EXIT_FAILURE));
	while ((*tab)[i])
	{
		if (i != pos)
			tmp_tab[++y] = ft_strdup((*tab)[i]);
		i++;
	}
	tmp_tab[++y] = NULL;
	freetab(*tab);
	*tab = tmp_tab;
}

void	add_to_tab_pos(char ***tab, char *str, int pos)
{
	int		i;
	int		len;
	char	**tmp;

	i = 0;
	if ((*tab)[0] == NULL)
		len = 2;
	while ((*tab)[i])
		i++;
	len = i + 2;
	tmp = (char **)malloc(len * sizeof(char *));
	if (!tmp)
		(ft_putstr_fd("Malloc error add_to_tab_pos\n", 2), exit(EXIT_FAILURE));
	i = -1;
	while ((*tab)[++i] && i < pos)
		tmp[i] = ft_strdup((*tab)[i]);
	tmp[i] = ft_strdup(str);
	while ((*tab)[i])
	{
		tmp[i + 1] = ft_strdup((*tab)[i]);
		i++;
	}
	tmp[i + 1] = NULL;
	freetab(*tab);
	*tab = tmp;
}

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
	if (!tmp)
		(ft_putstr_fd("Malloc error add to tab\n", 2), exit(EXIT_FAILURE));
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
			if (!tmp_tab)
				(ft_putstr_fd("Malloc error rm_tab_line\n", 2),
					exit(EXIT_FAILURE));
			while (++y < i)
				tmp_tab[y] = ft_strdup((*tab)[y]);
			while ((*tab)[++y])
				tmp_tab[y - 1] = ft_strdup((*tab)[y]);
			tmp_tab[y - 1] = NULL;
			(freetab(*tab), copy_tab(tab, tmp_tab), freetab(tmp_tab));
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
	if (!*taker)
		(ft_putstr_fd("Malloc error copying tab\n", 2), exit(EXIT_FAILURE));
	i = 0;
	while (giver[i])
	{
			(*taker)[i] = ft_strdup(giver[i]);
		i++;
	}
	(*taker)[i] = NULL;
}
