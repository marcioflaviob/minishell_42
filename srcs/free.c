/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:19:22 by trimize           #+#    #+#             */
/*   Updated: 2024/05/15 15:51:56 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	freetab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	child_free(t_sh *sh)
{
	freetab(sh->env);
	free(sh->current_dir);
	freetab(sh->variables);
	freetab(sh->args);
	free(sh->sp_bool);
	free(sh->emoji_path);
}
