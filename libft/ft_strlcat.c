/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teorimize <teorimize@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:53:23 by trimize           #+#    #+#             */
/*   Updated: 2023/12/22 17:32:55 by teorimize        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* ft_strlcat:
*	Adds src to dest with a final size in argument
*	len(src) + len(dest) is returned if size > len(dest)
*	otherwise, len(src) + size is returned
*/

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	lengdest;
	unsigned int	lengsrc;

	i = 0;
	lengsrc = ft_strlen(src);
	if (!dest && size == 0)
		return (lengsrc + 1);
	lengdest = ft_strlen(dest);
	if ((unsigned int)size <= lengdest)
		return (lengsrc + size);
	while ((i < (unsigned int)size - lengdest - 1) && src[i] != '\0')
	{
		dest[lengdest + i] = src[i];
		i++;
	}
	dest[lengdest + i] = '\0';
	return (lengsrc + lengdest);
}
