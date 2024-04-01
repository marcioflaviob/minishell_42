/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 18:50:22 by trimize           #+#    #+#             */
/*   Updated: 2024/04/01 23:34:52 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	str_add(char *str, char *add)
{
	int	i;

	i = 0;
	while (add[i])
	{
		str[i] = add[i];
		i++;
	}
}

int	tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	ft_isalnum_or_score(int c)
{
	if ((48 <= c && c <= 57) || ((65 <= c && c <= 90) || (97 <= c && c <= 122)))
		return (1);
	if (c == '_')
		return (1);
	return (0);
}

void	ft_strerase(char **str, int start, int num)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = start + num;
	if (start > ft_strlen_gnl(*str) || i > ft_strlen_gnl(*str)
		|| num > ft_strlen_gnl(*str))
		return ;
	result = malloc ((ft_strlen(*str) - num) + 1 * sizeof(char));
	if (!result)
		return ;
	while (i < start)
	{
		result[i] = (*str)[i];
		i++;
	}
	while ((*str)[j])
		result[i++] = (*str)[j++];
	result[i] = 0;
	*str = result;
}

char	*ft_stradd(char *str, int start, char *add)
{
	char	*first_part;
	char	*second_part;
	char	*result;

	first_part = ft_substr(str, 0, start);
	second_part = ft_substr(str, start, (ft_strlen(str) - start));
	result = ft_strjoin(first_part, add);
	result = ft_strjoin_gnl(result, second_part);
	free(first_part);
	free(second_part);
	free(str);
	return (result);
}

void	mod_checker(int *checker)
{
	if (*checker == 0)
		*checker = 1;
	else
		*checker = 0;
}

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
