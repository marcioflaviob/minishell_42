/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:08:39 by trimize           #+#    #+#             */
/*   Updated: 2023/12/08 18:59:17 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ft_isalpha:
*	Returns 1 if c is a letter, 0 otherwise
*/

int	ft_isalpha(int c)
{
	if ((65 <= c && c <= 90) || (97 <= c && c <= 122))
		return (1);
	return (0);
}
