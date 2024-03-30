/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_initial_art.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 22:56:21 by mbrandao          #+#    #+#             */
/*   Updated: 2024/03/30 15:36:18 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_minishell_art(void)
{
	int		fd;
	int		i;
	char	*buffer;
	char	COLORS[20][20] = {RED, RED, ORANGE, YELLOW, GREEN, BLUE, INDIGO};

	i = 0;
	fd = open("./assets/minishell_art", O_RDONLY);
	if (fd == -1)
		return ;
	while (1)
	{
		buffer = get_next_line(fd);
		if (!buffer)
			break ;
		write(STDOUT_FILENO, COLORS[i], ft_strlen_gnl(COLORS[i]));
		write(1, buffer, ft_strlen_gnl(buffer));
		write(STDOUT_FILENO, RESET, sizeof(RESET) - 1);
		i++;
		free(buffer);
	}
	write(1, "\n\n\n", 3);
	close(fd);
}
