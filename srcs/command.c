/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 22:23:53 by mbrandao          #+#    #+#             */
/*   Updated: 2024/04/07 16:26:13 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_sp(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (args[i][0] == '<' || args[i][0] == '>' || args[i][0] == '|')
			return (i);
		if (ft_equalstr(args[i], "<<") || ft_equalstr(args[i], ">>") || ft_equalstr(args[i], "&&"))
			return (i);
		i++;
	}
	return (0);
}

char	*find_path(char *command, t_sh *sh)
{
	int		i;
	char	**paths;
	char	*str;

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

char	**cmd_args(t_sh *sh, char **args)
{
	int		i;
	int		sp_index;
	char	**tab;
	char	*temp;

	i = 1;
	sp_index = find_sp(args);
	if (!sp_index)
		sp_index = tab_len(args) - 1;
	tab = NULL;
	temp = find_path(args[0], sh);
	add_to_tab(&tab, temp);
	free(temp);
	while (i < sp_index && args[i])
		add_to_tab(&tab, args[i++]);
	return (tab);
}

void	run_builtin(char *str, char **args, t_sh *sh)
{
	if (ft_equalstr(str, "echo"))
		echo(args);
	else if (ft_equalstr(str, "cd"))
	{
		if (find_sp(args) > 2)
			ft_putstr_fd("cd: too many arguments\n", 2);
		else
			cd(sh, args[1]);
	}
	else if (ft_equalstr(str, "pwd"))
		pwd();
	else if (ft_equalstr(str, "export"))
		export(sh, &args[1]);
	else if (ft_equalstr(str, "unset"))
		un_set(sh, &args[1]);
	else if (ft_equalstr(str, "env"))
		env(sh);
	else if (ft_equalstr(str, "exit"))
		exit(0);
}

int	is_builtin(char *str)
{
	if (ft_equalstr(str, "echo"))
		return (1);
	else if (ft_equalstr(str, "cd"))
		return (1);
	else if (ft_equalstr(str, "pwd"))
		return (1);
	else if (ft_equalstr(str, "export"))
		return (1);
	else if (ft_equalstr(str, "unset"))
		return (1);
	else if (ft_equalstr(str, "env"))
		return (1);
	else if (ft_equalstr(str, "exit"))
		return (1);
	else
		return (0);
}

void	exec_cmd(char **args, t_sh *sh)
{
	pid_t	pid;
	int		i;
	char	**cmd;

	i = 0;
	if (!args[0])
	{
		
	}
	pipe(sh->pipe);
	pid = fork();
	if (pid == 0)
	{
		if (find_sp(args))
		{
			if (ft_equalstr(args[find_sp(args)], "<"))
			{
				run_builtin(args[0], args, sh);
				rm_tab_line(&sh->args, sh->args[find_sp(args)]);
				rm_tab_line(&sh->args, sh->args[find_sp(args) + 1]);
				if (sh->fd_input != -2)
					close(sh->fd_input);
				if (sh->fd_output != -2)
					close(sh->fd_output);
				close(sh->pipe[0]);
				close(sh->pipe[1]);
				exit(0);
			}
			else if (ft_equalstr(args[find_sp(args)], ">"))
			{
				i = find_sp(args);
				redir_out_trunc(args[find_sp(args) + 1], &args[find_sp(args)], sh);
				if (!find_sp(&args[find_sp(args) + 1]))
					;
				else if (ft_equalstr(args[find_sp(&args[find_sp(args) + 1]) + i + 1], "|"))
				{
					dup2(sh->true_stdout, STDOUT_FILENO);
					dup2(sh->pipe[1], STDOUT_FILENO);
				}
				if (sh->fd_input != -2)
					close(sh->fd_input);
				close(sh->pipe[0]);
				close(sh->pipe[1]);
				run_builtin(args[0], args, sh);
				if (is_builtin(args[0]))
					exit(0);
				cmd = cmd_args(sh, args);
				execve(cmd[0], cmd, NULL);
				//cmd didn't execute
				exit(EXIT_FAILURE);
			}
			else if (ft_equalstr(args[find_sp(args)], ">>"))
			{
				i = find_sp(args);
				redir_out_app(args[find_sp(args) + 1], &args[find_sp(args)], sh);
				if (!find_sp(&args[find_sp(args) + 1]))
					;
				else if (ft_equalstr(args[find_sp(&args[find_sp(args) + 1]) + i + 1], "|"))
				{
					dup2(sh->true_stdout, STDOUT_FILENO);
					dup2(sh->pipe[1], STDOUT_FILENO);
				}
				if (sh->fd_input != -2)
					close(sh->fd_input);
				close(sh->pipe[0]);
				close(sh->pipe[1]);
				run_builtin(args[0], args, sh);
				if (is_builtin(args[0]))
					exit(0);
				cmd = cmd_args(sh, args);
				execve(cmd[0], cmd, NULL);
				//cmd didn't execute
				exit(EXIT_FAILURE);
			}
			else if (ft_equalstr(args[find_sp(args)], "|"))
			{
				if (sh->fd_input != -2)
					close(sh->fd_input);
				if (sh->fd_output != -2)
					close(sh->fd_output);
				dup2(sh->pipe[1], STDOUT_FILENO);
				close(sh->pipe[1]);
				close(sh->pipe[0]);
				run_builtin(args[0], args, sh);
				if (is_builtin(args[0]))
					exit(0);
				cmd = cmd_args(sh, args);
				if (sh->wrong_file != NULL)
					add_to_tab(&cmd, sh->wrong_file);
				execve(cmd[0], cmd, NULL);
			}
			else if (ft_equalstr(args[find_sp(args)], "&&"))
			{
				if (sh->fd_input != -2)
					close(sh->fd_input);
				if (sh->fd_output != -2)
					close(sh->fd_output);
				close(sh->pipe[0]);
				close(sh->pipe[1]);
				run_builtin(args[0], args, sh);
				if (is_builtin(args[0]))
					exit(0);
				cmd = cmd_args(sh, args);
				execve(cmd[0], cmd, NULL);
				//cmd didn't execute
				exit(EXIT_FAILURE);
			}
			else if (ft_equalstr(args[find_sp(args)], "||"))
			{
				if (sh->fd_input != -2)
					close(sh->fd_input);
				if (sh->fd_output != -2)
					close(sh->fd_output);
				close(sh->pipe[0]);
				close(sh->pipe[1]);
				run_builtin(args[0], args, sh);
				if (is_builtin(args[0]))
					exit(0);
				cmd = cmd_args(sh, args);
				execve(cmd[0], cmd, NULL);
				//cmd didn't execute
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			if (sh->fd_input != -2)
				close(sh->fd_input);
			if (sh->fd_output != -2)
				close(sh->fd_output);
			close(sh->pipe[0]);
			close(sh->pipe[1]);
			run_builtin(args[0], args, sh);
			if (is_builtin(args[0]))
					exit(0);
			cmd = cmd_args(sh, args);
			execve(cmd[0], cmd, NULL);
			//cmd didn't execute
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		i = find_sp(args);
		if (!find_sp(args))
		{
			waitpid(-1, &sh->last_cmd_st, 0);
			close(sh->pipe[1]);
			close(sh->pipe[0]);
			sh->position = tab_len(sh->args) - 1;
		}
		else
		{
			if (ft_equalstr(args[find_sp(args)], ">"))
			{
				if (!find_sp(&args[find_sp(args) + 1]))
					waitpid(pid, &sh->last_cmd_st, 0);
				else if (ft_equalstr(args[find_sp(&args[find_sp(args) + 1]) + i + 1], "|"))
					close(sh->pipe[1]);
				if (find_sp(&args[find_sp(args) + 1]) == 0)
					sh->position = tab_len(sh->args) - 1;
				else
					
					sh->position += find_sp(&args[find_sp(args) + 1]) + find_sp(args) + 1;
			}
			else if (ft_equalstr(args[find_sp(args)], ">>"))
			{
				if (!find_sp(&args[find_sp(args) + 1]))
					waitpid(pid, &sh->last_cmd_st, 0);
				else if (ft_equalstr(args[find_sp(&args[find_sp(args) + 1]) + i + 1], "|"))
					close(sh->pipe[1]);
				if (find_sp(&args[find_sp(args) + 1]) == 0)
					sh->position = tab_len(sh->args) - 1;
				else			
					sh->position += find_sp(&args[find_sp(args) + 1]) + find_sp(args) + 1;
			}
			//else if (ft_equalstr(args[find_sp(args)], ">")
			//	|| ft_equalstr(args[find_sp(args)], ">>"))
			//{
			//	if (!find_sp(&args[find_sp(args) + 1]) || !ft_equalstr(args[find_sp(&args[find_sp(args) + 1])], "|"))
			//		return ;
			//	else
			//	{
			//		i = 0;
			//		while (i < find_sp(&args[find_sp(args) + 1]))
			//			i++;
			//		sh->position += i;
			//	}
			//}
			else if (ft_equalstr(args[find_sp(args)], "<"))
			{
				//if (!find_sp(&args[find_sp(args) + 1]) || !ft_equalstr(args[find_sp(&args[find_sp(args) + 1])], "|"))
				//	return ;
				//else
				sh->position += find_sp(args) + 1;
			}
			else if (ft_equalstr(args[find_sp(args)], "|"))
			{
				close(sh->pipe[1]);
				sh->position += find_sp(args);
			}
			else if (ft_equalstr(args[find_sp(args)], "||"))
			{
				waitpid(pid, &sh->last_cmd_st, 0);
				if (sh->last_cmd_st != 0)
					sh->position += find_sp(args) + 1;
				else
				{
					if (find_sp(&args[find_sp(args) + 1]) == 0)
						sh->position = tab_len(sh->args) - 1;
					else
						sh->position += find_sp(args) + find_sp(&args[find_sp(args) + 1]);
				}
			}
			else if (ft_equalstr(args[find_sp(args)], "&&"))
			{
				waitpid(pid, &sh->last_cmd_st, 0);
				if (sh->last_cmd_st != 0)
					get_input(sh);
				else
					sh->position += find_sp(args) + 1;
			}
			else if (is_builtin(args[0]))
			{
				if (find_sp(args) == 0)
					sh->position = tab_len(sh->args) - 1;
				else
					sh->position += find_sp(args);
			}
		}
	}
}