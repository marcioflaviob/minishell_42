/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   on_startup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 22:46:03 by trimize           #+#    #+#             */
/*   Updated: 2024/04/05 17:17:15 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_prompt(t_sh *sh)
{
	// int		random;
	char	*random_line;
	char	*curr_dir;
	char	*fixed_dir;

	(void)sh;
	// random = get_random_number();
	// random_line = get_a_line(sh->emoji_path, random);
	random_line = NULL;
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

void	get_input(t_sh *sh)
{
	char	*buffer;
	char	*prompt;

	prompt = get_prompt(sh);
	write(STDOUT_FILENO, "\033[s", 3);
	buffer = readline(prompt);
	if (!buffer || ft_equalstr(buffer, "exit"))
	{
		printf("exit");
		if (buffer)
			free(buffer);
		free(prompt);
		free(sh->current_dir);
		exit(0);
	}
	if (buffer && buffer[0])
		add_history(buffer);
	// builtin_dealer(sh, buffer);
	sh->args = ft_better_split(buffer);
	free(prompt);
	return ;
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
		return (perror("Error opening file"), NULL);
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
