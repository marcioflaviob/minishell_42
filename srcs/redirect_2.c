/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 18:41:50 by mbrandao          #+#    #+#             */
/*   Updated: 2024/04/28 19:04:55 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redir_help(char *buffer, char *content)
{
	free(content);
	free(buffer);
	clean_gnl(STDIN_FILENO);
	ft_putstr_fd("^C\n", 1);
	term_reset();
}

void	redir_help2(int line, char *delimiter, char *content)
{
	char	*tmp;

	clean_gnl(STDIN_FILENO);
	ft_putstr_fd("minishell: warning: here-document at line ", 2);
	tmp = ft_itoa(line);
	ft_putstr_fd(tmp, 2);
	free (tmp);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putstr_fd("\')\n", 2);
	free(content);
}

void	redir_init(char **content, int *line)
{
	term_config();
	*content = (char *) malloc(sizeof(char));
	if (!*content)
		(ft_putstr_fd("Malloc error redirect here_doc\n", 2),
			exit(EXIT_FAILURE));
	*content[0] = 0;
	*line = 1;
}

char	*redir_in_heredoc(char *delimiter)
{
	char	*buffer;
	char	*content;
	int		line;

	redir_init(&content, &line);
	while (1)
	{
		buffer = get_next_line(STDIN_FILENO, 0);
		if (g_signal)
			return (redir_help(buffer, content), NULL);
		if (!buffer)
			return (redir_help2(line, delimiter, content), NULL);
		if (ft_strncmp(buffer, delimiter, ft_strlen(delimiter)) == 0
			&& buffer[ft_strlen(delimiter)] == '\n')
		{
			free(buffer);
			break ;
		}
		content = ft_strjoin_gnl(content, buffer);
		(free(buffer), line++);
	}
	return (term_reset(), content);
}
