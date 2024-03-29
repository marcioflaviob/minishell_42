/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:50:53 by trimize           #+#    #+#             */
/*   Updated: 2023/12/08 17:22:12 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	hex(long long int nbr, char *b, t_var *var)
{
	int		i;
	int		y;
	int		n;
	char	tmp;
	char	res[17];

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
	(printspace(var->width - i - 2), ft_putstr("0x"), ft_putstr(res));
	if (var->width - i - 2 > 0)
		return (i + (var->width - i - 2));
	else
		return (i);
}

int	hex2(unsigned int nbr, char *b, t_var *var)
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
	if (var->width - i > 0)
		return (printspace(var->width - i), ft_putstr(res), var->width);
	return (ft_putstr(res), i);
}

int	ft_printp(long long int p, t_var *var)
{
	if (p == 0)
	{
		if (var->width - 5 > 0)
			return (printspace(var->width - 5), ft_putstr("(nil)"), var->width);
		return (ft_putstr("(nil)"), 5);
	}
	return (hex(p, "0123456789abcdef", var) + 2);
}

int	switch_case(char c, va_list args, t_var *var)
{
	int		n;

	n = 0;
	if (c == 'c')
	{
		printspace(--var->width);
		ft_putchar(va_arg(args, int));
		if (var->width > 0)
			return (1 + var->width);
		return (1);
	}
	else if (c == 's')
		return (switch_case2(args, var));
	else if (c == 'p')
		return (ft_printp(va_arg(args, long long int), var));
	else if (c == 'd' || c == 'i')
		return (switch_case3(n, args, var));
	else if (c == 'u')
		return (ft_putnbr_unsigned2(va_arg(args, unsigned int), var));
	else if (c == 'x')
		return (hex2(va_arg(args, unsigned int), "0123456789abcdef", var));
	else if (c == 'X')
		return (hex2(va_arg(args, unsigned int), "0123456789ABCDEF", var));
	else
		return (var->error = -1, -1);
}

int	ft_printf(const char *str, ...)
{
	int		len;
	t_var	*var;
	va_list	args;

	if (!str)
		return (0);
	len = ft_errorplus(str);
	if (len == -1)
		return (-1);
	len = ft_error0(str);
	if (len == -1)
		return (-1);
	len = 0;
	var = ft_varnew(0);
	va_start(args, str);
	len = filler(str, var, len, args);
	free(var);
	return (va_end(args), len);
}
