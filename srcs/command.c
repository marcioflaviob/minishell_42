/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 22:23:53 by mbrandao          #+#    #+#             */
/*   Updated: 2024/04/22 18:23:59 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_sp(char **args, t_sh *sh)
{
	int	i;
	int	j;

	
	i = 0;
	j = sh->position;
	while (args[i])
	{
		if ((args[i][0] == '<' && sh->sp_bool[j] == 1) || (args[i][0] == '>' && sh->sp_bool[j] == 1) || (args[i][0] == '|' && sh->sp_bool[j] == 1))
			return (i);
		if ((ft_equalstr(args[i], "<<") && sh->sp_bool[j] == 1) || (ft_equalstr(args[i], ">>") && sh->sp_bool[j] == 1) || (ft_equalstr(args[i], "&&") && sh->sp_bool[j] == 1))
			return (i);
		i++;
		j++;
	}
	return (0);
}

int	find_sp_par(char **args, t_sh *sh)
{
	int	i;
	int	j;

	
	i = 0;
	j = sh->position;
	while (args[i])
	{
		if ((args[i][0] == '<' && sh->sp_bool[j] == 1) || (args[i][0] == '>' && sh->sp_bool[j] == 1) || (args[i][0] == '|' && sh->sp_bool[j] == 1) || (args[i][0] == ')' && sh->sp_bool[j] == 1))
			return (i);
		if ((ft_equalstr(args[i], "<<") && sh->sp_bool[j] == 1) || (ft_equalstr(args[i], ">>") && sh->sp_bool[j] == 1) || (ft_equalstr(args[i], "&&") && sh->sp_bool[j] == 1))
			return (i);
		i++;
		j++;
	}
	return (0);
}

int    find_sp_str(char *str)
{
    int    i;

    i = 0;
    if (ft_int_strstr_wc(str, "<<") != -1)
        return (ft_int_strstr_wc(str, "<<"));
    else if (ft_int_strstr_wc(str, ">>") != -1)
        return (ft_int_strstr_wc(str, ">>"));
    else if (ft_int_strstr_wc(str, "||") != -1)
        return (ft_int_strstr_wc(str, "||"));
    else if (ft_int_strstr_wc(str, "&&") != -1)
        return (ft_int_strstr_wc(str, "&&"));
    else if (ft_equalstr(str, "(") || ft_equalstr(str, ")"))
        return (0);
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
	sp_index = find_sp_par(args, sh);
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

//void	run_builtin(char *str, char **args, t_sh *sh)
//{
//	//if (ft_equalstr(str, "echo"))
//	//	echo(args, sh);
//	//else if (ft_equalstr(str, "cd"))
//	//{
//	//	if (find_sp(args, sh) > 2)
//	//		ft_putstr_fd("cd: too many arguments\n", 2);
//	//	else if (!ft_equalstr(args[find_sp(args, sh)], "|"))
//	//		cd(sh, args[1]);
//	//}
//	//else if (ft_equalstr(str, "pwd"))
//	//	pwd();
//	//else if (ft_equalstr(str, "export"))
//	//	export(sh, &args[1]);
//	//else if (ft_equalstr(str, "unset"))
//	//	un_set(sh, &args[1]);
//	//else if (ft_equalstr(str, "env"))
//	//	env(sh);
//}

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
	pid_t	pid2;
	int		i;
	char	*str;
	char	**cmd;

	i = 0;
	if (!args[0])
	{
		
	}
	pipe(sh->pipe);
	pid = fork();
	if (pid == 0)
	{
		if (is_builtin(args[0]))
			exit(EXIT_SUCCESS);
		else
		{
			if (find_sp(args, sh))
			{
				if (ft_equalstr(args[find_sp(args, sh)], "<"))
				{
					//run_builtin(args[0], args, sh);
					rm_tab_line(&sh->args, sh->args[find_sp(args, sh)]);
					rm_tab_line(&sh->args, sh->args[find_sp(args, sh) + 1]);
					if (sh->fd_input != -2)
						close(sh->fd_input);
					if (sh->fd_output != -2)
						close(sh->fd_output);
					close(sh->pipe[0]);
					close(sh->pipe[1]);
					exit(0);
				}
				else if (ft_equalstr(args[find_sp(args, sh)], ">"))
				{
					i = find_sp(args, sh);
					if (sh->out_par)
						(dup2(sh->fd_output, STDOUT_FILENO), close(sh->fd_output));
					else
						redir_out_trunc(args[find_sp(args, sh) + 1], &args[find_sp(args, sh)], sh);
					if (!find_sp(&args[find_sp(args, sh) + 1], sh))
						;
					else if (ft_equalstr(args[find_sp(&args[find_sp(args, sh) + 1], sh) + i + 1], "|") && find_sp(&args[find_sp(args, sh) + 1], sh) + i + 1 != check_sp_afpar(args))
					{
						pid2 = fork();
						if (pid2 == 0)
						{
							dup2(sh->true_stdout, STDOUT_FILENO);
							dup2(sh->pipe[1], STDOUT_FILENO);
							if (sh->fd_input != -2)
								close(sh->fd_input);
							close(sh->pipe[0]);
							close(sh->pipe[1]);
							cmd = cmd_args(sh, args);
							execve(cmd[0], cmd, NULL);
							//cmd didn't execute
							exit(EXIT_FAILURE);
							
						}
						else
							waitpid(pid2, &sh->last_cmd_st, 0);
					}
					if (sh->fd_input != -2)
						close(sh->fd_input);
					close(sh->pipe[0]);
					close(sh->pipe[1]);
					cmd = cmd_args(sh, args);
					execve(cmd[0], cmd, NULL);
					//cmd didn't execute
					exit(EXIT_FAILURE);
				}
				else if (ft_equalstr(args[find_sp(args, sh)], ">>"))
				{
					i = find_sp(args, sh);
					if (sh->out_par)
						(dup2(sh->fd_output, STDOUT_FILENO), close(sh->fd_output));
					else
						redir_out_trunc(args[find_sp(args, sh) + 1], &args[find_sp(args, sh)], sh);
					if (!find_sp(&args[find_sp(args, sh) + 1], sh))
						;
					else if (ft_equalstr(args[find_sp(&args[find_sp(args, sh) + 1], sh) + i + 1], "|") && find_sp(&args[find_sp(args, sh) + 1], sh) + i + 1 != check_sp_afpar(args))
					{
						pid2 = fork();
						if (pid2 == 0)
						{
							dup2(sh->true_stdout, STDOUT_FILENO);
							dup2(sh->pipe[1], STDOUT_FILENO);
							if (sh->fd_input != -2)
								close(sh->fd_input);
							close(sh->pipe[0]);
							close(sh->pipe[1]);
							cmd = cmd_args(sh, args);
							execve(cmd[0], cmd, NULL);
							//cmd didn't execute
							exit(EXIT_FAILURE);
							
						}
						else
							waitpid(pid2, &sh->last_cmd_st, 0);
					}
					else if (ft_equalstr(args[find_sp(&args[find_sp(args, sh) + 1], sh) + i + 1], "|") && find_sp(&args[find_sp(args, sh) + 1], sh) + i + 1 == check_sp_afpar(args))
					{
						write(sh->pipe_par[1], "", 0);
						close(sh->pipe_par[0]);
						close(sh->pipe_par[1]);
					}
					if (sh->fd_input != -2)
						close(sh->fd_input);
					close(sh->pipe[0]);
					close(sh->pipe[1]);
					cmd = cmd_args(sh, args);
					execve(cmd[0], cmd, NULL);
					//cmd didn't execute
					exit(EXIT_FAILURE);
				}
				else if (ft_equalstr(args[find_sp(args, sh)], "|"))
				{
					if (sh->fd_input != -2)
						close(sh->fd_input);
					if (sh->fd_output != -2)
						close(sh->fd_output);
					if (sh->pipe_par_bool == find_sp(args, sh) + sh->position)
					{
						dup2(sh->pipe_par[1], STDOUT_FILENO);
						close(sh->pipe_par[1]);
						close(sh->pipe_par[0]);
					}
					else
					{
						dup2(sh->pipe[1], STDOUT_FILENO);
						close(sh->pipe[1]);
						close(sh->pipe[0]);	
					}
					close(sh->pipe[1]);
					close(sh->pipe[0]);
					cmd = cmd_args(sh, args);
					if (sh->wrong_file != NULL)
						add_to_tab(&cmd, sh->wrong_file);
					execve(cmd[0], cmd, NULL);
				}
				else if (ft_equalstr(args[find_sp(args, sh)], "&&"))
				{
					if (sh->fd_input != -2)
						close(sh->fd_input);
					if (sh->pipe_par_bool)
					{
						dup2(sh->pipe_par[1], STDOUT_FILENO);
						close(sh->pipe_par[1]);
						close(sh->pipe_par[0]);
					}
					else if (sh->out_par)
						dup2(sh->fd_output, STDOUT_FILENO);
					if (sh->fd_output != -2)
						close(sh->fd_output);
					close(sh->pipe[0]);
					close(sh->pipe[1]);
					cmd = cmd_args(sh, args);
					execve(cmd[0], cmd, NULL);
					//cmd didn't execute
					exit(EXIT_FAILURE);
				}
				else if (ft_equalstr(args[find_sp(args, sh)], "||"))
				{
					if (sh->fd_input != -2)
						close(sh->fd_input);
					if (sh->pipe_par_bool)
					{
						dup2(sh->pipe_par[1], STDOUT_FILENO);
						close(sh->pipe_par[1]);
						close(sh->pipe_par[0]);
					}
					else if (sh->out_par)
						dup2(sh->fd_output, STDOUT_FILENO);
					if (sh->fd_output != -2)
						close(sh->fd_output);
					close(sh->pipe[0]);
					close(sh->pipe[1]);
					cmd = cmd_args(sh, args);
					execve(cmd[0], cmd, NULL);
					//cmd didn't execute
					exit(EXIT_FAILURE);
				}
			}
			else
			{
				dup2(sh->true_stdout, STDOUT_FILENO);
				if (sh->fd_input != -2)
					close(sh->fd_input);
				if (sh->op_pipe)
				{
					close(sh->pipe_par[1]);
					close(sh->pipe_par[0]);
				}
				if (sh->out_par)
					dup2(sh->fd_output, STDOUT_FILENO);
				if (sh->fd_output != -2)
					close(sh->fd_output);
				close(sh->pipe[0]);
				cmd = cmd_args(sh, args);
				execve(cmd[0], cmd, NULL);
				//cmd didn't execute
				exit(EXIT_FAILURE);
			}
		}
	}
	else
	{
		i = find_sp(args, sh);
		if (is_builtin(args[0]))
		{
			if (ft_equalstr(args[0], "exit"))
			{
				if (!args[1])
				{
					printf("exit");
					exit(0);
				}
				else
				{
					printf("exit");
					exit(ft_atoi(args[1]));
				}
				if (ft_equalstr(args[find_sp(args, sh)], "|"))
				{
					if (sh->position + find_sp(args, sh) == sh->pipe_par_bool)
					{
						pipe(sh->pipe_par);
						write(sh->pipe_par[1], "\x04", 1);
						close(sh->pipe_par[1]);
					}
					else
					{
						pipe(sh->pipe);
						write(sh->pipe[1], "\x04", 1);
						close(sh->pipe[1]);
					}
				}
				if (find_sp(args, sh) == 0)
					sh->position = tab_len(sh->args) - 1;
				else
					sh->position += find_sp_par(args, sh);
			}
			else if (ft_equalstr(args[0], "unset"))
			{
				un_set(sh, &args[1]);
				if (ft_equalstr(args[find_sp(args, sh)], "|"))
				{
					if (sh->position + find_sp(args, sh) == sh->pipe_par_bool)
					{
						pipe(sh->pipe_par);
						write(sh->pipe_par[1], "\x04", 1);
						close(sh->pipe_par[1]);
					}
					else
					{
						pipe(sh->pipe);
						write(sh->pipe[1], "\x04", 1);
						close(sh->pipe[1]);
					}
				}
				if (find_sp(args, sh) == 0)
					sh->position = tab_len(sh->args) - 1;
				else
					sh->position += find_sp_par(args, sh);
			}
			else if (ft_equalstr(args[0], "env"))
			{
				if (ft_equalstr(args[find_sp(args, sh)], "|"))
				{
					i = 0;
					if (sh->position + find_sp(args, sh) == sh->pipe_par_bool)
					{
						pipe(sh->pipe_par);
						while (sh->env[i])
							(ft_putstr_fd(sh->env[i++], sh->pipe_par[1]), write(sh->pipe_par[1], "\n", 1));
						write(sh->pipe_par[1], "\x04", 1);
						close(sh->pipe_par[1]);
					}
					else
					{
						pipe(sh->pipe);
						while (sh->env[i])
							(ft_putstr_fd(sh->env[i++], sh->pipe[1]), write(sh->pipe[1], "\n", 1));
						write(sh->pipe[1], "\x04", 1);
						close(sh->pipe[1]);
					}
					if (find_sp(args, sh) == 0)
						sh->position = tab_len(sh->args) - 1;
					else
						sh->position += find_sp_par(args, sh);
				}
				else if (ft_equalstr(args[find_sp(args, sh)], ">"))
				{
					//if (sh->out_par)
					//	dup2(sh->fd_output, STDOUT_FILENO);
					//else
					{	sh->fd_output = open(args[find_sp(args, sh) + 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
						if (sh->fd_output == -1)
							printf("Couldn't open file.");
					}
					i = -1;
					while (sh->env[++i] != NULL)
					{
						write(sh->fd_output, sh->env[i], ft_strlen(sh->env[i]));
						write(sh->fd_output, "\n", 1);
					}
					close(sh->fd_output);
					if (find_sp(args, sh) == 0)
						sh->position = tab_len(sh->args) - 1;
					else
						sh->position += find_sp(args, sh) + 2;
				}
				else if (ft_equalstr(args[find_sp(args, sh)], ">>"))
				{
					//if (sh->out_par)
					//	dup2(sh->fd_output, STDOUT_FILENO);
					//else
					{	sh->fd_output = open(args[find_sp(args, sh) + 1], O_WRONLY | O_CREAT | O_APPEND, 0666);
						if (sh->fd_output == -1)
							printf("Couldn't open file.");
					}
					write(sh->fd_output, str, ft_strlen(str));
					write(sh->fd_output,"\n", 1);
					close(sh->fd_output);
					if (find_sp(args, sh) == 0)
						sh->position = tab_len(sh->args) - 1;
					else
						sh->position += find_sp(args, sh) + 2;
				}
				else
				{
					env(sh);
					if (find_sp(args, sh) == 0)
						sh->position = tab_len(sh->args) - 1;
					else
						sh->position += find_sp_par(args, sh);
				}
			}
			else if (ft_equalstr(args[0], "export"))
			{
				export(sh, &args[1]);
				if (ft_equalstr(args[find_sp(args, sh)], "|"))
				{
					if (sh->position + find_sp(args, sh) == sh->pipe_par_bool)
					{
						pipe(sh->pipe_par);
						write(sh->pipe_par[1], "\x04", 1);
						close(sh->pipe_par[1]);
					}
					else
					{
						pipe(sh->pipe);
						write(sh->pipe[1], "\x04", 1);
						close(sh->pipe[1]);
					}
				}
				if (find_sp(args, sh) == 0)
					sh->position = tab_len(sh->args) - 1;
				else
					sh->position += find_sp_par(args, sh);
			}
			else if (ft_equalstr(args[0], "pwd"))
			{
				str = get_cwd();
				if (ft_equalstr(args[find_sp(args, sh)], "|"))
				{
					i = 0;
					if (sh->position + find_sp(args, sh) == sh->pipe_par_bool)
					{
						pipe(sh->pipe_par);
						write(sh->pipe_par[1], str, ft_strlen(str));
						write(sh->pipe_par[1],"\n", 1);
						write(sh->pipe_par[1], "\x04", 1);
						close(sh->pipe_par[1]);
					}
					else
					{
						pipe(sh->pipe);
						write(sh->pipe[1], str, ft_strlen(str));
						write(sh->pipe[1],"\n", 1);
						write(sh->pipe[1], "\x04", 1);
						close(sh->pipe[1]);
					}
					if (find_sp(args, sh) == 0)
						sh->position = tab_len(sh->args) - 1;
					else
						sh->position += find_sp_par(args, sh);
				}
				else if (ft_equalstr(args[find_sp(args, sh)], ">"))
				{
					//if (sh->out_par)
					//	dup2(sh->fd_output, STDOUT_FILENO);
					//else
					{	sh->fd_output = open(args[find_sp(args, sh) + 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
						if (sh->fd_output == -1)
							printf("Couldn't open file.");
					}
					write(sh->fd_output, str, ft_strlen(str));
					write(sh->fd_output,"\n", 1);
					close(sh->fd_output);
					if (find_sp(args, sh) == 0)
						sh->position = tab_len(sh->args) - 1;
					else
						sh->position += find_sp(args, sh) + 2;
				}
				else if (ft_equalstr(args[find_sp(args, sh)], ">>"))
				{
					//if (sh->out_par)
					//	dup2(sh->fd_output, STDOUT_FILENO);
					//else
					{	sh->fd_output = open(args[find_sp(args, sh) + 1], O_WRONLY | O_CREAT | O_APPEND, 0666);
						if (sh->fd_output == -1)
							printf("Couldn't open file.");
					}
					write(sh->fd_output, str, ft_strlen(str));
					write(sh->fd_output,"\n", 1);
					close(sh->fd_output);
					if (find_sp(args, sh) == 0)
						sh->position = tab_len(sh->args) - 1;
					else
						sh->position += find_sp(args, sh) + 2;
				}
				else
				{
					pwd();
					if (find_sp(args, sh) == 0)
						sh->position = tab_len(sh->args) - 1;
					else
						sh->position += find_sp_par(args, sh);
				}
				free(str);
			}
			else if (ft_equalstr(args[0], "cd"))
			{
				if (find_sp(args, sh) > 2)
				{
					ft_putstr_fd("cd: too many arguments\n", 2);
					sh->bool_result = 0;
				}
				else if (!ft_equalstr(args[find_sp(args, sh)], "|"))
					sh->bool_result = cd(sh, args[1]);
				else
				{
					if (sh->position + find_sp(args, sh) == sh->pipe_par_bool)
					{
						pipe(sh->pipe_par);
						write(sh->pipe_par[1], "\x04", 1);
						close(sh->pipe_par[1]);
					}
					else
					{
						pipe(sh->pipe);
						write(sh->pipe[1], "\x04", 1);
						close(sh->pipe[1]);
					}
				}
				if (find_sp(args, sh) == 0)
					sh->position = tab_len(sh->args) - 1;
				else
					sh->position += find_sp_par(args, sh);
			}
			else if (ft_equalstr(args[0], "echo"))
			{
				str = echo(args, sh);
				if (ft_equalstr(args[find_sp(args, sh)], "|"))
				{
					i = 0;
					if (sh->position + find_sp(args, sh) == sh->pipe_par_bool)
					{
						pipe(sh->pipe_par);
						write(sh->pipe_par[1], str, ft_strlen(str));
						write(sh->pipe_par[1], "\x04", 1);
						close(sh->pipe_par[1]);
					}
					else
					{
						pipe(sh->pipe);
						write(sh->pipe[1], str, ft_strlen(str));
						write(sh->pipe[1], "\x04", 1);
						close(sh->pipe[1]);
					}
					if (find_sp(args, sh) == 0)
						sh->position = tab_len(sh->args) - 1;
					else
						sh->position += find_sp_par(args, sh);
				}
				else if (ft_equalstr(args[find_sp(args, sh)], ">"))
				{
					//if (sh->out_par)
					//	dup2(sh->fd_output, STDOUT_FILENO);
					//else
					{	sh->fd_output = open(args[find_sp(args, sh) + 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
						if (sh->fd_output == -1)
							printf("Couldn't open file.");
					}
					write(sh->fd_output, str, ft_strlen(str));
					close(sh->fd_output);
					if (find_sp(args, sh) == 0)
						sh->position = tab_len(sh->args) - 1;
					else
						sh->position += find_sp(args, sh) + 2;
				}
				else if (ft_equalstr(args[find_sp(args, sh)], ">>"))
				{
					//if (sh->out_par)
					//	dup2(sh->fd_output, STDOUT_FILENO);
					//else
					{	sh->fd_output = open(args[find_sp(args, sh) + 1], O_WRONLY | O_CREAT | O_APPEND, 0666);
						if (sh->fd_output == -1)
							printf("Couldn't open file.");
					}
					write(sh->fd_output, str, ft_strlen(str));
					close(sh->fd_output);
					if (find_sp(args, sh) == 0)
						sh->position = tab_len(sh->args) - 1;
					else
						sh->position += find_sp(args, sh) + 2;
				}
				else
				{
					printf("%s", str);
					if (find_sp(args, sh) == 0)
						sh->position = tab_len(sh->args) - 1;
					else
						sh->position += find_sp_par(args, sh);
				}
				free(str);
			}
		}
		else if (!find_sp(args, sh))
		{
			waitpid(pid, &sh->last_cmd_st, 0);
			close(sh->pipe[1]);
			close(sh->pipe[0]);
			sh->position = tab_len(sh->args) - 1;
		}
		else
		{
			if (ft_equalstr(args[find_sp(args, sh)], ">"))
			{
				if (ft_equalstr(args[find_sp(&args[find_sp(args, sh) + 1], sh) + i + 1], "|"))
				{
					sh->position += find_sp(&args[find_sp(args, sh) + 1], sh) + i + 1;
					close(sh->pipe[1]);
					if (sh->pipe_par_bool)
						close(sh->pipe_par[1]);
				}
				else
				{
					waitpid(pid, &sh->last_cmd_st, 0);
					if (sh->last_cmd_st != 0)
						sh->bool_result = 0;
					else if (sh->last_cmd_st == 0)
						sh->bool_result = 1;
					if (sh->position + find_sp(args, sh) == sh->out_par)
						(close(sh->fd_output), sh->out_par = 0);
					if (find_sp(&args[find_sp(args, sh) + 1], sh) == 0)
						sh->position = tab_len(sh->args) - 1;
					else
						
						sh->position += find_sp_par(&args[find_sp_par(args, sh) + 1], sh) + find_sp_par(args, sh) + 1;
				}
			}
			else if (ft_equalstr(args[find_sp(args, sh)], ">>"))
			{
				if (ft_equalstr(args[find_sp(&args[find_sp(args, sh) + 1], sh) + i + 1], "|"))
				{
					sh->position += find_sp(&args[find_sp(args, sh) + 1], sh) + i + 1;
					close(sh->pipe[1]);
					if (sh->pipe_par_bool)
						close(sh->pipe_par[1]);
				}
				else
				{
					waitpid(pid, &sh->last_cmd_st, 0);
					if (sh->last_cmd_st != 0)
						sh->bool_result = 0;
					else if (sh->last_cmd_st == 0)
						sh->bool_result = 1;
					if (sh->position + find_sp(args, sh) == sh->out_par)
						(close(sh->fd_output), sh->out_par = 0);
					if (find_sp(&args[find_sp(args, sh) + 1], sh) == 0)
						sh->position = tab_len(sh->args) - 1;
					else			
						sh->position += find_sp_par(&args[find_sp_par(args, sh) + 1], sh) + find_sp_par(args, sh) + 1;
				}
			}
			else if (ft_equalstr(args[find_sp(args, sh)], "<"))
				sh->position += find_sp(args, sh) + 1;
			else if (ft_equalstr(args[find_sp(args, sh)], "|"))
			{
				close(sh->pipe[1]);
				if (sh->position + find_sp(args, sh) == sh->pipe_par_bool)
					close(sh->pipe_par[1]);
				sh->position += find_sp(args, sh);
			}
			else if (ft_equalstr(args[find_sp(args, sh)], "||"))
			{
				waitpid(pid, &sh->last_cmd_st, 0);
				if (sh->last_cmd_st != 0)
				{
					sh->bool_result = 0;
					//if (find_sp(&args[find_sp(args, sh) + 1], sh) == 0)
					//	sh->position = tab_len(sh->args) - 1;
					sh->position += find_sp_par(args, sh);
				}
				else
				{
					sh->bool_result = 1;
					//if (find_sp(&args[find_sp(args, sh) + 1], sh) == 0)
					//	sh->position = tab_len(sh->args) - 1;
					sh->position += find_sp_par(args, sh);
				}
			}
			else if (ft_equalstr(args[find_sp(args, sh)], "&&"))
			{
				waitpid(pid, &sh->last_cmd_st, 0);
				if (sh->last_cmd_st != 0)
				{
					sh->bool_result = 0;
					//if (find_sp(&args[find_sp(args, sh) + 1], sh) == 0)
					//	sh->position = tab_len(sh->args) - 1;
					sh->position += find_sp_par(args, sh);
				}
				else
				{
					sh->bool_result = 1;
					//if (find_sp(&args[find_sp(args, sh) + 1], sh) == 0)
					//	sh->position = tab_len(sh->args) - 1;					
					sh->position += find_sp_par(args, sh);
				}
			}
		}
	}
}