/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:40:25 by trimize           #+#    #+#             */
/*   Updated: 2023/12/08 19:05:40 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* ft_lstclear:
*	Deletes and frees every nodes of lst, lst is set to NULL
*/

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	if (lst && *lst && del)
	{
		(ft_lstclear(&(*lst)->next, del), ft_lstdelone(*lst, del));
		*lst = 0;
	}
}
