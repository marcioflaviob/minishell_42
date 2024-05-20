/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:11:51 by mbrandao          #+#    #+#             */
/*   Updated: 2024/05/20 12:47:03 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	wildcard_finder_2(char *str, t_wc *wc, int j, int *pass)
{
	if (wc[j].pos == 0 && ft_strncmp(str, wc[j].segment,
			ft_strlen(wc[j].segment)) != 0)
		return (*pass = 0, 0);
	else if (wc[j].pos == 1 && ft_strncmp(str + ft_strlen(str)
			- ft_strlen(wc[j].segment), wc[j].segment,
			ft_strlen(wc[j].segment)) != 0)
		return (*pass = 0, 0);
	return (1);
}

int	wildcard_finder_3(t_wc *wc, int j, int *pass)
{
	wc->found_position = ft_strstr_wc(wc->current_position,
			wc[j].segment);
	if (wc->found_position == wc->current_position)
	{
		wc->found_position = ft_strstr_wc(wc->current_position + 1,
				wc[j].segment);
		return (1);
	}
	if (wc->found_position == NULL)
		return (*pass = 0, 0);
	else
	{
		wc->current_position = wc->found_position
			+ ft_strlen(wc[j].segment);
		return (1);
	}
}

void	wildcard_finder_4(t_wc *wc, char *str, int *pass, int j)
{
	while (wc[j].segment)
	{
		if (wc[j].segment[0] != 0)
		{
			if (!wildcard_finder_2(str, wc, j, &(*pass)))
				break ;
			else if (wc[j].pos == -1)
				if (!wildcard_finder_3(wc, j, &(*pass)))
					break ;
		}
		j++;
	}
}

void	wildcard_finder(char ***tab, t_wc *wc, t_sh *sh)
{
	int		i;
	int		j;
	int		pass;
	char	*str;

	i = 0;
	while ((*tab)[i])
	{
		str = (*tab)[i];
		pass = 1;
		wc->current_position = str;
		j = 0;
		wildcard_finder_4(wc, str, &pass, j);
		if (!pass)
			remove_from_tab(tab, i--, sh);
		i++;
	}
}

void	segment_fill_2(char *input, t_segfill *s)
{
	while (input[s->i])
	{
		if (input[s->i] == '*' && !s->in_quotes)
			s->seg_count++;
		else if (input[s->i] == '"' || input[s->i] == '\'')
		{
			if (s->in_quotes && s->quote_char == input[s->i])
				s->in_quotes = 0;
			else if (!s->in_quotes)
			{
				s->in_quotes = 1;
				s->quote_char = input[s->i];
			}
		}
		s->i++;
	}
}
