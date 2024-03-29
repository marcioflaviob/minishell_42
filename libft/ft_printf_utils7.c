/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils7.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teorimize <teorimize@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 20:35:55 by trimize           #+#    #+#             */
/*   Updated: 2023/12/09 20:18:46 by teorimize        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	hex8(unsigned int nbr, char *b)
{
	int		i;
	int		y;
	int		n;
	char	tmp;
	char	res[17];

	if (nbr == 0)
		return (ft_putchar('0'), 1);
	(ft_bzero(res, 17), i = 0);
	while (nbr != 0)
	{
		res[i++] = (b[nbr % ft_strlen(b)]);
		nbr = nbr / ft_strlen(b);
	}
	y = -1;
	n = i;
	while (++y < n / 2)
	{
		tmp = res[y];
		res[y] = res[n - y - 1];
		res[n - y - 1] = tmp;
	}
	return (ft_putstr(res), i);
}

int	ft_flagdotx(const char *str, va_list args, t_var *var)
{
	int				y;
	unsigned int	i;
	unsigned int	tmp;
	unsigned int	a;

	y = ft_atoi(str);
	i = 0;
	tmp = va_arg(args, unsigned int);
	if (y == 0 && tmp == 0)
	{
		if (var->width - (int)i > 0)
			return (printspace(var->width), var->width);
		return (0);
	}
	a = get_hexnumber(tmp, "0123456789abcdef");
	if (var->width > y)
		i = ft_flagdotx2(a, i, var, y);
	y = y - a;
	while (y > 0)
		(ft_putchar('0'), y--, i++);
	y = hex8(tmp, "0123456789abcdef");
	return (i = i + a, i);
}

int	ft_flagdotupperx(const char *str, va_list args, t_var *var)
{
	int				y;
	unsigned int	i;
	unsigned int	tmp;
	unsigned int	a;

	y = ft_atoi(str);
	i = 0;
	tmp = va_arg(args, unsigned int);
	if (y == 0 && tmp == 0)
	{
		if (var->width - (int)i > 0)
			return (printspace(var->width), var->width);
		return (0);
	}
	a = get_hexnumber(tmp, "0123456789ABCDEF");
	if (var->width > y)
		i = ft_flagdotx2(a, i, var, y);
	y = y - a;
	while (y > 0)
		(ft_putchar('0'), y--, i++);
	y = hex8(tmp, "0123456789ABCDEF");
	return (i = i + a, i);
}

int	caseminusdot(const char *str, t_var *var, va_list args)
{
	int	y;
	int	i;
	int	a;
	int	x;

	i = 1;
	a = 0;
	while (str[i] == '-' || str[i] == '+')
		i++;
	x = i;
	while (ft_isdigit(str[i]))
		i++;
	y = case_flagdot(&str[i], args, var);
	i++;
	while (ft_isdigit(str[i]))
		i++;
	i++;
	var->v_i = var->v_i + i - 2;
	i = ft_atoi(&str[x]);
	while (i > y)
		(ft_putchar(' '), i--, a++);
	return (a + y);
}

int	w_plus(const char *str, va_list args)
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
	(ft_putchar('+'), ft_putnbr(tmp));
	return (y + ft_lenint(tmp) + 1);
}
