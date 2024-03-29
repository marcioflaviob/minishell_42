/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils8.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:20:02 by trimize           #+#    #+#             */
/*   Updated: 2023/12/08 17:21:42 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	w_space(const char *str, va_list args)
{
	int	tmp;
	int	i;
	int	y;

	y = 0;
	tmp = va_arg(args, int);
	i = ft_atoi(str) - ft_lenint(tmp) - 1;
	while (i > 0)
	{
		ft_putchar(' ');
		i--;
		y++;
	}
	(ft_putchar(' '), ft_putnbr(tmp));
	return (y + ft_lenint(tmp) + 1);
}

int	switch_case2(va_list args, t_var *var)
{
	char	*tmp;

	tmp = va_arg(args, char *);
	if (tmp == NULL)
	{
		if (var->width - 6 > 0)
			return (printspace(var->width - 6), ft_putstr(tmp), var->width);
		return (ft_putstr(tmp), 6);
	}
	(printspace(var->width - (int)ft_strlen(tmp)), ft_putstr(tmp));
	if (var->width - (int)ft_strlen(tmp) > 0)
		return ((int)ft_strlen(tmp) + (var->width - (int)ft_strlen(tmp)));
	else
		return ((int)ft_strlen(tmp));
}

int	switch_case3(int n, va_list args, t_var *var)
{
	n = va_arg(args, int);
	printspace(var->width - ft_lenint(n));
	if (var->width - ft_lenint(n) > 0)
		return (ft_putnbr(n), var->width);
	else
		return (ft_putnbr(n), ft_lenint(n));
}

int	case_flag02(int i, char const *str, t_var *var, va_list args)
{
	int	y;

	y = i;
	while (str[y] == '0')
	{
		var->v_i++;
		y++;
	}
	var->v_i--;
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] == 'd' || str[i] == 'i')
		return (flag0di(&str[y], args, var));
	else if (str[i] == 'u')
		return (ft_flag0u(&str[y], args));
	else if (str[i] == 'x')
		return (ft_flag0x(&str[y], args));
	else if (str[i] == 'X')
		return (ft_flag0upperx(&str[y], args));
	return (var->error = -1, -1);
}

int	case_flagminus2(int y, t_var *var, int c, int a)
{
	if (y == -1)
		return (var->error = -1, -1);
	while (c > y)
		(ft_putchar(' '), c--, a++);
	return (a + y);
}
