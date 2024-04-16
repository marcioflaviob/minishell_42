/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 18:55:56 by mbrandao          #+#    #+#             */
/*   Updated: 2024/04/16 19:51:17 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_find_first(const char *s, int c)
 {
 	int	i;

 	i = 0;
 	while (s[i])
 	{
 		if (s[i] == (unsigned char)c)
 			return (i);
 		i++;
 	}
 	return (0);
}

int	arg_checker(char *str)
{
 	char	*sub;

 	if (!ft_find_first(str, '='))
 		return (0);
 	sub = get_substring_b(str, '=');
 	if (ft_find_first(sub, '\'') || ft_find_first(sub, '"'))
 		return (0);
 	return (1);
}

int	check_special(char *str, t_sh *sh)
{
 	if (ft_equalstr(str, ">") && sh->sp_bool[sh->position] == 1)
 		return (1);
 	else if (ft_equalstr(str, ">>") && sh->sp_bool[sh->position] == 1)
 		return (2);
 	else if (ft_equalstr(str, "<") && sh->sp_bool[sh->position] == 1)
 		return (3);
 	else if (ft_equalstr(str, "<<") && sh->sp_bool[sh->position] == 1)
 		return (4);
 	else if (ft_equalstr(str, "|") && sh->sp_bool[sh->position] == 1)
 		return (5);
 	else if (ft_equalstr(str, "||") && sh->sp_bool[sh->position] == 1)
 		return (6);
 	else if (ft_equalstr(str, "&&") && sh->sp_bool[sh->position] == 1)
 		return (7);
 	return (0);
}

int	check_sp_afpar(char **args)
{
	int	i;
	int	par;

	i = 1;
	par = 1;
	while (par != 0 && args[i])
	{
		if (args[i][0] == '(')
			par++;
		else if (args[i][0] == ')')
			par--;
		i++;
		
	}
	while (args[i] && args[i][0] == ')')
		i++;
	if (ft_equalstr(args[i], "|") || ft_equalstr(args[i], ">") || ft_equalstr(args[i], ">>") || ft_equalstr(args[i], "||") || ft_equalstr(args[i], "&&"))
		return (i);
	else if (args[i])
		return (printf("minishell: parse error near `%s\'", args[i]), -1);
	return (0);
}

int	go_af_par(char **args)
{
	int	i;
	int	par;

	i = 1;
	par = 1;
	while (par != 0 && args[i])
	{
		if (args[i][0] == '(')
			par++;
		else if (args[i][0] == ')')
			par--;
		i++;
		
	}
	if (args[i - 1][0] != ')')
		return (0);
	return (i);
}

void	arg(t_sh *sh)
{
	int		special;
	int		fd;
	char	*buffer;

	fd = 0;
	if (sh->position == tab_len(sh->args) - 1)
		get_input(sh);	
	else
	{
		special = check_special(sh->args[sh->position], sh);
		if (arg_checker(sh->args[sh->position]) && !special)
			sh->position++;
		else if (special && !sh->args[sh->position + 1])
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
			ft_putstr_fd(sh->args[sh->position], 2);
			ft_putstr_fd("\n", 2);
			sh->position = tab_len(sh->args) - 1;
		}
		else if (special && sh->args[sh->position + 1])
		{
			if (special == 1)
			{
				dup2(sh->true_stdout, STDOUT_FILENO);
				redir_out_trunc_p(sh->args[sh->position + 1], &sh->args[sh->position], sh);
				sh->position += 2;
				exec_cmd(&sh->args[sh->position], sh);
			}
			else if (special == 2)
			{
				dup2(sh->true_stdout, STDOUT_FILENO);
				redir_out_app_p(sh->args[sh->position + 1], &sh->args[sh->position], sh);
				sh->position += 2;
				exec_cmd(&sh->args[sh->position], sh);
			}
			else if (special == 3 && !sh->args[sh->position + 2])
			{
				dup2(sh->true_stdin, STDIN_FILENO);
				redir_in(sh->args[sh->position + 1], &sh->args[0], sh);
			}
			else if (special == 3 && sh->args[sh->position + 2])
			{
				dup2(sh->true_stdin, STDIN_FILENO);
				fd = open(sh->args[sh->position + 1], O_RDONLY);
				if ((!find_sp(&sh->args[sh->position + 1], sh) || !ft_equalstr(sh->args[find_sp(&sh->args[sh->position + 1], sh) + 1], "|")) && (fd == -1))
				{
					ft_putstr_fd("minishell: no such file or directory: ", 2);
					ft_putstr_fd(sh->args[sh->position + 1], 2);
					ft_putstr_fd("\n", 2);
					sh->position = tab_len(sh->args) - 1;
				}
				else
				{
					if (fd != -1)
						close(fd);
					redir_in(sh->args[sh->position + 1], &sh->args[sh->position], sh);
					sh->position += 2;
					exec_cmd(&sh->args[sh->position], sh);
					free(sh->wrong_file);
					sh->wrong_file = NULL;
				}
			}
			else if (special == 4)
			{
				dup2(sh->true_stdin, STDIN_FILENO);
				dup2(sh->true_stdout, STDOUT_FILENO);
				pipe(sh->pipe);
				buffer = redir_in_heredoc(sh->args[sh->position + 1]);
				write(sh->pipe[1], buffer, ft_strlen(buffer));
				close(sh->pipe[1]);
				free(buffer);
				dup2(sh->pipe[0], STDIN_FILENO);
				close(sh->pipe[0]);
				sh->position += 2;
				exec_cmd(&sh->args[sh->position], sh);
			}
			else if (special == 5)
			{
				dup2(sh->true_stdin, STDIN_FILENO);
				dup2(sh->true_stdout, STDOUT_FILENO);
				if (sh->position == sh->pipe_par_bool)
				{
					sh->pipe_par_bool = 0;
					close(sh->pipe_par[1]);
					dup2(sh->pipe_par[0], STDIN_FILENO);
					close(sh->pipe_par[0]);	
				}
				else
				{
					dup2(sh->pipe[0], STDIN_FILENO);
					close(sh->pipe[0]);
				}
				sh->position++;
			}
			else if (special == 6)
			{
				if (sh->bool_result == 1)
				{
					if (find_sp(&sh->args[sh->position + 1], sh) == 0)
						sh->position = tab_len(sh->args) - 1;
					else
					{
						if (sh->args[sh->position + 1][0] == '(')
							sh->position += check_sp_afpar(&sh->args[sh->position + 1]);
						else
							sh->position += find_sp(&sh->args[sh->position + 1], sh) + 1;
					}
				}
				else
					sh->position++;
			}
			else if (special == 7)
			{
				if (sh->bool_result == 0)
				{
					while (sh->args[sh->position])
					{
						if (sh->args[sh->position][0] == '(')
							sh->position += go_af_par(&sh->args[sh->position]);
						if (ft_equalstr(sh->args[sh->position], "||"))
							break;
						sh->position++;
					}
					if (sh->position == tab_len(sh->args))
						sh->position = tab_len(sh->args) - 1;
				}
				else
					sh->position++;
			}
		}
		else if (ft_equalstr(sh->args[sh->position], "("))
		{
			sh->inside_par++;
			if (go_af_par(&sh->args[sh->position]) > 0)
			{
				if (ft_equalstr(sh->args[check_sp_afpar(&sh->args[sh->position]) + sh->position], "|") && !sh->pipe_par_bool)
				{
					pipe(sh->pipe_par);
					sh->op_pipe = 1;
					sh->pipe_par_bool = check_sp_afpar(&sh->args[sh->position]) + sh->position;
				}
				else if (ft_equalstr(sh->args[check_sp_afpar(&sh->args[sh->position]) + sh->position], ">"))
				{
					sh->fd_output = open(sh->args[check_sp_afpar(&sh->args[sh->position]) + 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
					sh->out_par = check_sp_afpar(&sh->args[sh->position]) + sh->position;
				}
				else if (ft_equalstr(sh->args[check_sp_afpar(&sh->args[sh->position]) + sh->position], ">>"))
				{
					sh->fd_output = open(sh->args[check_sp_afpar(&sh->args[sh->position]) + 1], O_WRONLY | O_CREAT | O_APPEND, 0666);
					sh->out_par = check_sp_afpar(&sh->args[sh->position]) + sh->position;
				}
			}
			//else if (check_sp_afpar(&sh->args[sh->position]) == -1)
			//	sh->position = tab_len(sh->args);
			sh->position++;
		}
		else if (ft_equalstr(sh->args[sh->position], ")"))
		{
			sh->inside_par--;
			sh->position++;
		}
		else
			exec_cmd(&sh->args[sh->position], sh);
		arg(sh);
	}
}

