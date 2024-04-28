/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:40:56 by mbrandao          #+#    #+#             */
/*   Updated: 2024/04/28 18:37:44 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_sp_bool(t_sh *sh)
{
	int	*result;
	int	i;
	int	tmp;

	i = 0;
	result = (int *)malloc((tab_len(sh->args) - 1) * sizeof(int));
	if (!result)
		(ft_putstr_fd("Malloc error getting sp bool\n", 2), exit(EXIT_FAILURE));
	while (sh->args[i])
	{
		tmp = find_sp_str(sh->args[i]);
		if (tmp != -1 && !is_quoted(sh->args[i], tmp))
			result[i++] = 1;
		else
			result[i++] = 0;
	}
	sh->sp_bool = result;
}

int	is_quoted(char *str, int i)
{
	if (is_around_dquotes(str, i) || is_around_squotes(str, i))
		return (1);
	return (0);
}



void	space_adder(char **str)
{
	int		i;

	i = 0;
	while ((*str)[i])
	{
		if (is_quoted(*str, i))
			i++;
		else if ((*str)[i] == '>' && (*str)[i + 1] && (*str)[i + 1] != '>')
		{
			*str = ft_stradd(*str, i++, " ");
			*str = ft_stradd(*str, ++i, " ");
		}
		else if ((*str)[i] == '<' && (*str)[i + 1] && (*str)[i + 1] != '<')
		{
			*str = ft_stradd(*str, i++, " ");
			*str = ft_stradd(*str, ++i, " ");
		}
		else if ((*str)[i] == '|' && (*str)[i + 1] && (*str)[i + 1] != '|')
		{
			*str = ft_stradd(*str, i++, " ");
			*str = ft_stradd(*str, ++i, " ");
		}
		else if ((*str)[i] == '>' && (*str)[i + 1] && (*str)[i + 1] == '>')
		{
			*str = ft_stradd(*str, i++, " ");
			i++;
			*str = ft_stradd(*str, ++i, " ");
		}
		else if ((*str)[i] == '<' && (*str)[i + 1] && (*str)[i + 1] == '<')
		{
			*str = ft_stradd(*str, i++, " ");
			i++;
			*str = ft_stradd(*str, ++i, " ");
		}
		else if ((*str)[i] == '|' && (*str)[i + 1] && (*str)[i + 1] == '|')
		{
			*str = ft_stradd(*str, i++, " ");
			i++;
			*str = ft_stradd(*str, ++i, " ");
		}
		else if ((*str)[i] == '&' && (*str)[i + 1] && (*str)[i + 1] == '&')
		{
			*str = ft_stradd(*str, i++, " ");
			i++;
			*str = ft_stradd(*str, ++i, " ");
		}
		else
			i++;
	}
}

void	swap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	sort_strings_by_first_char(char **arr, int n)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < n - 1)
	{
		while (j < n - i - 1)
		{
			if (arr[j][0] > arr[j + 1][0])
				swap(&arr[j], &arr[j + 1]);
			j++;
		}
		j = 0;
		i++;
	}
}
