/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:40:39 by mbrandao          #+#    #+#             */
/*   Updated: 2024/04/23 02:52:06 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_int_strstr_wc(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		while (to_find[j] && (str[i + j] == to_find[j]))
			j++;
		if (to_find[j] == '\0')
			return (i);
		else
		{
			j = 0;
			i++;
		}
	}
	if (to_find[j] == '\0')
		return (i);
	return (-1);
}

char	*ft_strstr_wc(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		while (to_find[j] && (str[i + j] == to_find[j]))
			j++;
		if (to_find[j] == '\0')
			return (str + i);
		else
		{
			j = 0;
			i++;
		}
	}
	if (to_find[j] == '\0')
		return (str + i);
	return (NULL);
}

int	ft_int_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return (i);
		i++;
	}
	if ((unsigned char)c == 0)
		return (i);
	else
		return (-1);
}

void	fill_ba(char **b, char **a, char *input)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	*b = ft_strdup("");
	*a = ft_strdup("");
	while (input[i] != '*')
		*b = ft_strjoin_gnl(*b, &(input[i++]));
	i++;
	while (input[i])
		*a = ft_strjoin_gnl(*a, &(input[i++]));
}

int	ft_tabchr(char **tab, char c)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (ft_strchr(tab[i], c))
			return (i);
		i++;
	}
	return (-1);
}

void	remove_quotes(char **str)
{
	char *src = *str, *dst = *str;
	while (*src) {
		if (*src == '\\' && (*(src + 1) == '\"' || *(src + 1) == '\'')) {
			src++;
		} else if (*src == '\"' || *src == '\'') {
			src++;
			continue;
		}
		*dst++ = *src++;
	}
	*dst = '\0';
}

void wildcard_finder(char ***tab, t_wc *wc) {
	int		i;
	int		j;
	int		pass;
	char	*str;
	char	*current_position;
	char	*found_position;

	i = 0;
	while ((*tab)[i])
	{
		str = (*tab)[i];
		pass = 1;
		current_position = str;
		j = 0;
		while (wc[j].segment) 
		{
			if (wc[j].segment[0] != 0)
			{
				if (wc[j].pos == 0 && ft_strncmp(str, wc[j].segment, ft_strlen(wc[j].segment)) != 0)
				{
					pass = 0;
					break ;
				}
				else if (wc[j].pos == -1)
				{
					found_position = ft_strstr_wc(current_position, wc[j].segment);
					if (found_position == current_position)
						found_position = ft_strstr_wc(current_position + 1, wc[j].segment);
					if (found_position == NULL)
					{
						pass = 0;
						break ;
					}
					else
						current_position = found_position + ft_strlen(wc[j].segment);
				}
				else if (wc[j].pos == 1 && ft_strncmp(str + ft_strlen(str) - ft_strlen(wc[j].segment), wc[j].segment, ft_strlen(wc[j].segment)) != 0)
				{
					pass = 0;
					break ;
				}
			}
			j++;
		}
		if (!pass)
			remove_from_tab(tab, i--);
		i++;
	}
}

int	ft_part_len(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

// pos is defined as the position of the wildcard in the input
// pos is 0 when the wildcard is the first argument
// pos is -1 when the wildcard is in the middle of the arguments
// pos is 1 when the wildcard is the last argument
void segment_fill(t_wc **wc, char *input)
{
	int		i;
	int		j;
	int		x;
	int		seg_count;
	int		in_quotes;
	char	quote_char;

	i = 0;
	j = 0;
	seg_count = 0;
	in_quotes = 0;
	quote_char = '\0';
	while (input[i])
	{
		if (input[i] == '*' && !in_quotes)
			seg_count++;
		else if (input[i] == '"' || input[i] == '\'')
		{
			if (in_quotes && quote_char == input[i])
				in_quotes = 0;
			else if (!in_quotes)
			{
				in_quotes = 1;
				quote_char = input[i];
			}
		}
		i++;
	}
	*wc = malloc((seg_count + 2) * sizeof(t_wc));
	if (!*wc)
		(ft_putstr_fd("Malloc error tab in segment fill", 2), exit(EXIT_FAILURE));
	i = 0;
	j = 0;
	while (input[i])
	{
		if (i == 0 && input[i] != '*')
		{
			x = 0;
			(*wc)[j].segment = malloc (ft_part_len(input, '*') + 1 * sizeof(char));
			if (!((*wc)[j].segment))
				(ft_putstr_fd("Malloc error segment in segment fill", 2), free(*wc) ,exit(EXIT_FAILURE));
			while (input[i] && (input[i] != '*' || in_quotes))
			{
				if (input[i] == '"' || input[i] == '\'')
				{
					if (in_quotes && quote_char == input[i])
						in_quotes = 0;
					else if (!in_quotes)
					{
						in_quotes = 1;
						quote_char = input[i];
					}
				}
				(*wc)[j].segment[x++] = input[i++];
				(*wc)[j].pos = 0;
			}
			(*wc)[j].segment[x] = '\0';
			quotes_removal_helper(&(*wc)[j].segment);
			j++;
		}
		if (input[i] == '*' && !in_quotes)
		{
			i++;
			x = 0;
			(*wc)[j].segment = malloc (ft_part_len(input + 1, '*') + 1 * sizeof(char));
			if (!((*wc)[j].segment))
				(ft_putstr_fd("Malloc error segment in segment fill", 2), free(*wc) ,exit(EXIT_FAILURE));
			while (input[i] && (input[i] != '*' || in_quotes))
			{
				if (input[i] == '"' || input[i] == '\'')
				{
					if (in_quotes && quote_char == input[i])
						in_quotes = 0;
					else if (!in_quotes)
					{
						in_quotes = 1;
						quote_char = input[i];
					}
				}
				(*wc)[j].pos = (i == 0) ? 0 : (input[i + 1] == '\0' ? 1 : -1);
				(*wc)[j].segment[x++] = input[i++];
			}
			(*wc)[j].segment[x] = '\0';
			quotes_removal_helper(&(*wc)[j].segment);
			j++;
		}
		i++;
	}
	(*wc)[j].segment = NULL;
}

int	wildcard(t_sh *sh)
{
	int		fd[2];
	int		i;
	int		pos;
	int		char_pos;
	pid_t	pid;
	char 	**result;
	char	*buffer;
	char	*tmp;
	char	**cmd;
	t_wc	*wc;

	pos = ft_tabchr(sh->args, '*');
	if (pos == -1)
		return (0);
	pipe(fd);
	char_pos = ft_int_strchr(sh->args[pos], '*');
	buffer = ft_strdup("");
	cmd = malloc(2 * sizeof(char *));
	if (!cmd)
		(ft_putstr_fd("Malloc error ls in wildcard", 2) , exit(EXIT_FAILURE));
	cmd[0] = find_path("ls", sh);
	cmd[1] = NULL;
	while (is_quoted(sh->args[pos], char_pos) && char_pos != -1)
	{
		if (ft_int_strchr(sh->args[pos] + (char_pos + 1), '*') == -1)
			char_pos = -1;
		else
			char_pos += ft_int_strchr(sh->args[pos] + (char_pos + 1), '*') + 1;
	}
	if (pos != -1 && char_pos != -1 && !is_quoted(sh->args[pos], char_pos))
	{
		pid = fork();
		if (pid == 0)
		{
			dup2(fd[1], 1);
			close(fd[0]);
			close(fd[1]);
			execve(cmd[0], cmd, sh->env);
			return (1);
		}
		else
		{
			waitpid(pid, NULL, 0);
			close(fd[1]);
			while (1)
			{
				tmp = get_next_line(fd[0]);
				if (!tmp)
					break ;
				buffer = ft_strjoin_gnl(buffer, tmp);
				free(tmp);
			}
			close(fd[0]);
			result = ft_split(buffer, '\n');
			free(buffer);

			segment_fill(&wc, sh->args[pos]);

			wildcard_finder(&result, wc);

			remove_from_tab(&sh->args, pos);

			i = 0;
			while (result[i])
			{
				result[i] = ft_stradd(result[i], 0, "'");
				result[i] = ft_stradd(result[i], ft_strlen_gnl(result[i]), "'");
				add_to_tab_pos(&sh->args, result[i++], pos);
			}
			return (1);
		}
	}
	else
		return (0);
}
