/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:04:47 by trimize           #+#    #+#             */
/*   Updated: 2023/12/08 19:29:10 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* ft_strnstr:
*	Returns the pointer to the first occurence of little in big
*/

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < len && big[i])
	{
		while (i + j < len && little[j] && (big[i + j] == little[j]))
			j++;
		if (little[j] == '\0')
			return ((char *)big + i);
		else
		{
			j = 0;
			i++;
		}
	}
	if (little[j] == '\0')
		return ((char *)big + i);
	return (0);
}
