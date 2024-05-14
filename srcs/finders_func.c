/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finders_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 19:10:19 by trimize           #+#    #+#             */
/*   Updated: 2024/05/14 21:47:56 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_sp(char **args, t_sh *sh)
{
	int	i;
	int	j;

	i = 0;
	j = sh->position;
	while (args[i])
	{
		if ((args[i][0] == '<' && sh->sp_bool[j] == 1)
			|| (args[i][0] == '>' && sh->sp_bool[j] == 1)
			|| (args[i][0] == '|' && sh->sp_bool[j] == 1))
			return (i);
		if ((ft_equalstr(args[i], "||") && sh->sp_bool[j] == 1)
			|| (ft_equalstr(args[i], ">>") && sh->sp_bool[j] == 1)
			|| (ft_equalstr(args[i], "&&") && sh->sp_bool[j] == 1))
			return (i);
		i++;
		j++;
	}
	return (0);
}

int	find_sp_redir(char **args, t_sh *sh, int j)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if ((args[i][0] == '<' && sh->sp_bool[j] == 1)
			|| (args[i][0] == '>' && sh->sp_bool[j] == 1)
			|| (args[i][0] == '|' && sh->sp_bool[j] == 1))
			return (i);
		if ((ft_equalstr(args[i], "||") && sh->sp_bool[j] == 1)
			|| (ft_equalstr(args[i], ">>") && sh->sp_bool[j] == 1)
			|| (ft_equalstr(args[i], "&&") && sh->sp_bool[j] == 1))
			return (i);
		i++;
		j++;
	}
	return (0);
}

int	find_non_redir(char **args, t_sh *sh)
{
	int	i;
	int	j;

	i = 0;
	j = sh->position;
	while (args[i])
	{
		if ((args[i][0] == '|' && sh->sp_bool[j] == 1))
			return (i);
		if ((ft_equalstr(args[i], "||") && sh->sp_bool[j] == 1)
			|| (ft_equalstr(args[i], "&&") && sh->sp_bool[j] == 1))
			return (i);
		i++;
		j++;
	}
	return (tab_len(sh->args) - 1 - sh->position);
}

int	find_sp_echo(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (ft_equalstr(args[i], ">")
			|| ft_equalstr(args[i], "|")
			|| ft_equalstr(args[i], "<"))
			return (i);
		if ((ft_equalstr(args[i], "||"))
			|| (ft_equalstr(args[i], ">>"))
			|| (ft_equalstr(args[i], "&&")))
			return (i);
		i++;
	}
	return (0);
}

int	find_sp_par(char **args, t_sh *sh)
{
	int	i;
	int	j;

	i = 0;
	j = sh->position;
	while (args[i])
	{
		if ((args[i][0] == '<' && sh->sp_bool[j] == 1)
			|| (args[i][0] == '>' && sh->sp_bool[j] == 1)
			|| (args[i][0] == '|' && sh->sp_bool[j] == 1)
			|| (args[i][0] == ')' && sh->sp_bool[j] == 1))
			return (i);
		if ((ft_equalstr(args[i], "||") && sh->sp_bool[j] == 1)
			|| (ft_equalstr(args[i], ">>") && sh->sp_bool[j] == 1)
			|| (ft_equalstr(args[i], "&&") && sh->sp_bool[j] == 1))
			return (i);
		i++;
		j++;
	}
	return (0);
}

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

char	*find_path(char *command, t_sh *sh)
{
	int		i;
	char	**paths;
	char	*str;

	i = 0;
	if (get_type(command) != -1 && ft_strchr(command, '/'))
	{
		if (get_type(command) == 1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(command, 2);
			ft_putstr_fd(": Is a directory\n", 2);
			exit(126);
		}
		if (access(command, X_OK) != -1)
			return (command);
		if (access(command, X_OK) == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(command, 2);
			ft_putstr_fd(": Permission denied\n", 2);
			exit(126);
		}
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
	ft_putstr_fd("\n", 2);
	freetab(paths);
	return (NULL);
}
