/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_equalstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:15:39 by trimize           #+#    #+#             */
/*   Updated: 2024/04/07 16:24:39 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

/*
	Returns 1 if the strings are equal, 0 otherwise
*/

int	ft_equalstr(char const *str, char const *str2)
{
	int	i;

	i = 0;
	if (!str || !str2)
		return (0);
	while (str[i] && str2[i])
	{
		if (str[i] != str2[i])
			return (0);
		i++;
	}
	if (!str[i] && !str2[i])
		return (1);
	return (0);
}
