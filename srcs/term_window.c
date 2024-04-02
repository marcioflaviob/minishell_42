/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 18:16:49 by trimize           #+#    #+#             */
/*   Updated: 2024/04/02 11:27:29 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	new_terminal(t_sh *shell, char *buffer)
{
	pid_t	pid;
	int		permission_fd;

	shell->term_command = (char **)malloc(6 * sizeof(char *));
	shell->term_command[0] = ft_strdup("/usr/bin/gnome-terminal");
	shell->term_command[1] = ft_strdup("--");
	shell->term_command[2] = ft_strdup("bash");
	shell->term_command[3] = ft_strdup("-c");
	shell->term_command[4] = ft_strdup("./minishell");
	shell->term_command[5] = NULL;
	(set_env(shell), pid = fork());
	if (pid == 0)
	{
		if (buffer[15] == '1')
		{
			permission_fd = open("./assets/permission", O_RDWR | O_TRUNC);
			write(permission_fd, "open_terminal =0", 16);
			(close(permission_fd));
			execve("/usr/bin/gnome-terminal", shell->term_command, shell->env);
			(free(shell->env), free(shell->term_command));
		}
		exit(0);
	}
	return ;
}
