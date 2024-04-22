/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 14:26:14 by mbrandao          #+#    #+#             */
/*   Updated: 2024/04/22 22:30:08 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redir_out_trunc_p(char *outfile, char **args, t_sh *sh)
{
	char	*buffer;

	sh->fd_output = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (sh->fd_output == -1)
	{
		printf("Couldn't open file.");
		return ;
	}
	dup2(sh->fd_output, STDOUT_FILENO);
	if (!args[2])
	{
		while (1)
		{
			buffer = get_next_line(STDIN_FILENO);
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
		printf("Couldn't open file.");
		return ;
	}
	dup2(sh->fd_output, STDOUT_FILENO);
	if (!args[1])
	{
		while (1)
		{
			buffer = get_next_line(STDIN_FILENO);
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
		printf("Couldn't open file.");
		return ;
	}
	dup2(sh->fd_output, STDOUT_FILENO);
	if (!args[1])
	{
		while (1)
		{
			buffer = get_next_line(STDIN_FILENO);
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
		printf("Couldn't open file.");
		return ;
	}
	dup2(sh->fd_output, STDOUT_FILENO);
	if (!args[2])
	{
		while (1)
		{
			buffer = get_next_line(STDIN_FILENO);
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
	int		line;

	term_config();
	content = (char *) malloc(sizeof(char));
	content[0] = 0;
	line = 1;
	while (1)
	{
		buffer = get_next_line(STDIN_FILENO);
		if (g_signal)
		{
			free(buffer);
			printf("^C\n");
			term_reset();
			return (NULL);
		}
		if (!buffer)
		{
			printf("minishell: warning: here-document at line %d delimited by end-of-file (wanted `%s')\n", line, delimiter);
			break ;
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
