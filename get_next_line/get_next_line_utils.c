/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:57:13 by trimize           #+#    #+#             */
/*   Updated: 2024/05/13 19:27:12 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr_tgnl(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((unsigned char)c == 0)
		return ((char *)&s[i]);
	else
		return (0);
}

int	ft_strlen_tgnl(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin_tgnl(char *s1, char *s2)
{
	int		i;
	int		y;
	char	*cat;

	i = 0;
	y = 0;
	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		if (!s1)
			return (0);
		s1[0] = 0;
	}
	cat = (char *)malloc(((ft_strlen_tgnl(s1)
					+ ft_strlen_tgnl(s2)) + 1) * sizeof(char));
	if (!cat)
		return (0);
	while (s1[i])
	{
		cat[i] = s1[i];
		i++;
	}
	while (s2[y])
		cat[i++] = s2[y++];
	return (cat[i] = 0, free(s1), cat);
}
