/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finders_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 19:10:19 by trimize           #+#    #+#             */
/*   Updated: 2024/05/31 21:03:59 by trimize          ###   ########.fr       */
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

void	fp_helper(char *command, t_sh *sh)
{
	if (get_type(command) == 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(command, 2);
		ft_putstr_fd(": Is a directory\nz", 2);
		child_free(sh);
		exit(126);
	}
	if (access(command, X_OK) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(command, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		child_free(sh);
		exit(126);
	}
}

void	fp_helper2(char ***paths, t_sh *sh)
{
	char	*str;

	str = get_env("PATH", sh);
	if (!str)
		(child_free(sh), ft_putstr_fd("minishell: command not found", 2),
			exit(1));
	*paths = ft_split(str, ':');
	free(str);
}

char	*find_path(char *command, t_sh *sh)
{
	int		i;
	char	**paths;
	char	*str;

	i = 0;
	if (get_type(command) != -1 && ft_strchr(command, '/'))
	{
		fp_helper(command, sh);
		if (access(command, X_OK) != -1)
			return (command);
	}
	fp_helper2(&paths, sh);
	while (paths[i])
	{
		str = ft_strjoin(paths[i++], "/");
		str = ft_strjoin_gnl(str, command);
		if (access(str, X_OK) != -1)
			return (freetab(paths), str);
		free(str);
	}
	ft_putstr_fd("minishell: ", 2);
	(ft_putstr_fd(command, 2), ft_putstr_fd(": command not found", 2));
	return (ft_putstr_fd("\n", 2), freetab(paths), NULL);
}
