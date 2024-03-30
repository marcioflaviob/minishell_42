/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   on_startup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 22:46:03 by trimize           #+#    #+#             */
/*   Updated: 2024/03/30 13:57:56 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_input(void)
{
	char	*buffer;

	while (1)
	{
		buffer = readline(">> ");
		if (buffer) 
		{
			printf("Command received: %s\n", buffer);
			if (buffer[0] != '\0')
				add_history(buffer);
		}
	}
	return (buffer);
}

