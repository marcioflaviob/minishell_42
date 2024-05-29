/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 22:23:53 by mbrandao          #+#    #+#             */
/*   Updated: 2024/05/29 13:20:56 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	if (!temp)
	{
		child_free(sh);
		exit(127);
	}
	add_to_tab(&tab, temp);
	free(temp);
	while (i < sp_index && args[i])
		add_to_tab(&tab, args[i++]);
	return (tab);
}

void	builtin_handler(t_sh *sh, t_exe *exe, char **args)
{
	if (ft_equalstr(args[0], "exit"))
		exit_parent(sh, exe, args);
	else if (ft_equalstr(args[0], "unset"))
		unset_parent(sh, args);
	else if (ft_equalstr(args[0], "env"))
		env_parent_7(sh, exe, args);
	else if (ft_equalstr(args[0], "export"))
		export_parent_4(sh, exe, args);
	else if (ft_equalstr(args[0], "pwd"))
		pwd_parent_5(sh, exe, args);
	else if (ft_equalstr(args[0], "cd"))
		cd_parent_2(sh, args);
	else if (ft_equalstr(args[0], "echo"))
		echo_parent_4(sh, exe, args);
}

void	exec_cmd(char **args, t_sh *sh)
{
	t_exe	exe;

	exe.i = 0;
	sh->nb_cmd++;
	if (pipe(sh->pipe) != 0)
		(perror("pipe error"), child_free(sh), exit(EXIT_FAILURE));
	add_pid(sh->nb_cmd, sh);
	sh->pid[sh->nb_cmd - 1] = fork();
	if (sh->pid[sh->nb_cmd - 1] == -1)
		(perror("fork error"), child_free(sh), exit(EXIT_FAILURE));
	if (sh->pid[sh->nb_cmd - 1] == 0)
		child_cmd_handler(sh, &exe, args);
	else
	{
		exe.i = find_sp(args, sh);
		if (is_builtin(args[0]))
			builtin_handler(sh, &exe, args);
		else if (!find_sp(args, sh))
			exec_cmd_13(sh);
		else
			exec_cmd_18(sh, args);
	}
}
