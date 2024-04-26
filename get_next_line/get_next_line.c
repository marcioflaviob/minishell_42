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

#include "get_next_line.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <fcntl.h>

char	*onenewline(int fd, char *str)
{
	char	*buff;
	int		bytes;
	int		i;

	i = 0;
	buff = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	bytes = 5;
	while (!ft_strchr_tgnl(str, '\n') && bytes != 0)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes == -1)
			return (free(buff), NULL);
		if (bytes == 0 && i == 0)
		{
			free(str);
			return (free(buff), NULL);
		}
		buff[bytes] = 0;
		str = ft_strjoin_tgnl(str, buff);
		i++;
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
	if (!str[i])
		return (free(str), NULL);
	tmp = (char *)malloc((ft_strlen_tgnl(str) - i + 1) * sizeof(char));
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

char	*get_next_line(int fd, int err)
{
	char		*line;
	static char	*str[4096];

	if (err == 1)
		return (free(str[fd]), NULL);
	if (fd < 0 || BUFFER_SIZE <= 0 )
		return (0);
	str[fd] = onenewline(fd, str[fd]);
	if (!str[fd])
		return (NULL);
	line = getoneline(str[fd]);
	str[fd] = next_line(str[fd]);
	return (line);
}

//int	main(void)
//{
//	int		fd[2];
//	int i = 0;

//	pipe(fd);
//	write(fd[1], "", 0);
//	close(fd[1]);

//	while (i < 130)
//	{
//		char *str = get_next_line(fd[0]);
//		if (!str)
//			exit(0);
//		printf("%s", str);
//		free(str);
//		i++;
//	}
//	close(fd[0]);
//	return (0);
//}
