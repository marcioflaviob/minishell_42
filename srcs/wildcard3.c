/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:09:29 by mbrandao          #+#    #+#             */
/*   Updated: 2024/05/13 19:25:22 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// pos is defined as the position of the wildcard in the input
// pos is 0 when the wildcard is the first argument
// pos is -1 when the wildcard is in the middle of the arguments
// pos is 1 when the wildcard is the last argument
void	segment_fill_3(char *input, t_segfill *s, t_wc **wc)
{
	while (input[s->i] && (input[s->i] != '*' || s->in_quotes))
	{
		if (input[s->i] == '"' || input[s->i] == '\'')
		{
			if (s->in_quotes && s->quote_char == input[s->i])
				s->in_quotes = 0;
			else if (!s->in_quotes)
			{
				s->in_quotes = 1;
				s->quote_char = input[s->i];
			}
		}
		(*wc)[s->j].segment[s->x++] = input[s->i++];
		(*wc)[s->j].pos = 0;
	}
}

void	segment_fill_4(char *input, t_segfill *s, t_wc **wc)
{
	while (input[s->i] && (input[s->i] != '*' || s->in_quotes))
	{
		if (input[s->i] == '"' || input[s->i] == '\'')
		{
			if (s->in_quotes && s->quote_char == input[s->i])
				s->in_quotes = 0;
			else if (!s->in_quotes)
			{
				s->in_quotes = 1;
				s->quote_char = input[s->i];
			}
		}
		if (s->i == 0)
			(*wc)[s->j].pos = 0;
		else if (input[s->i + 1] == '\0')
			(*wc)[s->j].pos = 1;
		else
			(*wc)[s->j].pos = -1;
		(*wc)[s->j].segment[s->x++] = input[s->i++];
	}
}

void	segment_fill_5(char *input, t_segfill *s, t_wc **wc)
{
	if (s->i == 0 && input[s->i] != '*')
	{
		s->x = 0;
		(*wc)[s->j].segment = malloc (ft_part_len(input, '*')
				+ 1 * sizeof(char));
		if (!((*wc)[s->j].segment))
			(ft_putstr_fd("Malloc error segment in segment fill", 2),
				free(*wc), exit(EXIT_FAILURE));
		segment_fill_3(input, s, wc);
		(*wc)[s->j].segment[s->x] = '\0';
		quotes_removal_helper(&(*wc)[s->j].segment);
		s->j++;
	}
}

void	segment_fill_6(char *input, t_segfill *s, t_wc **wc)
{
	if (input[s->i] == '*' && !s->in_quotes)
	{
		s->i++;
		s->x = 0;
		(*wc)[s->j].segment = malloc (ft_part_len(input + 1, '*')
				+ 1 * sizeof(char));
		if (!((*wc)[s->j].segment))
			(ft_putstr_fd("Malloc error segment in segment fill", 2),
				free(*wc), exit(EXIT_FAILURE));
		segment_fill_4(input, s, wc);
		(*wc)[s->j].segment[s->x] = '\0';
		quotes_removal_helper(&(*wc)[s->j].segment);
		s->j++;
	}
}

void	segment_fill(t_wc **wc, char *input)
{
	t_segfill	s;

	s.i = 0;
	s.j = 0;
	s.seg_count = 0;
	s.in_quotes = 0;
	s.quote_char = '\0';
	segment_fill_2(input, &s);
	*wc = malloc((s.seg_count + 2) * sizeof(t_wc));
	if (!*wc)
		(ft_putstr_fd("Malloc error tab in segment fill", 2),
			exit(EXIT_FAILURE));
	s.i = 0;
	s.j = 0;
	while (input[s.i])
	{
		segment_fill_5(input, &s, wc);
		segment_fill_6(input, &s, wc);
	}
	(*wc)[s.j].segment = NULL;
}
