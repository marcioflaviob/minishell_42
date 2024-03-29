/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 21:46:03 by mbrandao          #+#    #+#             */
/*   Updated: 2024/03/29 23:37:35 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char	*updated;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	updated = helper_ft(fd, updated);
	if (!updated || updated[0] == 0)
	{
		free(updated);
		updated = NULL;
		return (NULL);
	}
	line = line_dealer(updated);
	if (updated)
	{
		if (updated[0] == 0)
		{
			free (updated);
			updated = NULL;
		}
	}
	return (line);
}
