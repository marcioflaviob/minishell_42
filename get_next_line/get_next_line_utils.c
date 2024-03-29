/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 22:26:39 by mbrandao          #+#    #+#             */
/*   Updated: 2024/02/24 19:43:22 by mbrandao         ###   ########.fr       */
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

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	initialize(int *i, int *j)
{
	*i = 0;
	*j = 0;
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*result;

	initialize(&i, &j);
	if (!s1)
	{
		s1 = malloc (1 * sizeof(char));
		if (!s1)
			return (NULL);
		s1[0] = 0;
	}
	result = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	while (s2[j])
		result[i++] = s2[j++];
	result[i] = 0;
	free(s1);
	return (result);
}

char	*line_dealer(char *updated)
{
	int		i;
	int		j;
	int		size;
	char	*line;

	initialize(&i, &j);
	size = ft_strlen(updated);
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
