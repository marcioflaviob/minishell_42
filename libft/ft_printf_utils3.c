/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:51:49 by trimize           #+#    #+#             */
/*   Updated: 2023/12/08 17:21:27 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_lenint2(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

int	flagdotdi(const char *str, va_list args, int y, t_var *var)
{
	int	tmp;
	int	i;

	i = 0;
	y = ft_atoi(str);
	tmp = va_arg(args, int);
	if (tmp == 0 && y == 0)
	{
		if (var->width > 0)
			return (printspace(var->width), var->width);
		return (0);
	}
	if (y > ft_lenint2(tmp))
	{
		if (tmp < 0)
			return (flagdotdi2(y, tmp, var, i));
		else
			return (flagdotdi3(y, tmp, var, i));
		return (var->error = -1, -1);
	}
	else
		return (flagdotdi4(var, tmp));
}

int	case_flagdot2(const char *str, va_list args, t_var *var)
{
	int	i;

	i = 0;
	if (str[i] == '.')
		i++;
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] == 'd' || str[i] == 'i')
		return (flagdotdi(&str[1], args, ft_atoi(&str[1]), var));
	else if (str[i] == 'u')
		return (ft_flagdotu(&str[1], args, var));
	else if (str[i] == 'x')
		return (ft_flagdotx(&str[1], args, var));
	else if (str[i] == 'X')
		return (ft_flagdotupperx(&str[1], args, var));
	return (-1);
}

int	case_flagdot(const char *str, va_list args, t_var *var)
{
	int		i;
	char	*tmp;

	i = 0;
	while (!ft_isalpha(str[i]))
		i++;
	if (str[i] == 's')
	{
		tmp = va_arg(args, char *);
		if (tmp == NULL && ft_atoi(&str[1]) >= 6)
		{
			if (var->width - 6 > 0)
				return (printspace(var->width - 6), ft_putstr(tmp), var->width);
			return (ft_putstr(tmp), 6);
		}
		else if (tmp == NULL && ft_atoi(&str[1]) < 6)
			return (case_flagdot5(var));
		else if (ft_atoi(&str[1]) < (int)ft_strlen(tmp))
			return (case_flagdot4(i, str, tmp, var));
		else if (ft_atoi(&str[1]) >= (int)ft_strlen(tmp))
			return (case_flagdot3(var, tmp));
	}
	return (case_flagdot2(str, args, var));
}

int	ft_rev(char *res, int n)
{
	int		i;
	char	tmp;

	i = 0;
	while (i < n / 2)
	{
		tmp = res[i];
		res[i] = res[n - i - 1];
		res[n - i - 1] = tmp;
		i++;
	}
	ft_putstr(res);
	return (n);
}
