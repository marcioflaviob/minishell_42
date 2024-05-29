/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_7.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:38:31 by trimize           #+#    #+#             */
/*   Updated: 2024/05/29 13:26:57 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	word_len_2(const char *str, t_word *w)
{
	while (str[w->i] && (str[w->i] != ' '
			|| (w->squote_flag || w->dquote_flag)))
	{
		if (str[w->i] == '\'' || str[w->i] == '"')
		{
			if (str[w->i] == '"' && !w->squote_flag)
				w->dquote_flag = !w->dquote_flag;
			else if (str[w->i] == '\'')
				w->squote_flag = !w->squote_flag;
			w->i++;
			continue ;
		}
		if ((str[w->i] == '(' || str[w->i] == ')')
			&& !w->squote_flag && !w->dquote_flag)
		{
			if (w->i != 0)
				break ;
			else
				w->i++;
			continue ;
		}
		w->i++;
	}
}

int	count_args(char const *str)
{
	t_c_args	c;

	c.i = 0;
	c.args = 1;
	c.squote_flag = 0;
	c.dquote_flag = 0;
	count_args_4(str, &c);
	return (c.args);
}

void	add_pid(size_t size, t_sh *sh)
{
	pid_t	*tmp;
	size_t	i;

	i = -1;
	if (size == 1)
		return ;
	else
	{
		tmp = (pid_t *)malloc((size) * sizeof(pid_t));
		while (++i < size - 1)
			tmp[i] = sh->pid[i];
		free(sh->pid);
		i = -1;
		sh->pid = (pid_t *)malloc((size) * sizeof(pid_t));
		while (++i < size - 1)
			sh->pid[i] = tmp[i];
		free(tmp);
	}
}
