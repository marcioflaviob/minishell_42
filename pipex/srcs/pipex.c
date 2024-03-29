/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:06:13 by trimize           #+#    #+#             */
/*   Updated: 2024/03/29 18:19:38 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	check_args(int argc, char **argv)
{
	if (argc < 5)
		(ft_putstr_fd("Wrong number of arguments\n",
				STDERR_FILENO), exit(-1));
	else if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		if (argc != 6)
			(ft_putstr_fd("Wrong number of arguments\n",
					STDERR_FILENO), exit(-1));
	}
}

int	main(int argc, char **argv)
{
	t_tmp	tmp;
	int		i;

	tmp.status = 0;
	i = 0;
	check_args(argc, argv);
	tmp.env = (char **)malloc(3 * sizeof(char *));
	if (tmp.env == NULL)
		(exit(EXIT_FAILURE), free(tmp.pid));
	tmp.pid = ft_calloc(argc - 2, sizeof(pid_t));
	tmp.lang = ft_strdup("LANG=en_US.UTF-8");
	tmp.lcall = ft_strdup("LANG=en_US.UTF-8");
	tmp.env[0] = tmp.lang;
	tmp.env[1] = tmp.lcall;
	tmp.env[2] = NULL;
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		here_doc_init(&tmp, argv, argc);
	else
		(pipe_init(&tmp, argv, argc), check_commands(argc, argv, &tmp),
			free_exit_main(&tmp));
	if (WIFEXITED(tmp.status))
		return (WEXITSTATUS(tmp.status));
	else if (WIFSIGNALED(tmp.status))
		return (WTERMSIG(tmp.status));
	return (0);
}
