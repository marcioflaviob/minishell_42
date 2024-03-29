/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils9.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:44:19 by trimize           #+#    #+#             */
/*   Updated: 2023/12/08 17:21:45 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	flagdotdi2(int y, int tmp, t_var *var, int i)
{
	y = y - ft_lenint2(tmp);
	printspace(var->width - y - ft_lenint2(tmp) - 1);
	ft_putchar('-');
	while (y > 0)
		(ft_putchar('0'), y--, i++);
	i = i + ft_lenint(tmp);
	if (var->width - i > 0)
		return (ft_putnbr_n(tmp), var->width);
	return (ft_putnbr_n(tmp), i);
}

int	flagdotdi3(int y, int tmp, t_var *var, int i)
{
	y = y - ft_lenint2(tmp);
	printspace(var->width - y - ft_lenint2(tmp));
	while (y > 0)
		(ft_putchar('0'), y--, i++);
	i = i + ft_lenint(tmp);
	if (var->width - i > 0)
		return (ft_putnbr_n(tmp), var->width);
	return (ft_putnbr(tmp), i);
}

int	flagdotdi4(t_var *var, int tmp)
{
	if (var->width - ft_lenint(tmp) > 0)
	{
		printspace(var->width - ft_lenint(tmp));
		return (ft_putnbr(tmp), var->width);
	}
	return (ft_putnbr(tmp), ft_lenint(tmp));
}

int	case_flagdot3(t_var *var, char *tmp)
{
	if (var->width - (int)ft_strlen(tmp) > 0)
	{
		printspace(var->width - (int)ft_strlen(tmp));
		return (ft_putstr(tmp), var->width);
	}
	return (ft_putstr(tmp), (int)ft_strlen(tmp));
}

int	case_flagdot4(int i, const char *str, char *tmp, t_var *var)
{
	int	y;

	y = ft_atoi(&str[i - 1]);
	(printspace(var->width - y), i = 0);
	while (i < y)
		ft_putchar(tmp[i++]);
	if (var->width - i > 0)
		return (var->width);
	return (i);
}
