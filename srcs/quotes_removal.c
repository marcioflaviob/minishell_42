/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_removal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 00:27:17 by mbrandao          #+#    #+#             */
/*   Updated: 2024/04/06 22:39:29 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//TODO Fix quote removal

int	qrh_init(int *i, int *j, char *str, char **result)
{
	*i = 0;
	*j = 0;
	*result = malloc(ft_strlen(str) + 1);
	if (!(*result))
		return -1;
	return (0);
}

void	qrh_helper1(int *iq, char *q)
{
	*iq = 0;
	*q = '\0';
}

void	qrh_helper2(int *iq, char *q, char **str, int i)
{
	*iq = 1;
	*q = (*str)[i];
}

void	quotes_removal_helper(char **str)
{
	int		i;
	int		j;
	int		in_quotes;
	char	quote_char;
	char	*result;

	in_quotes = 0;
	quote_char = qrh_init(&i, &j, *str, &result);
	while ((*str)[i])
	{
		if ((*str)[i] == '\'' || (*str)[i] == '\"')
		{
			if (in_quotes && (*str)[i] == quote_char)
				qrh_helper1(&in_quotes, &quote_char);
			else if (!in_quotes)
				qrh_helper2(&in_quotes, &quote_char, str, i);
			else
				result[j++] = (*str)[i];
		}
		else
			result[j++] = (*str)[i];
		i++;
	}
	result[j] = '\0';
	(free(*str), *str = result);
}


// void	quotes_removal_helper(char **str)
// {
// 	int	i;

// 	i = 0;
// 	while ((*str)[i])
// 	{
// 		if ((*str)[i] == '\'')
// 		{
// 			if (is_around_squotes(*str, i))
// 			{
// 				ft_strerase(str, i, 1);
// 				while ((*str)[i++] != '\'')
// 					;
// 				ft_strerase(str, i, 1);
// 			}
// 		}
// 		if ((*str)[i] == '\"')
// 		{
// 			if (is_around_dquotes(*str, i))
// 			{
// 				ft_strerase(str, i, 1);
// 				while ((*str)[i++] != '\"')
// 					;
// 				ft_strerase(str, i, 1);
// 			}
// 		}
// 		i++;
// 	}
// }

void	quotes_removal(char ***cmds)
{
	int	i;

	i = 0;
	while ((*cmds)[i])
	{
		quotes_removal_helper((&(*cmds)[i]));
		i++;
	}
}
//ls | cat file1 && cat M*k* *READ* *i