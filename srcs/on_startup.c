/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   on_startup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 22:46:03 by trimize           #+#    #+#             */
/*   Updated: 2024/03/30 23:48:25 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_prompt(void)
{
	int		random;
	char	*random_line;
	char	*curr_dir;
	char	*fixed_dir;

	random = get_random_number();
	random_line = get_a_line("./assets/emojis", random);
	curr_dir = get_cwd();
	fixed_dir = get_curr_dir(curr_dir);
	free(curr_dir);
	random_line = ft_strjoin_gnl(random_line, CYAN_BACK);
	random_line = ft_strjoin_gnl(random_line, fixed_dir);
	random_line = ft_strjoin_gnl(random_line, " ➤");
	random_line = ft_strjoin_gnl(random_line, RESET);
	random_line = ft_strjoin_gnl(random_line, " ");
	free(fixed_dir);
	return (random_line);
}

char	*get_input(void)
{
	char	*buffer;
	char	*prompt;

	prompt = get_prompt();
	write(STDOUT_FILENO, "\033[s", 3);
	buffer = readline(prompt);
	if (!buffer || ft_equalstr(buffer, "exit"))
	{
		printf("exit");
		if (buffer)
			free(buffer);
		free(prompt);
		exit(0);
	}
	if (buffer && buffer[0])
		add_history(buffer);
	free(prompt);
	return (buffer);
}

char	*get_a_line(char *filename, int line_number)
{
	int		fd;
	int		i;
	int		current_line_number;
	char	*line;

	current_line_number = 0;
	i = -1;
	fd = open(filename, O_RDONLY);
	if (line_number > 128)
		line_number = 128;
	if (fd == -1)
		return (perror("Error opening file"), NULL); //TODO Fix problem when changing directory, the path to emojis would change and it won't open
	while (current_line_number != line_number)
	{
		line = get_next_line(fd);
		line[ft_strlen_gnl(line) - 1] = ' ';
		current_line_number++;
		if (current_line_number != line_number)
			free(line);
	}
	close(fd);
	return (line);
}

int	get_random_number(void)
{
	int		fd_random;
	char	random;

	fd_random = open("/dev/random", O_RDONLY);
	if (fd_random == -1)
		return (printf("Couldn't open /dev/random\n"), 50);
	read(fd_random, &random, 1);
	close(fd_random);
	if (random < 0)
		random *= -1;
	random = random % 127;
	if (random <= 0)
		random = 1;
	return (random);
}

char	*get_curr_dir(char *path)
{
	int		i;
	int		y;
	char	*curr_dir;

	i = 0;
	y = 0;
	while (path[i])
		i++;
	while (path[i] != '/')
	{
		y++;
		i--;
	}
	i++;
	curr_dir = (char *)malloc(y * sizeof(char));
	y = 0;
	while (path[i])
		curr_dir[y++] = path[i++];
	curr_dir[y] = 0;
	return (curr_dir);
}
