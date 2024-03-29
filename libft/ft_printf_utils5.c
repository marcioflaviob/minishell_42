/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 20:21:53 by trimize           #+#    #+#             */
/*   Updated: 2023/12/08 17:21:32 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	case_flagplus(const char *str, va_list args, t_var *var)
{
	int	res;
	int	i;

	res = va_arg(args, int);
	i = 1;
	while (str[i] == '+' || str[i] == '-')
	{
		i++;
		var->v_i++;
	}
	if (ft_isdigit(str[i]))
		return (w_plus(&str[i], args));
	else if (res >= 0)
		return (ft_putchar('+'), ft_putnbr(res), ft_lenint(res) + 1);
	else if (res < 0)
		return (ft_putnbr(res), ft_lenint(res));
	else
		return (var->error = -1, -1);
}

int	switch_case_flags(const char *str, va_list args, t_var *var)
{
	int	i;

	i = 0;
	if (str[i] == '0')
		return (case_flag0(str, args, var));
	else if (str[i] == '-')
		return (case_flagminus(str, args, var));
	else if (str[i] == '.')
		return (case_flagdot(str, args, var));
	else if (str[i] == '#')
		return (case_flagsharp(str, args, var));
	else if (str[i] == ' ')
		return (case_flagspace(str, args, var));
	else if (str[i] == '+')
		return (case_flagplus(str, args, var));
	return (var->error = -1, -1);
}

t_var	*ft_varnew(int i)
{
	t_var	*list;

	list = (t_var *)malloc(sizeof(t_var));
	if (!list)
		return (0);
	list->v_i = i;
	list->width = 0;
	list->error = 0;
	return (list);
}

int	filler2(int len, const char *str, t_var *var)
{
	if (len == -1)
		return (-1);
	if (!ft_isdigit(str[var->v_i + 1]))
		var->v_i--;
	var->v_i = var->v_i + ft_lenint(ft_atoi(&str[var->v_i + 1]));
	var->v_i++;
	return (len);
}

int	filler(const char *str, t_var *var, int len, va_list args)
{
	while (str[var->v_i])
	{
		if (str[var->v_i] == 37 && str[var->v_i + 1] != 37)
		{
			checkwidth(str, var);
			if (isflag(str[var->v_i + 1], "-0.# +"))
			{
				len = filler3(len, str, args, var);
				if (len == -1)
					return (-1);
			}
			else
			{
				len = len + switch_case(str[++var->v_i], args, var);
				if (var->error == -1)
					return (-1);
			}
		}
		else if (str[var->v_i] == '%' && str[var->v_i + 1] == '%')
			(ft_putchar('%'), len++, var->v_i++);
		else
			(ft_putchar(str[var->v_i]), len++);
		var->v_i++;
	}
	return (len);
}
