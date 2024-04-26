/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 14:26:14 by mbrandao          #+#    #+#             */
/*   Updated: 2024/04/26 21:42:55 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redir_out_trunc_p(char *outfile, char **args, t_sh *sh)
{
	char	*buffer;

	sh->fd_output = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (sh->fd_output == -1)
	{
		ft_putstr_fd("Couldn't open file\n", 2);
		return ;
	}
	dup2(sh->fd_output, STDOUT_FILENO);
	if (!args[2])
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

void	redir_out_trunc(char *outfile, char **args, t_sh *sh)
{
	char	*buffer;

	sh->fd_output = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
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
	char	*buffer;

	sh->fd_output = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (sh->fd_output == -1)
	{
		ft_putstr_fd("Couldn't open file\n", 2);
		return ;
	}
	dup2(sh->fd_output, STDOUT_FILENO);
	if (!args[2])
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

void	redir_in(char *infile, char **args, t_sh *sh)
{
	sh->fd_input = open(infile, O_RDONLY);
	if (sh->fd_input == -1 && args[2])
	{
		sh->wrong_file = ft_strdup(infile);
		return ;
	}
	else if (sh->fd_input == -1 && !args[2])
		return (perror("minishell"));
	else
		dup2(sh->fd_input, STDIN_FILENO);
	return ;
}

char	*redir_in_heredoc(char *delimiter)
{
	char	*buffer;
	char	*content;
	char	*tmp;
	int		line;

	term_config();
	content = (char *) malloc(sizeof(char));
	if (!content)
		(ft_putstr_fd("Malloc error redirect here_doc\n", 2), exit(EXIT_FAILURE));
	content[0] = 0;
	line = 1;
	while (1)
	{
		buffer = get_next_line(STDIN_FILENO, 0);
		if (g_signal)
		{
			free(content);
			free(buffer);
			get_next_line(STDIN_FILENO, 1);
			ft_putstr_fd("^C\n", 1);
			term_reset();
			return (NULL);
		}
		if (!buffer)
		{
			get_next_line(STDIN_FILENO, 1);
			ft_putstr_fd("minishell: warning: here-document at line ", 2);
			tmp = ft_itoa(line);
			ft_putstr_fd(tmp, 2);
			free (tmp);
			ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
			ft_putstr_fd(delimiter, 2);
			ft_putstr_fd("\')\n", 2);
			free(content);
			return (NULL);
		}
		if (ft_strncmp(buffer, delimiter, ft_strlen(delimiter)) == 0 && buffer[ft_strlen(delimiter)] == '\n')
		{
			free(buffer);
			break ;
		}
		content = ft_strjoin_gnl(content, buffer);
		free(buffer);
		line++;
	}
	term_reset();
	return (content);
}
