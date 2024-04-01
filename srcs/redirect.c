/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 14:26:14 by mbrandao          #+#    #+#             */
/*   Updated: 2024/04/01 17:59:07 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redir_out_trunc(char *content, char *outfile)
{
	int	fd;

	fd = open(outfile, O_WRONLY | O_TRUNC);
	if (fd == -1)
	{
		printf("Couldn't open file.");
		return ;
	}
	write(fd, content, ft_strlen(content));
}

void	redir_out_app(char *content, char *outfile)
{
	int	fd;

	fd = open(outfile, O_WRONLY | O_APPEND);
	if (fd == -1)
	{
		printf("Couldn't open file.");
		return ;
	}
	write(fd, content, ft_strlen(content));
}

char	*redir_in(char *infile)
{
	int		fd;
	char	*buffer;
	char	*content;

	fd = open(infile, O_RDONLY);
	if (fd == -1)
	{
		perror("minishell");
		return (NULL);
	}
	content = (char *) malloc(sizeof(char));
	content[0] = 0;
	while (1)
	{
		buffer = get_next_line(fd);
		if (!buffer)
		{
			(free(buffer), close(fd));
			break ;
		}
		content = ft_strjoin_gnl(content, buffer);
		free(buffer);
	}
	close(fd);
	return (content);
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
