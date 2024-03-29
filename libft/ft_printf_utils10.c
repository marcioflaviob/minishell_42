/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils10.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:01:06 by trimize           #+#    #+#             */
/*   Updated: 2023/12/08 17:21:48 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	case_flagdot5(t_var *var)
{
	if (var->width > 1)
		return (printspace(var->width), ft_putstr(""), var->width);
	return (ft_putstr(""), 0);
}

int	filler3(int len, const char *str, va_list args, t_var *var)
{
	len = len + switch_case_flags(&str[++var->v_i], args, var);
	if (var->error == -1)
		return (-1);
	len = filler2(len, str, var);
	if (!str[var->v_i])
		return (len);
	return (len);
}

int	ft_putnbr_unsigned3(unsigned int n, char *res, int i)
{
	while (n > 0)
	{
		res[i++] = n % 10 + 48;
		n = n / 10;
	}
	return (i);
}

int	ft_flagdotu2(int y, unsigned int tmp, t_var *var, int i)
{
	if (y > ft_lenunsint(tmp))
		(printspace(var->width - y), i = var->width - y);
	else
	{
		printspace(var->width - ft_lenunsint(tmp));
		(i = var->width - ft_lenunsint(tmp));
	}
	return (i);
}

int	ft_flagdotx2(unsigned int a, unsigned int i, t_var *var, int y)
{
	if (y > (int)a)
		(printspace(var->width - y), i = var->width - y);
	else
		(printspace(var->width - (int)a), i = var->width - (int)a);
	return (i);
}
