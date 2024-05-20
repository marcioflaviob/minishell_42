/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:24:23 by trimize           #+#    #+#             */
/*   Updated: 2024/05/20 14:51:07 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	count_args_2(char const *str, t_c_args *c)
{
	while ((str[c->i] != 0) && (str[c->i] != ' ' && str[c->i] != '('
			&& str[c->i] != ')') && !(str[c->i] == '\''
			|| str[c->i] == '"'))
		c->i++;
}

void	count_args_3(char const *str, t_c_args *c)
{
	while ((str[c->i] != 0) && (str[c->i] != '\'' && str[c->i] != '"'))
		c->i++;
	if (str[c->i] == '\'' || str[c->i] == '"')
	{
		if (str[c->i] == '"' && !c->squote_flag)
			c->dquote_flag = !c->dquote_flag;
		else if (str[c->i] == '\'')
			c->squote_flag = !c->squote_flag;
		c->i++;
	}
}

void	count_args_5(char const *str, t_c_args *c)
{
	while ((str[c->i] != 0) && (str[c->i] == ' '))
	{
		if (!c->dquote_flag && !c->squote_flag)
			c->args++;
		while ((str[c->i] != 0) && (str[c->i] == ' '))
			c->i++;
	}
}

void	count_args_4(char const *str, t_c_args *c)
{
	while (str[c->i])
	{
		count_args_5(str, c);
		if (str[c->i])
		{
			if (str[c->i] == '\'' || str[c->i] == '"')
			{
				if (str[c->i] == '"' && !c->squote_flag)
					c->dquote_flag = !c->dquote_flag;
				else if (str[c->i] == '\'')
					c->squote_flag = !c->squote_flag;
				c->i++;
				continue ;
			}
			else if ((str[c->i] == '(' || str[c->i] == ')') && !c->squote_flag && !c->dquote_flag)
			{
				c->args++;
				c->i++;
				continue ;
			}
			else if (!c->squote_flag && !c->dquote_flag)
				count_args_2(str, c);
			else
				count_args_3(str, c);
		}
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
	//printf("\narg counter: %d\n", c.args);
	return (c.args);
}
