/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_initial_art.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 22:56:21 by mbrandao          #+#    #+#             */
/*   Updated: 2024/04/28 19:03:57 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_minishell_art(void)
{
	int		fd;
	int		i;
	char	*buffer;
	char	**colors;

	i = 0;
	colors = (char **)malloc(8 * sizeof(char *));
	if (!colors)
		(ft_putstr_fd("Malloc error minishell art\n", 2), exit(1));
	fill_color(colors);
	fd = open("./assets/minishell_art", O_RDONLY);
	if (fd == -1)
		return ;
	while (1)
	{
		buffer = get_next_line(fd, 0);
		if (!buffer)
			break ;
		write(STDOUT_FILENO, colors[i], ft_strlen_gnl(colors[i]));
		write(1, buffer, ft_strlen_gnl(buffer));
		write(STDOUT_FILENO, RESET, sizeof(RESET) - 1);
		i++;
		free(buffer);
	}
	(freetab(colors), write(1, "\n\n\n", 3), close(fd));
}

void	fill_color(char **color)
{
	color[0] = ft_strdup(RED);
	color[1] = ft_strdup(RED);
	color[2] = ft_strdup(ORANGE);
	color[3] = ft_strdup(YELLOW);
	color[4] = ft_strdup(GREEN);
	color[5] = ft_strdup(BLUE);
	color[6] = ft_strdup(INDIGO);
	color[7] = NULL;
}
