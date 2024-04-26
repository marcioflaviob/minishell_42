/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:43:44 by mbrandao          #+#    #+#             */
/*   Updated: 2024/02/24 20:31:16 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
// #include "get_next_line_utils.c"

char	*helper_ft(int fd, char *updated)
{
	int		char_num;
	char	*previous;

	char_num = 1;
	previous = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!previous)
		return (NULL);
	while (!has_end(updated) && char_num != 0)
	{
		char_num = read(fd, previous, BUFFER_SIZE);
		if (char_num == -1)
		{
			free(previous);
			return (NULL);
		}
		previous[char_num] = 0;
		updated = ft_strjoin_gnl(updated, previous);
	}
	free(previous);
	return (updated);
}

char	*get_next_line(int fd)
{
	static char	*updated[4096];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	updated[fd] = helper_ft(fd, updated[fd]);
	if (!updated[fd] || updated[fd][0] == 0)
	{
		free(updated[fd]);
		updated[fd] = NULL;
		return (NULL);
	}
	line = line_dealer(updated[fd]);
	if (updated[fd])
	{
		if (updated[fd][0] == 0)
		{
			free (updated[fd]);
			updated[fd] = NULL;
		}
	}
	return (line);
}
/*
int main() {
	int fd = open("poem.txt", O_RDONLY);
	int fd2 = open("poem2.txt", O_RDONLY);

	char *line1 = get_next_line(fd);
	char *ligne1 = get_next_line(fd2);
	char *line2 = get_next_line(fd);
	char *ligne2 = get_next_line(fd2);
	char *line3 = get_next_line(fd);
	char *ligne3 = get_next_line(fd2);
	char *ligne4 = get_next_line(fd2);
	char *line4 = get_next_line(fd);

	
	printf("%s", line1);
	printf("%s", line2);
	printf("%s", line3);
	printf("%s", line4);

	printf("%s", ligne1);
	printf("%s", ligne2);
	printf("%s", ligne3);
	printf("%s", ligne4);
	
	free(line1);
	free(line2);
	free(line3);
	free(line4);
	
	free(ligne1);
	free(ligne2);
	free(ligne3);
	free(ligne4);

	close (fd);
	close (fd2);
}
*/
