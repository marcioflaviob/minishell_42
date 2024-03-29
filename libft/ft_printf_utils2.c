/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 19:12:07 by trimize           #+#    #+#             */
/*   Updated: 2023/12/08 17:21:24 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	get_hexnumber(long long int nbr, char *b)
{
	int	i;

	i = 0;
	if (nbr == 0)
		return (1);
	while (nbr != 0)
	{
		i++;
		nbr = nbr / ft_strlen(b);
	}
	return (i);
}

int	ft_flag0x(const char *str, va_list args)
{
	int				y;
	unsigned int	i;
	unsigned int	tmp;
	unsigned int	a;

	y = ft_atoi(str);
	i = 0;
	tmp = va_arg(args, unsigned int);
	a = get_hexnumber(tmp, "0123456789abcdef");
	y = y - a;
	while (y > 0)
		(ft_putchar('0'), y--, i++);
	y = hex8(tmp, "0123456789abcdef");
	return (i = i + a, i);
}

int	ft_flag0upperx(const char *str, va_list args)
{
	int				y;
	unsigned int	i;
	unsigned int	tmp;
	unsigned int	a;

	y = ft_atoi(str);
	i = 0;
	tmp = va_arg(args, unsigned int);
	a = get_hexnumber(tmp, "0123456789ABCDEF");
	y = y - a;
	while (y > 0)
		(ft_putchar('0'), y--, i++);
	y = hex8(tmp, "0123456789ABCDEF");
	return (i = i + a, i);
}

int	case_flag0(const char *str, va_list args, t_var *var)
{
	int	i;

	i = 0;
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] == '.')
		return (case0dot(str, args, var));
	i = 0;
	if (str[i] == '-')
		return (var->error = -1, -1);
	if (str[i] == '.')
		i++;
	return (case_flag02(i, str, var, args));
}

int	case_flagminus(const char *str, va_list args, t_var *var)
{
	int	i;
	int	y;
	int	a;
	int	x;
	int	c;

	i = 1;
	a = 0;
	if (str[i] == '0')
		return (var->error = -1, -1);
	while (str[i] == '-')
		i++;
	c = ft_atoi(&str[i]);
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] == '.')
		return (caseminusdot(str, var, args));
	var->v_i = var->v_i + i - 1;
	y = switch_case(str[i], args, var);
	x = i;
	if (str[x - 1] == '-' && isflag(str[x], "cspdiuxX") && c != 0)
		(ft_putchar(' '), a++);
	return (case_flagminus2(y, var, c, a));
}
