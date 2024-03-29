/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils6.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:51:02 by trimize           #+#    #+#             */
/*   Updated: 2023/12/08 17:21:35 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	checkwidth(const char *str, t_var *var)
{
	if (str[var->v_i + 1] != '0')
	{
		var->v_i++;
		var->width = ft_atoi(&str[var->v_i]);
		while (ft_isdigit(str[var->v_i]))
			var->v_i++;
		var->v_i--;
	}
}

void	printspace(int nb)
{
	while (nb > 0)
		(ft_putchar(' '), nb--);
}

int	case0dot(const char *str, va_list args, t_var *var)
{
	int	i;
	int	y;

	y = ft_atoi(str);
	var->width = y;
	i = 1;
	while (str[i] && !isflag(str[i], "diuxX"))
	{
		var->v_i++;
		if (str[i] == '.')
		{
			return (case_flagdot(&str[i], args, var));
		}
		i++;
	}
	return (0);
}

int	ft_putnbr_unsigned2(unsigned int n, t_var *var)
{
	int		i;
	int		y;
	int		nb;
	char	tmp;
	char	res[11];

	if (n == 0 && var->width - 1 > 0)
		return (printspace(var->width - 1), ft_putchar('0'), var->width);
	else if (n == 0)
		return (ft_putchar('0'), 1);
	(ft_bzero(res, 11), i = 0);
	i = ft_putnbr_unsigned3(n, res, i);
	y = -1;
	nb = i;
	while (++y < nb / 2)
	{
		tmp = res[y];
		res[y] = res[nb - y - 1];
		res[nb - y - 1] = tmp;
	}
	if (var->width - i > 0)
		return (printspace(var->width - i), ft_putstr(res), var->width);
	return (ft_putstr(res), i);
}

int	ft_flagdotu(const char *str, va_list args, t_var *var)
{
	int				y;
	unsigned int	i;
	unsigned int	tmp;

	y = ft_atoi(str);
	i = 0;
	tmp = va_arg(args, unsigned int);
	if (y == 0 && tmp == 0)
	{
		if (var->width - (int)i > 0)
			return (printspace(var->width), var->width);
		return (0);
	}
	if (var->width > ft_atoi(str))
		i = ft_flagdotu2(y, tmp, var, i);
	y = y - ft_lenunsint(tmp);
	while (y > 0)
		(ft_putchar('0'), y--, i++);
	i = i + ft_lenunsint(tmp);
	return (ft_putnbr_unsigned(tmp), i);
}
