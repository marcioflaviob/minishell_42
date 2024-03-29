/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:12:38 by trimize           #+#    #+#             */
/*   Updated: 2023/12/08 19:00:15 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ft_atoi:
*	Converts a char * to an int, returns the int
*/

int	ft_atoi(const char *nptr)
{
	int	i;
	int	num;
	int	sign;

	i = 0;
	num = 0;
	sign = 1;
	while (nptr[i] == '\t' || nptr[i] == '\n' || nptr[i] == ' '
		|| nptr[i] == '\r' || nptr[i] == '\v' || nptr[i] == '\f')
		i++;
	if (nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (48 <= nptr[i] && nptr[i] <= 57)
		num = num * 10 + (nptr[i++] - 48);
	return (sign * num);
}

/*int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	printf("%d", ft_atoi("\x022"));
	printf("%d", atoi("2"));
	return (0);
}*/