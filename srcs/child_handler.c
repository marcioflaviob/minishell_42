/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 19:03:47 by trimize           #+#    #+#             */
/*   Updated: 2024/05/13 19:06:53 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	child_cmd_handler(t_sh *sh, t_exe *exe, char **args)
{
	before_command();
	if (is_builtin(args[0]))
		exit(EXIT_SUCCESS);
	if (find_sp(args, sh))
	{
		if (ft_equalstr(args[find_sp(args, sh)], "<"))
			exec_cmd_2(sh, args);
		else if (ft_equalstr(args[find_sp(args, sh)], ">"))
			exec_cmd_4(sh, exe, args);
		else if (ft_equalstr(args[find_sp(args, sh)], ">>"))
			exec_cmd_6(sh, exe, args);
		else if (ft_equalstr(args[find_sp(args, sh)], "|"))
			exec_cmd_7(sh, exe, args);
		else if (ft_equalstr(args[find_sp(args, sh)], "&&"))
			exec_cmd_8(sh, exe, args);
		else if (ft_equalstr(args[find_sp(args, sh)], "||"))
			exec_cmd_9(sh, exe, args);
	}
	else
		exec_cmd_10(sh, exe, args);
}
