/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign_dealer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 18:30:25 by mbrandao          #+#    #+#             */
/*   Updated: 2024/05/21 17:43:28 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_var_name(char *str)
{
	int		i;

	i = 0;
	if (str[i] == '?')
		return (ft_strdup("?"));
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

void	replace_env_helper(char ***str, t_sh *sh)
{
	int		j;
	char	*var_name;
	char	*var_val;

	j = has_dollar_sign(**str);
	var_name = get_var_name(**str + (j + 1));
	var_val = get_env(var_name, sh);
	if (!var_val)
		ft_strerase(*str, j, ft_strlen(var_name) + 1);
	else
	{
		ft_strerase(*str, j, ft_strlen(var_name) + 1);
		**str = ft_stradd(**str, j, var_val);
	}
}

void	replace_env(char **str, t_sh *sh)
{
	int		i;
	int		j;
	int		tmp;

	i = 0;
	j = has_dollar_sign(*str);
	while (j != -1)
	{	
		if (is_around_squotes(*str, j) && (!is_around_dquotes(*str, j)
				|| is_dquote_in_squote(*str, j)))
			;
		else
			replace_env_helper(&str, sh);
		tmp = j;
		if (has_dollar_sign(*str + (j + 1)) != -1)
			j = has_dollar_sign(*str + (j + 1)) + tmp + 1;
		else
			j = -1;
	}
}

void	dollar_sign_dealer(char ***commands, t_sh *sh)
{
	int	i;

	i = 0;
	while ((*commands)[i])
	{
		if (has_dollar_sign((*commands)[i]) >= 0)
			replace_env(&(*commands)[i], sh);
		i++;
	}
}
