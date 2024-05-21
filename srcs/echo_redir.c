/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:16:05 by mbrandao          #+#    #+#             */
/*   Updated: 2024/05/21 14:37:43 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redirect_2(t_sh *sh, t_redir *redir, char **args)
{
	if (args[redir->y] && ft_equalstr(args[redir->y], "<"))
	{
		redir->i += find_sp(&args[redir->i], sh) + 1;
		redir->fd_input = open(args[redir->i], O_RDONLY);
		if (redir->fd_input == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(args[redir->i], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			redir->error_in = 0;
		}
	}
	if (args[redir->y] && ft_equalstr(args[redir->y], ">"))
	{
		redir->i += find_sp(&args[redir->i], sh) + 1;
		redir->fd_output = open(args[redir->i],
				O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (redir->fd_output == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(args[redir->i], 2);
			ft_putstr_fd(": Permission denied\n", 2);
			redir->error_out = 0;
		}
	}
}

void	redirect_3(t_sh *sh, t_redir *redir, char **args)
{
	if (args[redir->y] && ft_equalstr(args[redir->y], ">>"))
	{
		redir->i += find_sp(&args[redir->i], sh) + 1;
		redir->fd_output = open(args[redir->i],
				O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (redir->fd_output == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(args[redir->i], 2);
			ft_putstr_fd(": Permission denied\n", 2);
			redir->error_out = 0;
		}
	}
	sh->position += redir->i - redir->tmp;
	redir->y = find_sp(&args[redir->i], sh) + redir->i;
}

void	redirect_init(t_redir *redir, char **args, t_sh *sh)
{
	redir->fd_output = 0;
	redir->fd_input = 0;
	redir->i = 0;
	redir->error_in = 1;
	redir->error_out = 1;
	redir->y = find_sp(&args[redir->i], sh);
}

int	redirect(t_sh *sh, char **args)
{
	t_redir	redir;

	redirect_init(&redir, args, sh);
	while (ft_equalstr(args[redir.y], "<")
		|| ft_equalstr(args[redir.y], ">") || ft_equalstr(args[redir.y], ">>"))
	{
		redir.tmp = redir.i;
		redirect_2(sh, &redir, args);
		redirect_3(sh, &redir, args);
	}
	if (args[redir.y]
		&& ft_equalstr(args[redir.y], "|") && !redir.fd_output)
		(dup2(sh->pipe[1], STDOUT_FILENO), close(sh->pipe[1]),
			sh->position += find_sp_echo(&sh->args[sh->position], sh));
	else if (args[redir.y]
		&& ft_equalstr(args[redir.y], "|") && redir.fd_output)
		sh->position += find_sp_echo(&sh->args[sh->position], sh);
	if (!redir.error_in || !redir.error_out)
		return (0);
	if (redir.fd_output && redir.fd_output != -1)
		(dup2(redir.fd_output, STDOUT_FILENO), close(redir.fd_output), close(sh->pipe[1]));
	if (redir.fd_input && redir.fd_input != -1)
		(dup2(redir.fd_input, STDIN_FILENO), close(redir.fd_input));
	return (1);
}
