/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:31:46 by trimize           #+#    #+#             */
/*   Updated: 2023/12/08 19:23:22 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//splits a char * by a delimiter c into multiple char * in a char **

/* ft_split:
*	Splits a char * by a delimiter c into multiple char * in a char **
*	returns the char ** created
*/

static int	wordcount(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != '\0')
			count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}

void	freesplit(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

static int	getlenword(int start, const char *s, char c)
{
	int	i;
	int	len;

	i = start;
	while (s[i] && s[i] != c)
		i++;
	len = i - start;
	return (len);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		y;
	int		x;
	char	**str;

	i = 0;
	y = 0;
	if (!s)
		return (0);
	str = (char **)malloc((wordcount(s, c) + 1) * sizeof(char *));
	if (!str)
		return (0);
	while (i < wordcount(s, c))
	{
		x = 0;
		while (s[y] == c && s[y])
			y++;
		str[i] = (char *)malloc((getlenword(y, s, c) + 1) * sizeof(char));
		if (!str[i])
			return (str[i] = 0, freesplit(str), NULL);
		while (s[y] != c && s[y])
			str[i][x++] = s[y++];
		str[i++][x] = 0;
	}
	return (str[i] = 0, str);
}
