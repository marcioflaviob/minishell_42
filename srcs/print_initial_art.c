/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_initial_art.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 22:56:21 by mbrandao          #+#    #+#             */
/*   Updated: 2024/03/29 23:16:40 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_minishell_art(void)
{
	int		fd;
	char	*buffer;

	fd = open("../assets/minishell_art", O_RDONLY);
	if (fd == -1)
		return ;
	while (1)
	{
		buffer = get_next_line(fd);
		if (!buffer)
			break ;
		printf("%s\n", buffer);
		free(buffer);
	}
	close(fd);
}
