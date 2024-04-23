/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_better_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:18:13 by trimize           #+#    #+#             */
/*   Updated: 2024/04/23 05:12:07 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_args(char const *str)
{
	int	i;
	int	args;
	int	quote_flag;

	i = 0;
	args = 0;
	quote_flag = 0;
	while (str[i])
	{
		while ((str[i] != 0) && (str[i] == ' '))
			i++;
		if (str[i])
		{
			if (str[i] == '\'' || str[i] == '"')
			{
				quote_flag = !quote_flag;
				i++;
				continue ;
			}
			else if ((str[i] == '(' || str[i] == ')') && !quote_flag)
			{
				args++;
				i++;
				continue ;
			}
			else if (!quote_flag)
			{
				args++;
				while ((str[i] != 0) && (str[i] != ' ' && str[i] != '(' && str[i] != ')') && !(str[i] == '\'' || str[i] == '"'))
					i++;
			}
			else
			{
				args++;
				while ((str[i] != 0) && (str[i] != '\'' && str[i] != '"'))
					i++;
				if (str[i] == '\'' || str[i] == '"')
					i++;
			}
		}
	}
	return (args);
}

static int	word_len(char const *str)
{
	int	i;
	int	quote_flag;

	i = 0;
	quote_flag = 0;
	while (str[i] && (str[i] != ' ' || quote_flag))
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote_flag = !quote_flag;
			i++;
			continue ;
		}
		if ((str[i] == '(' || str[i] == ')') && !quote_flag)
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
	// printf("args counter: %d\n", count_args(s));
	if (!s || (initial_config(&i, &j, (count_args(s) + 1), &tab) == 0))
		return (NULL);
	while (i < count_args(s))
	{
		if (s[j] != ' ')
		{
			tab[i] = (char *) malloc((word_len(s + j) + 1) * sizeof(char));
			if (null_handler(tab, &i) == 0 || tab[i] == NULL)
				return (NULL);
			if (s[j] == '(' || s[j] == ')')
			{
				tab[i][0] = s[j];
				tab[i][1] = '\0';
				j++;
			}
			else
			{
				ft_strlcpy(tab[i], (char *) s + j, word_len(s + j) + 1);
				j += word_len((s + j));
			}
			i++;
		}
		else
			j++;
	}
	free(s);
	tab[i] = NULL;
	return (tab);
}