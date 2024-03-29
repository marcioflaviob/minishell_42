/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils11.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 13:51:36 by trimize           #+#    #+#             */
/*   Updated: 2023/12/08 17:21:53 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_error0(const char *str)
{
	int	i;
	int	a;
	int	c;

	a = 0;
	i = 0;
	c = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			while (!isflag(str[++i], "csdixXup%"))
			{
				if (str[i] == '0' && !ft_isdigit(str[i - 1])
					&& str[i - 1] != '.')
					a++;
				if (str[i] == '-')
					c++;
			}
		}
		i++;
	}
	if (a != 0 && c != 0)
		return (-1);
	return (0);
}

int	ft_errorplus(const char *str)
{
	int	i;
	int	a;
	int	c;

	a = 0;
	i = 0;
	c = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			while (!isflag(str[++i], "csdixXup%"))
			{
				if (str[i] == '+')
					a++;
				if (str[i] == ' ')
					c++;
			}
		}
		i++;
	}
	if (a != 0 && c != 0)
		return (-1);
	return (0);
}
