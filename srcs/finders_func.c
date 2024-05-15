/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finders_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 19:10:19 by trimize           #+#    #+#             */
/*   Updated: 2024/05/15 14:56:17 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_sp_str(char *str)
{
	int	i;

	i = 0;
	if (ft_int_strstr_wc(str, "<<") != -1)
		return (ft_int_strstr_wc(str, "<<"));
	else if (ft_int_strstr_wc(str, ">>") != -1)
		return (ft_int_strstr_wc(str, ">>"));
	else if (ft_int_strstr_wc(str, "||") != -1)
		return (ft_int_strstr_wc(str, "||"));
	else if (ft_int_strstr_wc(str, "&&") != -1)
		return (ft_int_strstr_wc(str, "&&"));
	else if (ft_equalstr(str, "(") || ft_equalstr(str, ")"))
		return (0);
	else
	{
		while (str[i])
		{
			if (str[i] == '<' || str[i] == '>' || str[i] == '|')
				return (i);
			i++;
		}
		return (-1);
	}
}

void	fp_helper(char *command)
{
	if (get_type(command) == 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(command, 2);
		ft_putstr_fd(": Is a directory\nz", 2);
		exit(126);
	}
	if (access(command, X_OK) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(command, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		exit(126);
	}
}

char	*find_path(char *command, t_sh *sh)
{
	int		i;
	char	**paths;
	char	*str;

	i = 0;
	if (get_type(command) != -1 && ft_strchr(command, '/'))
	{
		fp_helper(command);
		if (access(command, X_OK) != -1)
			return (command);
	}
	paths = ft_split(get_env("PATH", sh), ':');
	while (paths[i])
	{
		str = ft_strjoin(paths[i++], "/");
		str = ft_strjoin_gnl(str, command);
		if (access(str, X_OK) != -1)
			return (freetab(paths), str);
		free(str);
	}
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": command not found", 2);
	(ft_putstr_fd("\n", 2), freetab(paths));
	return (NULL);
}
