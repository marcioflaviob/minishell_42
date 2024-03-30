/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 23:24:42 by mbrandao          #+#    #+#             */
/*   Updated: 2024/03/30 23:54:19 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	echo(char **args)
{
	int	i;

	i = 1;
	if (!args[i])
		write(1, "\n", 1);
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
		while (args[i])
		{
			printf("%s", args[i++]);
			if (args[i])
				printf(" ");
		}
		printf("\n");
	}
}
