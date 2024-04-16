/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 23:24:42 by mbrandao          #+#    #+#             */
/*   Updated: 2024/04/13 15:10:41 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	echo(char **args, t_sh *sh)
{
	int	i;
	int	y;

	i = 1;
	if (!args[i])
		printf("\n");
	else if (ft_equalstr(args[i++], "-n"))
	{
		while (args[i])
		{
			printf("%s", args[i++]);
			if (args[i])
				printf(" ");
		}
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
			printf("%s", args[i++]);
			if (args[i])
				printf(" ");
		}
		printf("\n");
	}
}
