/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 14:26:14 by mbrandao          #+#    #+#             */
/*   Updated: 2024/04/02 20:57:10 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redir_out_trunc(int first, char *outfile)
{
	int		fd;
	char	*buffer;

	fd = open(outfile, O_WRONLY | O_TRUNC);
	if (fd == -1)
	{
		printf("Couldn't open file.");
		return ;
	}
	dup2(STDOUT_FILENO, fd);
	if (first)
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
	close(fd);
}

void	redir_out_app(int first, char *outfile)
{
	int		fd;
	char	*buffer;

	fd = open(outfile, O_WRONLY | O_APPEND);
	if (fd == -1)
	{
		printf("Couldn't open file.");
		return ;
	}
	dup2(STDOUT_FILENO, fd);
	if (first)
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
	close(fd);
}

char	*redir_in(char *infile, char **args)
{
	int		fd;

	fd = open(infile, O_RDONLY);
	if (fd == -1 && args[2])
		return (infile);
	else if (fd == -1 && !args[2])
		return (perror("minishell"), NULL);
	dup2(STDIN_FILENO, fd);
	close(fd);
	return (NULL);
}

char	*redir_in_heredoc(int fd, char *delimiter)
{
	char	*buffer;
	char	*content;

	content = (char *) malloc(sizeof(char));
	content[0] = 0;
	while (1)
	{
		buffer = get_next_line(fd);
		if (ft_equalstr(buffer, delimiter))
		{
			free(buffer);
			break ;
		}
		content = ft_strjoin_gnl(content, buffer);
		free(buffer);
	}
	close(fd);
	return (content);
}
