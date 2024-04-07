/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 18:55:56 by mbrandao          #+#    #+#             */
/*   Updated: 2024/04/04 17:05:14 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	ft_find_first(const char *s, int c)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == (unsigned char)c)
// 			return (i);
// 		i++;
// 	}
// 	return (0);
// }

// int	arg_checker(char *str)
// {
// 	char	*sub;

// 	if (!ft_find_first(str, '='))
// 		return (0);
// 	sub = get_substring_b(str, '=');
// 	if (ft_find_first(sub, '\'') || ft_find_first(sub, '"'))
// 		return (0);
// 	return (1);
// }

// int	check_special(char *str)
// {
// 	if (ft_equalstr(str, ">"))
// 		return (1);
// 	else if (ft_equalstr(str, ">>"))
// 		return (2);
// 	else if (ft_equalstr(str, "<"))
// 		return (3);
// 	else if (ft_equalstr(str, "<<"))
// 		return (4);
// 	else if (ft_equalstr(str, "|"))
// 		return (5);
// 	else if (ft_equalstr(str, "||"))
// 		return (6);
// 	else if (ft_equalstr(str, "&&"))
// 		return (7);
// 	return (0);
// }

// void	first_arg(t_sh *sh)
// {
// 	int		special;
// 	char	*tmp;
// 	char	*substr;

// 	special = check_special(sh->args[0]);
// 	if (arg_checker(sh->args[0]) && !special)
// 	{
// 		quotes_removal_helper(&(sh->args[0]));
// 		substr = get_substring_b(sh->args[0], '=');
// 		tmp = get_env(substr, sh);
// 		if (tmp)
// 			(free(tmp), free(substr), export(sh, sh->args[0]));
// 		else
// 			add_to_tab(&sh->variables, sh->args[0]);
// 	}
// 	else if (special && sh->args[1])
// 	{
// 		if (special == 1)
// 			redir_out_trunc(1, sh->args[1]);
// 		if (special == 2)
// 			redir_out_app(1, sh->args[1]);
// 		if (special == 3 && !sh->args[2])
// 			redir_in(sh->args[1], &sh->args[0]);
// 		else if (special == 3 && sh->args[2])
// 			redir_in(1, &sh->args[0]);
// 	}
// 	else if (special && !sh->args[1])
// 		ft_putstr_fd("minishell: syntax error near unexpected token `", STDERR);
// }
