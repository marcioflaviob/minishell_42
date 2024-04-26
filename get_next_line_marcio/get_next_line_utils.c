/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:43:34 by mbrandao          #+#    #+#             */
/*   Updated: 2024/02/24 16:44:13 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Function that returns 0 if the str doesn't contain the end of line
int	has_end(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (0);
}


char	*line_dealer(char *updated)
{
	int		i;
	int		j;
	int		size;
	char	*line;

	initialize(&i, &j);
	size = ft_strlen_gnl(updated);
	if (has_end(updated))
		size = has_end(updated);
	line = (char *) malloc ((size + 2) * sizeof(char));
	if (!line)
		return (NULL);
	while (updated[i] != '\n' && updated[i])
	{
		line[i] = updated[i];
		i++;
	}
	if (updated[i] == '\n')
		line[i++] = '\n';
	line[i] = 0;
	while (updated[i])
		updated[j++] = updated[i++];
	while (updated[j])
		updated[j++] = 0;
	return (line);
}
