/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   on_startup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 22:46:03 by trimize           #+#    #+#             */
/*   Updated: 2024/03/30 17:06:53 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_input(void)
{
	int		random;
	char	*random_line;
	char	*buffer;

	random = get_random_number();
	random_line = get_a_line("./assets/emojis", random);
	buffer = readline(random_line);
	if (buffer || buffer[0])
		add_history(buffer);
	free(random_line);
	return (buffer);
}

char	*get_a_line(char *filename, int line_number)
{
	int		fd;
	int		i;
	int		current_line_number;
	char	*line;

	current_line_number = 0;
	i = -1;
	fd = open(filename, O_RDONLY);
	if (line_number > 128)
		line_number = 128;
	if (fd == -1)
		return (perror("Error opening file"), NULL);
	while (current_line_number != line_number)
	{
		line = get_next_line(fd);
		line[ft_strlen_gnl(line) - 1] = 0;
		current_line_number++;
		if (current_line_number != line_number)
			free(line);
	}
	close(fd);
	return (line);
}

int	get_random_number(void)
{
	int		fd_random;
	char	random;

	fd_random = open("/dev/random", O_RDONLY);
	if (fd_random == -1)
		return (printf("Couldn't open /dev/random\n"), 50);
	read(fd_random, &random, 1);
	close(fd_random);
	if (random < 0)
		random *= -1;
	random = random % 127;
	if (random <= 0)
		random = 1;
	return (random);
}
