/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 15:26:55 by mbrandao          #+#    #+#             */
/*   Updated: 2024/04/22 18:02:22 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cd(t_sh *sh, char *folder)
{
	int	type;

	type = get_type(folder);
	if (type == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		(perror(folder));
		return (0);
	}
	else if (type != 1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(folder, 2);
		(ft_putstr_fd(": Not a directory", 2));
		return (0);
	}
	if (chdir(folder) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		(perror(folder));
		return (0);
	}
	free(sh->current_dir);
	sh->current_dir = get_cwd();
	return (1);
}
