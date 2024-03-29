/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 16:25:18 by trimize           #+#    #+#             */
/*   Updated: 2023/12/08 19:06:23 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* ft_lstdelone
*	Deletes and frees the last node of lst
*/

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst && del)
		(del(lst->content), free(lst));
}
