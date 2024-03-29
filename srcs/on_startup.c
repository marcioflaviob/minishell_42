/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   on_startup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 22:46:03 by trimize           #+#    #+#             */
/*   Updated: 2024/03/29 23:44:35 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_input(void)
{
	char	*buffer;

	while (1)
	{
		buffer = get_next_line(STDIN_FILENO);
		if (buffer[ft_strlen_gnl(buffer) - 1] == '\n')
			break ;
	}
	return (buffer);
}

