/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 12:13:20 by trimize           #+#    #+#             */
/*   Updated: 2024/04/06 16:29:44 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strlen_gnl(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	initialize(int *i, int *j)
{
	*i = 0;
	*j = 0;
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*result;

	initialize(&i, &j);
	if (!s1)
		s1 = ft_strdup("");
	if (!s2)
		return (s1);
	result = (char *)malloc((ft_strlen_gnl(s1)
				+ ft_strlen_gnl(s2) + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	while (s2[j])
		result[i++] = s2[j++];
	(free(s1), result[i] = 0);
	return (result);
}
