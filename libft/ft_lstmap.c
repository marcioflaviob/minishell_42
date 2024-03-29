/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 18:09:54 by trimize           #+#    #+#             */
/*   Updated: 2023/12/08 19:09:09 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* ft_lstmap:
*	Applies a function to every node of a list and creates a new
*	list resulting of these successive applications
*/

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;

	res = 0;
	while (lst)
	{
		ft_lstadd_back(&res, ft_lstnew(f(lst->content)));
		if (!res)
			return (ft_lstclear(&res, del), NULL);
		lst = lst->next;
	}
	return (res);
}
