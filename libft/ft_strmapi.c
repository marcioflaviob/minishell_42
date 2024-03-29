/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:53:38 by trimize           #+#    #+#             */
/*   Updated: 2023/12/08 19:27:51 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* ft_strmapi:
*	Applies f to each char of s, i is the first argument of f
*	allocates another char * resulting from these successive applications
*/

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*map;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	map = (char *)malloc(i + 1 * sizeof(char));
	if (!map)
		return (0);
	i = 0;
	while (s[i])
	{
		map[i] = f(i, s[i]);
		i++;
	}
	map[i] = 0;
	return (map);
}
