/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 23:24:42 by mbrandao          #+#    #+#             */
/*   Updated: 2024/04/22 18:20:19 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*echo(char **args, t_sh *sh)
{
	int	i;
	int	y;
	char	*str;

	i = 1;
	str = 0;
	if (!args[i])
		return (str = ft_strjoin_gnl(str, "\n"), str);
	else if (ft_equalstr(args[i++], "-n"))
	{
		if (find_sp(&args[0], sh))
			y = find_sp(&args[0], sh);
		else
			y = tab_len(args) - 1;
		while (i < y)
		{
			str = ft_strjoin_gnl(str, args[i++]);
			if (args[i])
				str = ft_strjoin_gnl(str, " ");
		}
		return (str);
	}
	else
	{
		i = 1;
		if (find_sp(&args[0], sh))
			y = find_sp(&args[0], sh);
		else
			y = tab_len(args) - 1;
		while (i < y)
		{
			str = ft_strjoin_gnl(str, args[i++]);
			if (args[i])
				str = ft_strjoin_gnl(str, " ");
		}
		str = ft_strjoin_gnl(str, "\n");
		return (str);
	}
}
