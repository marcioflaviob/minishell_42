/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:48:18 by trimize           #+#    #+#             */
/*   Updated: 2024/03/16 13:10:11 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_exit(t_tmp *tmp, int finish)
{
	freetab(tmp->env);
	free(tmp->pid);
	if (tmp->fd_input != -1)
		close(tmp->fd_input);
	if (tmp->fd_output != -1)
		close(tmp->fd_output);
	if (tmp->fd_error != -1)
		close(tmp->fd_error);
	if (finish == 1)
		exit(EXIT_SUCCESS);
	else if (finish == 0)
	{
		freetab(tmp->cmd);
		exit(EXIT_FAILURE);
	}	
}

void	free_exit_main(t_tmp *tmp)
{
	freetab(tmp->env);
	free(tmp->pid);
	if (tmp->fd_input != -1)
		close(tmp->fd_input);
	if (tmp->fd_output != -1)
		close(tmp->fd_output);
	if (tmp->fd_error != -1)
		close(tmp->fd_error);
}

void	free_here_doc(t_tmp *tmp)
{
	free(tmp->buffer);
	exit(EXIT_FAILURE);
}
