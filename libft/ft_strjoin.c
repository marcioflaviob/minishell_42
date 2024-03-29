/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:59:15 by trimize           #+#    #+#             */
/*   Updated: 2023/12/08 19:24:38 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* ft_strjoin:
*	Allocates and returns a new string wich is s1 + s2
*/

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		y;
	char	*cat;

	i = 0;
	y = 0;
	if (!s1)
		return (0);
	while (s1[i])
		i++;
	while (s2[y])
		y++;
	cat = (char *)malloc((i + y) + 1 * sizeof(char));
	if (!cat)
		return (0);
	i = 0;
	while (s1[i])
	{
		cat[i] = s1[i];
		i++;
	}
	y = 0;
	while (s2[y])
		cat[i++] = s2[y++];
	return (cat[i] = 0, cat);
}
