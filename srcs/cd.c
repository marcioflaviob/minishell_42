/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 15:26:55 by mbrandao          #+#    #+#             */
/*   Updated: 2024/04/02 00:15:08 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cd(t_sh *sh, char *folder)
{
	int	type;

	type = get_type(folder);
	if (type == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(folder);
		return ;
	}
	else if (type != 1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(folder, 2);
		ft_putstr_fd(": Not a directory", 2);
		return ;
	}
	if (chdir(folder) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(folder);
		return ;
	}
	free(sh->current_dir);
	sh->current_dir = get_cwd();
}
