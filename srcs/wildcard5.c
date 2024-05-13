/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:12:49 by mbrandao          #+#    #+#             */
/*   Updated: 2024/05/13 16:40:36 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	init_wc(t_sh *sh, t_segcheck *c)
{
	c->pos = ft_tabchr(sh->args, '*');
	if (c->pos == -1)
		return (1);
	pipe(c->fd);
	c->char_pos = ft_int_strchr(sh->args[c->pos], '*');
	c->buffer = ft_strdup("");
	c->cmd = malloc(2 * sizeof(char *));
	if (!c->cmd)
		(ft_putstr_fd("Malloc error ls in wildcard", 2), exit(EXIT_FAILURE));
	c->cmd[0] = find_path("ls", sh);
	c->cmd[1] = NULL;
	return (0);
}

void	wc_while(t_sh *sh, t_segcheck *c)
{
	while (is_quoted(sh->args[c->pos], c->char_pos) && c->char_pos != -1)
	{
		if (ft_int_strchr(sh->args[c->pos] + (c->char_pos + 1), '*') == -1)
			c->char_pos = -1;
		else
			c->char_pos += ft_int_strchr(sh->args[c->pos]
					+ (c->char_pos + 1), '*') + 1;
	}
}

void	wc_else(t_sh *sh, t_segcheck *c)
{
	waitpid(c->pid, NULL, 0);
	close(c->fd[1]);
	while (1)
	{
		c->tmp = get_next_line(c->fd[0], 0);
		if (!c->tmp)
			break ;
		c->buffer = ft_strjoin_gnl(c->buffer, c->tmp);
		free(c->tmp);
	}
	close(c->fd[0]);
	c->result = ft_split(c->buffer, '\n');
	free(c->buffer);
	segment_fill(&(c->wc), sh->args[c->pos]);
	wildcard_finder(&(c->result), c->wc);
	remove_from_tab(&sh->args, c->pos);
	c->i = 0;
	while (c->result[c->i])
	{
		c->result[c->i] = ft_stradd(c->result[c->i], 0, "'");
		c->result[c->i] = ft_stradd(c->result[c->i],
				ft_strlen_gnl(c->result[c->i]), "'");
		add_to_tab_pos(&sh->args, c->result[c->i++], c->pos);
	}
}

int	wildcard(t_sh *sh)
{
	t_segcheck	c;

	if (init_wc(sh, &c))
		return (0);
	wc_while(sh, &c);
	if (c.pos != -1 && c.char_pos != -1
		&& !is_quoted(sh->args[c.pos], c.char_pos))
	{
		c.pid = fork();
		if (c.pid == 0)
		{
			dup2(c.fd[1], 1);
			close(c.fd[0]);
			close(c.fd[1]);
			execve(c.cmd[0], c.cmd, sh->env);
			return (1);
		}
		else
			return (wc_else(sh, &c), 1);
	}
	else
		return (0);
}
