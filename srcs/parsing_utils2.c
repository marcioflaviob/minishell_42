/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:31:48 by trimize           #+#    #+#             */
/*   Updated: 2024/05/15 13:47:25 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	go_af_par(char **args)
{
	int	i;
	int	par;

	i = 1;
	par = 1;
	while (par != 0 && args[i])
	{
		if (args[i][0] == '(')
			par++;
		else if (args[i][0] == ')')
			par--;
		i++;
	}
	if (args[i - 1][0] != ')')
		return (0);
	return (i);
}
