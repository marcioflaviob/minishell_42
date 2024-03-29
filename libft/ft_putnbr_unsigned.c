/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:19:12 by trimize           #+#    #+#             */
/*   Updated: 2023/12/08 19:19:06 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* ft_putnbr_unsigned:
*	Prints an unsigned int, returns the number of printed characters
*/

int	ft_putnbr_unsigned(unsigned int n)
{
	int		i;
	int		y;
	int		nb;
	char	tmp;
	char	res[11];

	i = 0;
	if (n == 0)
		return (ft_putchar('0'), 1);
	ft_bzero(res, 11);
	while (n > 0)
	{
		res[i++] = n % 10 + 48;
		n = n / 10;
	}
	y = 0;
	nb = i;
	while (y < nb / 2)
	{
		tmp = res[y];
		res[y] = res[nb - y - 1];
		res[nb - y - 1] = tmp;
		y++;
	}
	return (ft_putstr(res), i);
}
