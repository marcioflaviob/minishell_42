/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 18:55:56 by mbrandao          #+#    #+#             */
/*   Updated: 2024/04/08 16:39:54 by trimize          ###   ########.fr       */
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

void	arg(t_sh *sh)
{
	int		special;
	int		fd;
	char	*buffer;

	fd = 0;
	dup2(sh->true_stdin, STDIN_FILENO);
	dup2(sh->true_stdout, STDOUT_FILENO);
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
				redir_out_trunc_p(sh->args[sh->position + 1], &sh->args[sh->position], sh);
				sh->position += 2;
				exec_cmd(&sh->args[sh->position], sh);
			}
			else if (special == 2)
			{
				redir_out_app_p(sh->args[sh->position + 1], &sh->args[sh->position], sh);
				sh->position += 2;
				exec_cmd(&sh->args[sh->position], sh);
			}
			else if (special == 3 && !sh->args[sh->position + 2])
				redir_in(sh->args[sh->position + 1], &sh->args[0], sh);
			else if (special == 3 && sh->args[sh->position + 2])
			{
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
				sh->position++;
				dup2(sh->pipe[0], STDIN_FILENO);
				close(sh->pipe[0]);
				exec_cmd(&sh->args[sh->position], sh);
			}
			else if (special == 6)
			{
				if (sh->last_cmd_st == 0)
				{
					if (find_sp(&sh->args[sh->position + 1], sh) == 0)
						sh->position = tab_len(sh->args) - 1;
					else
						sh->position += find_sp(&sh->args[sh->position], sh);
				}
				else
					sh->position++;
			}
			else if (special == 7)
			{
				if (sh->last_cmd_st != 0)
					sh->position = tab_len(sh->args) - 1;
				else
					sh->position++;
			}
			else if (special == 8)
				exec_cmd(&sh->args[sh->position], sh);
		}
		else
			exec_cmd(&sh->args[sh->position], sh);
		arg(sh);
	}
}

