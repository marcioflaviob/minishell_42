/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:50:07 by trimize           #+#    #+#             */
/*   Updated: 2023/12/08 19:15:04 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* ft_memset:
*	Fills n bytes of the memory area pointed by s with c
*/

void	*ft_memset(void *s, int c, size_t n)
{
	int	i;

	i = 0;
	while (n != 0)
	{
		((unsigned char *)s)[i] = c;
		n--;
		i++;
	}
	return (s);
}
