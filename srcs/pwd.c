/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:17:31 by mbrandao          #+#    #+#             */
/*   Updated: 2024/03/30 17:50:19 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pwd(void)
{
	char	*dir;

	dir = get_cwd();
	if (!dir)
		return ;
	printf("%s\n", dir);
}

char	*get_cwd(void)
{
	char	*buffer;

	buffer = (char *) malloc(1024 * sizeof(char));
	if (!buffer)
		return (NULL);
	if (getcwd(buffer, 1024) != NULL)
		return (buffer);
	else
	{
		free(buffer);
		return (NULL);
	}
}
