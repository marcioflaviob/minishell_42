/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:36:09 by trimize           #+#    #+#             */
/*   Updated: 2023/12/08 19:13:32 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* ft_memcpy:
*	Copies n bytes from memory area src to memory area dest,
*	memory may overlapp and have undefined behavior
*/

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	int		i;

	i = 0;
	if (!dest && !src)
		return (dest);
	while (i < (int)n)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	return (dest);
}
