/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 22:23:53 by mbrandao          #+#    #+#             */
/*   Updated: 2024/04/06 22:03:05 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_sp_str(char *str)
{
	int	i;

	i = 0;
	if (ft_int_strstr_wc(str, "<<") != -1)
		return (ft_int_strstr_wc(str, "<<"));
	else if (ft_int_strstr_wc(str, ">>") != -1)
		return (ft_int_strstr_wc(str, ">>"));
	else if (ft_int_strstr_wc(str, "||") != -1)
		return (ft_int_strstr_wc(str, "||"));
	else if (ft_int_strstr_wc(str, "&&") != -1)
		return (ft_int_strstr_wc(str, "&&"));
	else
	{
		while (str[i])
		{
			if (str[i] == '<' || str[i] == '>' || str[i] == '|')
				return (i);
			i++;
		}
		return (-1);
	}
}

int	find_sp(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (args[i][0] == '<' || args[i][0] == '>' || args[i][0] == '|')
			return (i);
		if (ft_equalstr(args[i], "<<") || ft_equalstr(args[i], ">>"))
			return (i);
		if (ft_equalstr(args[i], "||") || ft_equalstr(args[i], "&&"))
			return (i);
	}
	return (-1);
}

char    *find_path(char *command, t_sh *sh)
{
	int        i;
	char    **paths;
	char    *str;

	i = 0;
	paths = ft_split(get_env("PATH", sh), ':');
	while (paths[i])
	{
		str = ft_strjoin(paths[i++], "/");
		str = ft_strjoin_gnl(str, command);
		if (access(str, X_OK) != -1)
			return (freetab(paths), str);
		free(str);
	}
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": command not found", 2);
	ft_putstr_fd("\n", 2);
	freetab(paths);
	return (NULL);
}

// char	**cmd_args(t_sh *sh, char **args)
// {
// 	int		i;
// 	int		sp_index;
// 	char	**tab;
// 	char	*temp;

// 	i = 1;
// 	sp_index = find_sp(args);
// 	if (!sp_index)
// 		sp_index = tab_len(args) - 1;
// 	tab = NULL;
// 	temp = find_path(args[0], sh);
// 	add_to_tab(&tab, temp);
// 	free(temp);
// 	while (i < sp_index && args[i])
// 		add_to_tab(&tab, args[i++]);
// 	return (tab);
// }

// void	exec_cmd(char **args, int first, t_sh *sh)
// {
// 	pid_t	pid;
// 	char	*buffer;
// 	char	*content;
// 	char	**cmd_args;

// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		if (first)
// 		{
// 			if (find_sp(args))
// 			{
// 				if (ft_equalstr(args[find_sp(args)], ">"))
// 				{
// 					redir_out_trunc(0, args[find_sp(args) + 1]);
// 					close(sh->pipe_read[1]);
// 					close(sh->pipe_write[0]);
// 					close(sh->pipe_write[1]);
// 					cmd_args = cmd_args(sh, args);
// 					execve(cmd_args[0], cmd_args, NULL);
// 					//cmd didn't execute
// 				}
// 				else if (ft_equalstr(args[find_sp(args)], ">>"))
// 				{
// 					redir_out_app(0, args[find_sp(args) + 1]);
// 					close(sh->pipe_read[1]);
// 					close(sh->pipe_write[0]);
// 					close(sh->pipe_write[1]);
// 					cmd_args = cmd_args(sh, args);
// 					execve(cmd_args[0], cmd_args, NULL);
// 				}
// 				else if (ft_equalstr(args[find_sp(args)], "|"))
// 				{
// 					dup2(STDOUT_FILENO, sh->pipe_write[1]); 
// 					close(sh->pipe_read[1]);
// 					close(sh->pipe_write[0]);
// 					close(sh->pipe_write[1]);
// 					cmd_args = cmd_args(sh, args);
// 					execve(cmd_args[0], cmd_args, NULL);
// 				}
// 			}
// 			else
// 			{
// 				close(sh->pipe_read[1]);
// 				close(sh->pipe_write[0]);
// 				close(sh->pipe_write[1]);
// 				cmd_args = cmd_args(sh, args);
// 				execve(cmd_args[0], cmd_args, NULL);
// 				//cmd didn't execute
// 			}
// 		}
// 		else if (ft_equalstr(argv[-1], "|"))
// 		{
// 			content = strdup("");
// 			while (1)
// 			{
// 				buffer = get_next_line(sh->pipe_write[0]);
// 				if (!buffer)
// 					break ;
// 				free(buffer);
// 				content = ft_strjoin_gnl(content, buffer);
// 			}
// 			write(sh->pipe_read[1], content, ft_strlen(content));
// 			free(content);
// 			dup2(STDIN_FILENO, sh->pipe_read[0]);
// 			close(sh->pipe_read[0]);
// 			if (find_sp(args))
// 			{
// 				if (ft_equalstr(args[find_sp(args)], ">"))
// 				{
// 					redir_out_trunc(0, args[find_sp(args) + 1]);
// 					close(sh->pipe_read[1]);
// 					close(sh->pipe_write[0]);
// 					close(sh->pipe_write[1]);
// 					cmd_args = cmd_args(sh, args);
// 					execve(cmd_args[0], cmd_args, NULL);
// 					//cmd didn't execute
// 				}
// 				else if (ft_equalstr(args[find_sp(args)], ">>"))
// 				{
// 					redir_out_app(0, args[find_sp(args) + 1]);
// 					close(sh->pipe_read[1]);
// 					close(sh->pipe_write[0]);
// 					close(sh->pipe_write[1]);
// 					cmd_args = cmd_args(sh, args);
// 					execve(cmd_args[0], cmd_args, NULL);
// 				}
// 				else if (ft_equalstr(args[find_sp(args)], "|"))
// 				{
// 					dup2(STDOUT_FILENO, sh->pipe_write[1]); 
// 					close(sh->pipe_read[1]);
// 					close(sh->pipe_write[0]);
// 					close(sh->pipe_write[1]);
// 					cmd_args = cmd_args(sh, args);
// 					execve(cmd_args[0], cmd_args, NULL);
// 				}
// 			}
// 			else
// 			{
// 				close(sh->pipe_read[1]);
// 				close(sh->pipe_write[0]);
// 				close(sh->pipe_write[1]);
// 				cmd_args = cmd_args(sh, args);
// 				execve(cmd_args[0], cmd_args, NULL);
// 				//cmd didn't execute
// 			}
// 		}
// 	}
// 	else
// 	{
// 		close(sh->pipe_read[0]);
// 		close(sh->pipe_read[1]);
// 		close(sh->pipe_write[0]);
// 		close(sh->pipe_write[1]);
// 	}
// }
