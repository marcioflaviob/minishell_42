/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_initial_art.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 22:56:21 by mbrandao          #+#    #+#             */
/*   Updated: 2024/03/29 23:52:54 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_minishell_art(void)
{
	int		fd;
	char	*buffer;

	fd = open("./assets/minishell_art", O_RDONLY);
	if (fd == -1)
		return ;
	while (1)
	{
		buffer = get_next_line(fd);
		if (!buffer)
			break ;
		write(1, buffer, ft_strlen_gnl(buffer));
		free(buffer);
	}
	write(1, "\n\n\n", 3);
	close(fd);
}
