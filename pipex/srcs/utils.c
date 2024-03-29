/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 09:44:06 by trimize           #+#    #+#             */
/*   Updated: 2024/03/15 14:25:55 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	fill_cmd_ex(char **cmd, char *str, t_tmp *tmp)
{
	cmd[tmp->fill_z][tmp->fill_y] = 0;
	tmp->fill_z++;
	cmd[tmp->fill_z] = (char *)malloc(256 * sizeof(char));
	tmp->fill_i++;
	tmp->fill_y = 0;
	if (str[tmp->fill_i] == '\'')
	{
		tmp->fill_i++;
		while (str[tmp->fill_i] != '\'')
			cmd[tmp->fill_z][tmp->fill_y++] = str[tmp->fill_i++];
		tmp->fill_i++;
	}
	else if (str[tmp->fill_i] == '\"')
	{
		tmp->fill_i++;
		while (str[tmp->fill_i] != '\"')
			cmd[tmp->fill_z][tmp->fill_y++] = str[tmp->fill_i++];
		tmp->fill_i++;
	}
}

void	fill_cmd(char **cmd, char *str, t_tmp *tmp)
{
	int	arg;
	int	size;

	arg = 0;
	tmp->fill_i = 0;
	tmp->fill_y = 0;
	tmp->fill_z = 0;
	size = 0;
	while (str[tmp->fill_i] != ' ' && str[tmp->fill_i])
		tmp->fill_i++;
	while (str[tmp->fill_i - 1] != '/' && tmp->fill_i > 0)
	{
		tmp->fill_i--;
		size++;
	}
	cmd[tmp->fill_z] = (char *)malloc((size + 1) * sizeof(char));
	while (str[tmp->fill_i])
	{
		cmd[tmp->fill_z][tmp->fill_y++] = str[tmp->fill_i++];
		if (str[tmp->fill_i] == ' ')
			fill_cmd_ex(cmd, str, tmp);
	}
	cmd[tmp->fill_z][tmp->fill_y] = 0;
	cmd[tmp->fill_z + 1] = 0;
}

int	nb_arg(char *str)
{
	int	i;
	int	nb;

	i = 0;
	nb = 1;
	while (str[i])
	{
		if (str[i] == ' ')
			nb++;
		i++;
		if (str[i] == '\'')
		{
			while (str[i] != '\'')
				i++;
		}
		if (str[i] == '\"')
		{
			while (str[i] != '\"')
				i++;
		}
	}
	return (nb);
}

char	*find_path(char *command)
{
	int		i;
	char	**paths;
	char	*str;

	i = 0;
	paths = ft_split("/usr/local/sbin/:/usr/local/bin/:/usr/sbin/:/usr/bin/:" \
		"/sbin/:/bin/:/usr/games/:/usr/local/games/:/snap/bin/", ':');
	while (paths[i])
	{
		str = ft_strjoin(paths[i++], command);
		if (access(str, X_OK) != -1)
			return (freetab(paths), str);
		free(str);
	}
	ft_putstr_fd("command not found: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd("\n", 2);
	freetab(paths);
	str = ft_strdup("not_existing_directory");
	return (str);
}

void	freetab(char **array)
{
	int	i;

	i = 0;
	if (array == NULL)
		return ;
	while (array[i] != NULL)
		free(array[i++]);
	free(array);
}
