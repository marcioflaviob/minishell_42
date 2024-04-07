/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_better_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 16:45:19 by mbrandao          #+#    #+#             */
/*   Updated: 2024/04/03 15:09:02 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_args(char const *str)
{
	int	i;
	int	args;

	i = 0;
	args = 0;
	while (str[i])
	{
		while ((str[i] != 0) && (str[i] == ' '))
			i++;
		if (str[i])
		{
			if (str[i] == '\'')
				while (str[++i] != '\'')
					;
			else if (str[i] == '"')
				while (str[++i] != '"')
					;
			i++;
			args++;
		}
		while ((str[i] != 0) && (str[i] != ' '))
			i++;
	}
	return (args);
}

static int	word_len(char const *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ')
	{
		if (str[i] == '\'')
			while (str[++i] != '\'')
				;
		else if (str[i] == '"')
			while (str[++i] != '"')
				;
		i++;
		while ((str[i] != 0) && (str[i] != ' '))
			i++;
	}
	return (i);
}

static int	initial_config(int *i, int *j, int size, char ***tab)
{
	*i = 0;
	*j = 0;
	*tab = (char **) malloc(size * sizeof(char *));
	if (*tab == NULL)
		return (0);
	else
		return (1);
}

static int	null_handler(char **tab, int *i)
{
	int	index;

	index = *i;
	if (tab[index] == NULL)
	{
		while (index--)
			free(tab[index]);
		free(tab);
		return (0);
	}
	*i = index;
	return (1);
}

char	**ft_better_split(char *s)
{
	int		i;
	int		j;
	char	**tab;

	space_adder(&s);
	if (!s || (initial_config(&i, &j, (count_args(s) + 1), &tab) == 0))
		return (NULL);
	while (i < count_args(s))
	{
		if (s[j] != ' ')
		{
			tab[i] = (char *) malloc((word_len(s + j) + 1) * sizeof(char));
			if (null_handler(tab, &i) == 0 || tab[i] == NULL)
				return (NULL);
			ft_strlcpy(tab[i], (char *) s + j, word_len(s + j) + 1);
			j += word_len((s + j));
			i++;
		}
		else
			j++;
	}
	tab[i] = NULL;
	return (tab);
}
