/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   on_startup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 22:46:03 by trimize           #+#    #+#             */
/*   Updated: 2024/05/29 13:28:45 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_prompt(t_sh *sh)
{
	int		random;
	char	*random_line;
	char	*curr_dir;
	char	*fixed_dir;

	random = get_random_number();
	random_line = get_a_line(sh->emoji_path, random);
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

void	buffer_dealer(t_sh *sh, char **buffer, char *prompt)
{
	int	fd;

	*buffer = readline(prompt);
	free(prompt);
	if (!*buffer)
	{
		fd = open(sh->emoji_path, O_RDONLY);
		get_next_line(fd, 1);
		freetab(sh->env);
		free(sh->emoji_path);
		freetab(sh->variables);
		write(1, "exit", 4);
		close(sh->true_stdin);
		close(sh->true_stdout);
		close(fd);
		free(sh->current_dir);
		exit(0);
	}
	if (*buffer && *buffer[0])
		add_history(*buffer);
	else
		get_input(sh);
	sh->args = ft_better_split(*buffer);
}

void	checkers(t_sh *sh, char **buffer, char **prompt)
{
	if (par_check_all(sh->args, sh))
	{
		*buffer = ft_itoa(sh->last_cmd_st);
		*prompt = ft_strjoin("?=", *buffer);
		free(*buffer);
		add_env(sh, *prompt);
		free(*prompt);
		freetab(sh->args);
		get_input(sh);
	}
	while (wildcard(sh))
		;
	set_sp_bool(sh);
	replace_var(sh, &sh->args);
	quotes_removal(&sh->args);
}

void	get_input(t_sh *sh)
{
	char	*buffer;
	char	*prompt;

	sh->nb_cmd = 0;
	if (g_signal == 2)
	{
		add_env(sh, "?=130");
		g_signal = 0;
	}
	dup2(sh->true_stdin, STDIN_FILENO);
	dup2(sh->true_stdout, STDOUT_FILENO);
	if (sh->fd_input != -2)
		(close(sh->fd_input), sh->fd_input = -2);
	if (sh->fd_output != -2)
		(close(sh->fd_output), sh->fd_output = -2);
	sh->position = 0;
	waitpid(-1, &sh->last_cmd_st, 0);
	prompt = get_prompt(sh);
	write(STDOUT_FILENO, "\033[s", 3);
	buffer_dealer(sh, &buffer, prompt);
	checkers(sh, &buffer, &prompt);
	while (sh->args[sh->position] && !sh->args[sh->position][0])
		sh->position++;
	arg(sh);
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
		line = get_next_line(fd, 0);
		line[ft_strlen_gnl(line) - 1] = ' ';
		current_line_number++;
		if (current_line_number != line_number)
			free(line);
	}
	close(fd);
	return (line);
}
