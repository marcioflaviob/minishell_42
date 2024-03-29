/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:39:33 by trimize           #+#    #+#             */
/*   Updated: 2023/12/08 17:21:21 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	isflag(char c, char *flags)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(flags))
	{
		if (c == flags[i])
			return (1);
		i++;
	}
	return (0);
}

void	ft_putnbr_n(int n)
{
	if (n == -2147483648)
		write(1, "2147483648", 10);
	else if (n < 0)
		ft_putnbr(-n);
	else if (n > 9)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
		ft_putchar(n + 48);
}

int	flag0di(const char *str, va_list args, t_var *var)
{
	int	i;
	int	y;
	int	tmp;

	i = 0;
	y = ft_atoi(str);
	tmp = va_arg(args, int);
	if (tmp < 0)
	{
		(ft_putchar('-'), y = y - ft_lenint(tmp));
		while (y > 0)
			(ft_putchar('0'), y--, i++);
		return (ft_putnbr_n(tmp), i = i + ft_lenint(tmp), i);
	}
	else
	{
		y = y - ft_lenint(tmp);
		while (y > 0)
			(ft_putchar('0'), y--, i++);
		return (ft_putnbr(tmp), i = i + ft_lenint(tmp), i);
	}
	return (var->error = -1, -1);
}

int	ft_lenunsint(unsigned int n)
{
	int	i;

	i = 0;
	if (n < 0)
		i++;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

int	ft_flag0u(const char *str, va_list args)
{
	int				y;
	unsigned int	i;
	unsigned int	tmp;

	y = ft_atoi(str);
	i = 0;
	tmp = va_arg(args, unsigned int);
	y = y - ft_lenunsint(tmp);
	while (y > 0)
		(ft_putchar('0'), y--, i++);
	return (ft_putnbr_unsigned(tmp), i = i + ft_lenunsint(tmp), i);
}
