/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 15:26:55 by mbrandao          #+#    #+#             */
/*   Updated: 2024/03/30 17:44:13 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cd(t_sh *sh, char *folder) //TODO
{
	if (chdir(folder) == -1)
	{
		printf("minishell: cd: %s: No such file or directory", folder);
	}
}
