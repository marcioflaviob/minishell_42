/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 22:51:29 by trimize           #+#    #+#             */
/*   Updated: 2024/05/29 16:25:49 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_signal = 0;

void	var_start(t_sh *sh)
{
	set_env(sh);
	sh->nb_cmd = 0;
	sh->fd_input = -2;
	sh->fd_output = -2;
	sh->last_cmd_st = 0;
	sh->wrong_file = NULL;
	sh->refresh = 0;
	sh->inside_par = 0;
	sh->pipe_par_bool = 0;
	sh->out_par = 0;
	sh->bool_result = 1;
	sh->op_pipe = 0;
	sh->pid = (pid_t *)malloc(sizeof(pid_t));
	sh->true_stdin = dup(STDIN_FILENO);
	sh->true_stdout = dup(STDOUT_FILENO);
}

int	main(void)
{
	t_sh	shell;

	var_start(&shell);
	shell.current_dir = get_cwd();
	if (!shell.current_dir)
		return (0);
	shell.emoji_path = ft_strjoin(shell.current_dir, "/assets/emojis");
	(print_minishell_art(), signal_initializer());
	get_input(&shell);
	free(shell.current_dir);
	return (0);
}

//int	main(void)
//{
//	t_sh	shell;
//	int		permission_fd;
//	char	*buffer;

//	var_start(&shell);
//	permission_fd = open("./assets/permission", O_RDWR);
//	if (permission_fd == -1)
//		(write(2, "Failed opening permission file", 30));
//	else
//	{
//		buffer = get_next_line(permission_fd, 0);
//		if (buffer[15] == '1')
//			new_terminal(&shell, buffer);
//		else
//		{
//			shell.current_dir = get_cwd();
//			if (!shell.current_dir)
//				return (0);
//			shell.emoji_path = ft_strjoin(shell.current_dir, "/assets/emojis");
//			(print_minishell_art(), free(buffer), signal_initializer());
//			get_input(&shell);
//			free(shell.current_dir);
//		}
//	}
//	return (0);
//}
