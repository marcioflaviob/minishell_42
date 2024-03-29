/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:08:09 by trimize           #+#    #+#             */
/*   Updated: 2023/12/08 19:32:53 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ft_tolower:
*	Returns c to it's lowercase equivalent
*/

int	ft_tolower(int c)
{
	if (65 <= c && c <= 90)
		return (c + 32);
	else
		return (c);
}
