/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:51:27 by trimize           #+#    #+#             */
/*   Updated: 2023/12/08 19:33:49 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* ft_itoa.c:
*	Converts an int into a char *, returns the char * created.
*/

static int	lenint(int n)
{
	int		i;

	i = 0;
	if (n < 0)
		i++;
	if (n == 0)
		return (1);
	if (n == -2147483648)
		return (11);
	while (n != 0)
	{
		n = (n - (n % 10)) / 10;
		i++;
	}
	return (i);
}

static void	ft_rev_int_tab(char *tab, int size)
{
	int	i;
	int	j;
	int	x;

	i = 0;
	j = size - 1;
	if (tab[0] == '-')
	{
		i++;
		size++;
	}
	while (i < size / 2)
	{
		x = tab[j];
		tab[j] = tab[i];
		tab[i] = x;
		j--;
		i++;
	}
}

static void	intmin(char *str, int n)
{
	int	y;

	y = 1;
	if (n == -2147483648)
	{
		n = (n + 1) * -1;
		str[0] = '-';
		while (n > 0)
		{
			str[y++] = n % 10 + 48;
			n = (n - (n % 10)) / 10;
		}
		ft_rev_int_tab(str, y);
		str[10] = str[10] + 1;
		str[11] = 0;
	}
}

char	*ft_itoa(int n)
{
	int		y;
	char	*str;

	y = 0;
	str = (char *)malloc((lenint(n) + 1) * sizeof(char));
	if (!str)
		return (0);
	if (n == -2147483648)
		return (intmin(str, n), str);
	if (n == 0)
		str[y++] = '0';
	if (n < 0)
	{
		str[y++] = '-';
		n = n * -1;
	}
	while (n > 0)
	{
		str[y++] = n % 10 + 48;
		n = (n - (n % 10)) / 10;
	}
	str[y] = 0;
	return (ft_rev_int_tab(str, y), str);
}
