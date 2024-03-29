/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 01:43:11 by marvin            #+#    #+#             */
/*   Updated: 2023/11/18 01:43:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

char	*onenewline(int fd, char *str)
{
	char	*buff;
	int		bytes;

	buff = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	bytes = 5;
	while (!ft_strchr2(str, '\n') && bytes != 0)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes == -1)
			return (free(buff), NULL);
		buff[bytes] = 0;
		str = ft_strjoin2(str, buff);
	}
	return (free(buff), str);
}

char	*next_line(char *str)
{
	int		i;
	int		y;
	char	*tmp;

	i = 0;
	y = 0;
	while (str[i] != '\n' && str[i])
		i++;
	if ((!str[i]) || (str[i] == '\n' && !str[i + 1]))
		return (free(str), NULL);
	tmp = (char *)malloc((ft_strlen2(str) - i) * sizeof(char));
	if (!tmp)
		return (0);
	i++;
	while (str[i])
		tmp[y++] = str[i++];
	return (tmp[y] = 0, free(str), tmp);
}

char	*getoneline(char *str)
{
	int		i;
	char	*line;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	line = (char *)malloc((i + 2) * sizeof(char));
	if (!line)
		return (0);
	i = -1;
	while (str[++i] && str[i] != '\n')
		line[i] = str[i];
	if (str[i] == '\n')
	{
		line[i] = str[i];
		i++;
	}
	line[i] = 0;
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	str = onenewline(fd, str);
	if (!str)
		return (NULL);
	line = getoneline(str);
	str = next_line(str);
	return (line);
}

/*int	main()
{
	char *str;
	int	fd;

	fd = open("pipex.c", O_RDONLY);

	while (1)
	{
		str = get_next_line(fd);
		if (!str)
		{
			free(str);
			break ;
		}
		printf("%s\n", str);
		free(str);
	}
	close(fd)
}
*/