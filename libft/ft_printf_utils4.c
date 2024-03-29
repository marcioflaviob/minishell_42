/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 19:37:32 by trimize           #+#    #+#             */
/*   Updated: 2023/12/08 17:21:29 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	hexasharp(const char *str, unsigned int nbr, char *b)
{
	int		i;
	int		n;
	char	res[17];

	(ft_bzero(res, 17), i = 0);
	if (nbr == 0)
		return (ft_putchar('0'), 1);
	while (nbr != 0)
	{
		res[i++] = (b[nbr % ft_strlen(b)]);
		nbr = nbr / ft_strlen(b);
	}
	n = i;
	return (ft_putchar('0'), ft_putchar(str[1]), ft_rev(res, n) + 2);
}

int	case_flagsharp(const char *str, va_list args, t_var *var)
{
	if (str[1] == 'x')
		return (hexasharp(str, va_arg(args, unsigned int), "0123456789abcdef"));
	else if (str[1] == 'X')
		return (hexasharp(str, va_arg(args, unsigned int), "0123456789ABCDEF"));
	else
		return (var->error = -1, -1);
}

int	sspace(const char *str, va_list args)
{
	int		y;
	int		i;
	int		len;
	char	*res;

	y = ft_atoi(str);
	i = 0;
	res = va_arg(args, char *);
	len = (int)ft_strlen(res);
	while (y > len)
		(ft_putchar(' '), i++, y--);
	return (ft_putstr(res), i + len);
}

int	dispace(const char *str, va_list args)
{
	int	y;
	int	i;
	int	len;
	int	res;

	y = ft_atoi(str);
	i = 0;
	res = va_arg(args, int);
	len = (int)ft_lenint(res);
	if ((y == len) || (y == 0 && res >= 0))
		return (ft_putchar(' '), ft_putnbr(res), len + 1);
	while (y > len)
		(ft_putchar(' '), i++, y--);
	return (ft_putnbr(res), i + len);
}

int	case_flagspace(const char *str, va_list args, t_var *var)
{
	int	i;

	i = 1;
	while (str[i] == ' ')
	{
		i++;
		var->v_i++;
	}
	if (ft_isdigit(str[i]))
		return (w_space(str, args));
	if (str[i] == 's')
		return (sspace(str, args));
	else if (str[i] == 'i' || str[i] == 'd')
		return (dispace(str, args));
	return (var->error = -1, -1);
}
