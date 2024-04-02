/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign_dealer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 18:30:25 by mbrandao          #+#    #+#             */
/*   Updated: 2024/04/02 13:14:35 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_var_name(char *str)
{
	int		i;

	i = 0;
	while (str[i] && ft_isalnum_or_score(str[i]))
		i++;
	return (ft_substr(str, 0, i));
}

int	has_dollar_sign(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}

void	replace_env_helper(char ***str)
{
	int		j;
	char	*var_name;
	char	*var_val;

	j = has_dollar_sign(**str);
	var_name = get_var_name(**str + (j + 1));
	var_val = "random_value";
	if (!var_val)
		ft_strerase(*str, j, ft_strlen(var_name) + 1);
	else
	{
		ft_strerase(*str, j, ft_strlen(var_name) + 1);
		**str = ft_stradd(**str, j, var_val);
	}
}

void	replace_env(char **str)
{
	int		i;
	int		j;

	i = 0;
	j = has_dollar_sign(*str);
	while (j != -1)
	{	
		if (is_around_squotes(*str, j) && !is_around_dquotes(*str, j))
			;
		else
			replace_env_helper(&str);
		j = has_dollar_sign(*str + (j + 1));
	}
}

void	dollar_sign_dealer(char ***commands)
{
	int	i;

	i = 0;
	while ((*commands)[i])
	{
		if (has_dollar_sign((*commands)[i]) >= 0)
			replace_env(&(*commands)[i]);
		i++;
	}
}
