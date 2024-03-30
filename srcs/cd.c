/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 15:26:55 by mbrandao          #+#    #+#             */
/*   Updated: 2024/03/30 16:19:29 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cd(char *folder)
{
	DIR* dir = opendir(folder);
	if (!dir)
		printf("minishell: cd: %s: No such file or directory", folder);
	else
		//Change the DIR of the structure to this dir.
}
