/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:57:13 by trimize           #+#    #+#             */
/*   Updated: 2023/12/08 18:59:14 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ft_isascii:
*	Returns 1 if c is part of the ascii table
*	returns 0 otherwise
*/

int	ft_isascii(int c)
{
	if ((0 <= c && c <= 127))
		return (1);
	return (0);
}
