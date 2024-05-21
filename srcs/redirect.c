/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 14:26:14 by mbrandao          #+#    #+#             */
/*   Updated: 2024/05/21 14:46:11 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redir_out_trunc_p(char *outfile, char **args, t_sh *sh)
{
	(void)args;
	sh->fd_output = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (sh->fd_output == -1)
	{
		ft_putstr_fd("Couldn't open file\n", 2);
		return ;
	}
	dup2(sh->fd_output, STDOUT_FILENO);
	close(sh->fd_output);
}

void	redir_out_trunc(char *outfile, char **args, t_sh *sh)
{
	//char	*buffer;
	(void)args;
	sh->fd_output = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (sh->fd_output == -1)
	{
		ft_putstr_fd("Couldn't open file\n", 2);
		return ;
	}
	dup2(sh->fd_output, STDOUT_FILENO);
	//if (!args[1])
	//{
	//	while (1)
	//	{
	//		buffer = get_next_line(STDIN_FILENO, 0);
	//		if (!buffer)
	//			break ;
	//		write(1, buffer, ft_strlen(buffer));
	//		free(buffer);
	//	}
	//}
	close(sh->fd_output);
}

void	redir_out_app(char *outfile, char **args, t_sh *sh)
{
	char	*buffer;

	sh->fd_output = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (sh->fd_output == -1)
	{
		ft_putstr_fd("Couldn't open file\n", 2);
		return ;
	}
	dup2(sh->fd_output, STDOUT_FILENO);
	if (!args[1])
	{
		while (1)
		{
			buffer = get_next_line(STDIN_FILENO, 0);
			if (!buffer)
				break ;
			write(1, buffer, ft_strlen(buffer));
			free(buffer);
		}
	}
	close(sh->fd_output);
}

void	redir_out_app_p(char *outfile, char **args, t_sh *sh)
{
	(void)args;
	sh->fd_output = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (sh->fd_output == -1)
	{
		ft_putstr_fd("Couldn't open file\n", 2);
		return ;
	}
	dup2(sh->fd_output, STDOUT_FILENO);
	close(sh->fd_output);
}

void	redir_in(char *infile, char **args, t_sh *sh)
{
	sh->fd_input = open(infile, O_RDONLY);
	if (sh->fd_input == -1 && args[2])
	{
		sh->wrong_file = ft_strdup(infile);
		return ;
	}
	else if (sh->fd_input == -1 && !args[2])
	{
		sh->last_cmd_st = 1;
		return (perror("minishell"));
	}
	else
		dup2(sh->fd_input, STDIN_FILENO);
	return ;
}
