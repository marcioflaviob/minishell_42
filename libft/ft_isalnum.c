/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:47:39 by trimize           #+#    #+#             */
/*   Updated: 2023/12/08 18:59:29 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// is it alphanumeric ?

/* ft_isalnum:
*	Returns 1 if c is alphanumeric returns 0 otherwise
*/

int	ft_isalnum(int c)
{
	if ((48 <= c && c <= 57) || ((65 <= c && c <= 90) || (97 <= c && c <= 122)))
		return (1);
	return (0);
}
