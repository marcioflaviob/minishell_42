/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:40:56 by mbrandao          #+#    #+#             */
/*   Updated: 2024/05/20 15:40:22 by mbrandao         ###   ########.fr       */
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
	int	j;
	int	s_quote;
	int	d_quote;

	j = 0;
	s_quote = 0;
	d_quote = 0;
	while (j < i)
	{
		if (str[j] == '"' && !s_quote)
			d_quote = !d_quote;
		else if (str[j] == '\'')
			s_quote = !s_quote;
		j++;
	}
	if (s_quote || d_quote)
		return (1);
	return (0);
}

void	sa_add(char **str, int *i)
{
	*str = ft_stradd(*str, (*i)++, " ");
	*str = ft_stradd(*str, ++(*i), " ");
}

void	sa_add_extra(char **str, int *i)
{
	*str = ft_stradd(*str, (*i)++, " ");
	(*i)++;
	*str = ft_stradd(*str, ++(*i), " ");
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
			sa_add(str, &i);
		else if ((*str)[i] == '<' && (*str)[i + 1] && (*str)[i + 1] != '<')
			sa_add(str, &i);
		else if ((*str)[i] == '|' && (*str)[i + 1] && (*str)[i + 1] != '|')
			sa_add(str, &i);
		else if ((*str)[i] == '>' && (*str)[i + 1] && (*str)[i + 1] == '>')
			sa_add_extra(str, &i);
		else if ((*str)[i] == '<' && (*str)[i + 1] && (*str)[i + 1] == '<')
			sa_add_extra(str, &i);
		else if ((*str)[i] == '|' && (*str)[i + 1] && (*str)[i + 1] == '|')
			sa_add_extra(str, &i);
		else if ((*str)[i] == '&' && (*str)[i + 1] && (*str)[i + 1] == '&')
			sa_add_extra(str, &i);
		else
			i++;
	}
}
