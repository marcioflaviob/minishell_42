/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:53:04 by trimize           #+#    #+#             */
/*   Updated: 2023/12/08 19:04:05 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* ft_lstadd_back:
*	Adds the node new to the end of the list lst
*/

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (!ft_lstlast(*lst))
		*lst = new;
	else
		ft_lstlast(*lst)->next = new;
}
