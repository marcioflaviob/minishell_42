/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:27:26 by mbrandao          #+#    #+#             */
/*   Updated: 2024/05/13 23:10:20 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	copy_tab(char ***taker, char **giver)
{
	int	i;

	i = 0;
	while (giver[i])
		i++;
	*taker = (char **)malloc((i + 1) * sizeof(char *));
	if (!*taker)
		(ft_putstr_fd("Malloc error copying tab\n", 2), exit(EXIT_FAILURE));
	i = 0;
	while (giver[i])
	{
			(*taker)[i] = ft_strdup(giver[i]);
		i++;
	}
	(*taker)[i] = NULL;
}

int	get_random_number(void)
{
	int		fd_random;
	char	random;

	fd_random = open("/dev/random", O_RDONLY);
	if (fd_random == -1)
		return (ft_putstr_fd("Couldn't open /dev/random\n", 2), 50);
	read(fd_random, &random, 1);
	close(fd_random);
	if (random < 0)
		random *= -1;
	random = random % 127;
	if (random <= 0)
		random = 1;
	return (random);
}

int	is_alscore_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]) || str[i] == '_')
			i++;
		else
			return (0);
	}
	return (1);
}

int	is_num_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) || str[i] == '-' || str[i] == '+')
			i++;
		else
			return (0);
	}
	return (1);
}

