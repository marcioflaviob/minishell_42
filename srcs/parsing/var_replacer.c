/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_replacer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:59:46 by mbrandao          #+#    #+#             */
/*   Updated: 2024/05/20 12:46:45 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_variable_index(char **variables, char *name, t_sh *sh)
{
	int		i;
	char	*tmp;

	i = 0;
	while (variables[i])
	{
		tmp = get_substring_b(variables[i], '=', sh);
		if (ft_equalstr(tmp, name))
			return (free(tmp), i);
		i++;
	}
	free(tmp);
	return (-1);
}

void	add_env(t_sh *sh, char *variable)
{
	int		index;
	char	*name;
	char	*tmp;

	name = get_var_name(variable);
	index = find_variable_index(sh->variables, name, sh);
	if (index != -1)
	{
		remove_from_tab(&(sh->variables), index, sh);
		add_to_tab(&(sh->variables), variable);
	}
	else
	{
		tmp = get_env(variable, sh);
		if (!tmp)
		{
			if (name)
				add_to_tab(&(sh->variables), variable);
		}
		else
			export(sh, &variable);
		free(tmp);
	}
	free(name);
}

void	replace_var(t_sh *sh, char ***tab)
{
	int		i;
	int		index;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while ((*tab)[i])
	{
		index = ft_int_strchr((*tab)[i], '$');
		if (ft_int_strchr((*tab)[i], '=') != -1
			&& !is_quoted((*tab)[i], ft_int_strchr((*tab)[i], '=')))
			add_env(sh, (*tab)[i]);
		else if (index != -1 && (*tab)[i][index + 1]
			&& (*tab)[i][index + 1] != ' ' && (*tab)[i][index + 1] != '\''
			&& (*tab)[i][index + 1] != '\"' && (*tab)[i][index + 1] != ';')
			replace_env(&(*tab)[i], sh);
		i++;
	}
}
