/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teorimize <teorimize@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 16:31:24 by teorimize         #+#    #+#             */
/*   Updated: 2023/12/21 17:49:26 by teorimize        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* ft_atof:
*	Converts a char * to a double, returns the double
*/

static double	ft_atof_comp(char *str, double *num)
{
	int		n;
	int		i;
	double	d;

	if (str[0] == '.')
	{
		i = 1;
		d = 1;
		n = ft_atoi(&str[1]);
		while (str[i] == '0' && str[i])
		{
			d = d * 0.1;
			i++;
		}
		i = -1;
		while (++i < ft_lenint(n))
			d = d * 0.1;
		*num = *num + (d * ft_atoi(&str[1]));
		return (*num);
	}
	else
		return (0.0);
}

double	ft_atof(char *str)
{
	int		sign;
	int		i;
	double	num;

	i = 0;
	num = 0;
	sign = 1;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == ' '
		|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (48 <= str[i] && str[i] <= 57)
		num = num * 10.0 + (str[i++] - 48.0);
	ft_atof_comp(&str[i], &num);
	return (sign * num);
}
