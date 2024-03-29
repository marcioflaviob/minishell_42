/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:33:29 by trimize           #+#    #+#             */
/*   Updated: 2023/12/08 19:14:13 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* ft_memmove:
*	copies n bytes from memory area src to dest, works around overlapping
*/

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*tmp;
	char		*tmp2;
	size_t		i;

	i = 0;
	tmp = (char *)dest;
	tmp2 = (char *)src;
	if (!dest && !src)
		return (0);
	if (tmp > tmp2)
	{
		while (n-- > 0)
			tmp[n] = tmp2[n];
	}
	else
	{
		while (i < n)
		{
			tmp[i] = tmp2[i];
			i++;
		}
	}
	return (dest);
}
