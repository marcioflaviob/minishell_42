/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 18:16:49 by trimize           #+#    #+#             */
/*   Updated: 2024/05/06 17:28:21 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	new_terminal(t_sh *shell, char *buffer)
{
	pid_t	pid;
	int		perm_fd;

	shell->term_command = (char **)malloc(6 * sizeof(char *));
	if (!shell->term_command)
		(ft_putstr_fd("Malloc error new terminal\n", 2), exit(EXIT_FAILURE));
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
			perm_fd = open("./assets/permission", O_RDWR | O_TRUNC);
			(write(perm_fd, "open_terminal =0", 16), close(perm_fd));
			execve("/usr/bin/gnome-terminal", shell->term_command, shell->env);
			(free(shell->env), free(shell->term_command));
		}
		exit(0);
	}
	return ;
}
