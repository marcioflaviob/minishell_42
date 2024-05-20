/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_better_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:18:13 by trimize           #+#    #+#             */
/*   Updated: 2024/05/20 15:30:15 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	word_len(char const *str)
{
	int	i;
	int	squote_flag;
	int	dquote_flag;

	i = 0;
	squote_flag = 0;
	dquote_flag = 0;
	while (str[i] && (str[i] != ' ' || (squote_flag || dquote_flag)))
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			if (str[i] == '"' && !squote_flag)
				dquote_flag = !dquote_flag;
			else if (str[i] == '\'')
				squote_flag = !squote_flag;
			i++;
			continue ;
		}
		if ((str[i] == '(' || str[i] == ')') && !squote_flag && !dquote_flag)
		{
			if (i != 0)
				break ;
			else
				i++;
			continue ;
		}
		i++;
	}
	return (i);
}

static int	initial_config(int *i, int *j, int size, char ***tab)
{
	*i = 0;
	*j = 0;
	*tab = (char **)malloc(size * sizeof(char *));
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

void	ft_better_split_helper(int i, int *j, char ***tab, char *s)
{
	(*tab)[i][0] = s[(*j)++];
	(*tab)[i][1] = '\0';
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
			tab[i] = (char *)malloc((word_len(s + j) + 1) * sizeof(char));
			if (null_handler(tab, &i) == 0 || tab[i] == NULL)
				return (NULL);
			if (s[j] == '(' || s[j] == ')')
				ft_better_split_helper(i, &j, &tab, s);
			else
				(ft_strlcpy(tab[i], (char *)s + j, word_len(s + j) + 1), j
					+= word_len((s + j)));
			i++;
		}
		else
			j++;
	}
	return (free(s), tab[i] = NULL, tab);
}
