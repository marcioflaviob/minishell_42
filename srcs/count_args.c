/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:24:23 by trimize           #+#    #+#             */
/*   Updated: 2024/05/13 22:32:30 by mbrandao         ###   ########.fr       */
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
		c->i++;
}

void	count_args_4(char const *str, t_c_args *c)
{
	while (str[c->i])
	{
		while ((str[c->i] != 0) && (str[c->i] == ' '))
		{
			c->args++;
			while ((str[c->i] != 0) && (str[c->i] == ' '))
				c->i++;
		}
		if (str[c->i])
		{
			if (str[c->i] == '\'' || str[c->i] == '"')
			{
				c->quote_flag = !c->quote_flag;
				c->i++;
				continue ;
			}
			else if ((str[c->i] == '(' || str[c->i] == ')') && !c->quote_flag)
			{
				c->args++;
				c->i++;
				continue ;
			}
			else if (!c->quote_flag)
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
	c.quote_flag = 0;
	count_args_4(str, &c);
	// printf("args: %d\n", c.args);
	return (c.args);
}
