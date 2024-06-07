/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 23:24:42 by mbrandao          #+#    #+#             */
/*   Updated: 2024/06/07 18:39:22 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	echo_helper(t_sh *sh, char **str, char **args)
{
	if (find_sp_par(&args[0], sh))
		sh->echo_y = find_sp_par(&args[0], sh);
	else
		sh->echo_y = tab_len(args) - 1;
	while (sh->echo_i < sh->echo_y)
	{
		*str = ft_strjoin_gnl(*str, args[sh->echo_i++]);
		if (args[sh->echo_i])
			*str = ft_strjoin_gnl(*str, " ");
	}
}

void	echo_helper_2(t_sh *sh, char **str, char **args)
{
	if (ft_equalstr(args[sh->echo_i], "<")
		|| ft_equalstr(args[sh->echo_i], "<<")
		|| ft_equalstr(args[sh->echo_i], ">")
		|| ft_equalstr(args[sh->echo_i], "<<"))
		sh->echo_i += 2;
	if (args[sh->echo_i])
	{
		*str = ft_strjoin_gnl(*str, args[sh->echo_i++]);
		if (args[sh->echo_i])
			*str = ft_strjoin_gnl(*str, " ");
	}
}

char	*echo(char **args, t_sh *sh)
{
	char	*str;

	sh->echo_i = 1;
	str = 0;
	if (!args[sh->echo_i])
		return (str = ft_strjoin_gnl(str, "\n"), str);
	else if (ft_equalstr(args[sh->echo_i++], "-n"))
		return (echo_helper(sh, &str, args), str);
	else
	{
		sh->echo_i = 1;
		while (!ft_equalstr(args[sh->echo_i], "|")
			&& !ft_equalstr(args[sh->echo_i], "||")
			&& !ft_equalstr(args[sh->echo_i], "&&") && args[sh->echo_i])
			echo_helper_2(sh, &str, args);
		str = ft_strjoin_gnl(str, "\n");
		return (str);
	}
}
