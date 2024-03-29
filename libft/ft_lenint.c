/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lenint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:21:42 by trimize           #+#    #+#             */
/*   Updated: 2023/12/08 19:03:02 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ft_lenint:
*	Returns the number of digits in an int, if n < 0
*	the minus is included
*/

int	ft_lenint(int n)
{
	int	i;

	i = 0;
	if (n < 0)
		i++;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}
