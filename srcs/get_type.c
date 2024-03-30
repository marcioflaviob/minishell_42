/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 19:11:54 by mbrandao          #+#    #+#             */
/*   Updated: 2024/03/30 23:14:45 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// This function gets the type of what was passed as a path,
// returns 0 for files, 1 for directories and 2 for other files.

int	get_type(char *path)
{
	struct stat	st;

	if (stat(path, &st) == 0)
	{
		if (S_ISREG(st.st_mode))
			return (0);
		else if (S_ISDIR(st.st_mode))
			return (1);
		else
			return (2);
	}
	else
		return (-1);
}
