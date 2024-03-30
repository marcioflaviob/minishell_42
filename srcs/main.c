/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 22:51:29 by trimize           #+#    #+#             */
/*   Updated: 2024/03/30 23:35:29 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	builtin_dealer(t_sh *sh, char *cmd)
{
	char	**args;

	args = ft_split(cmd, ' ');
	if (ft_equalstr(args[0], "pwd"))
		(freetab(args), free(cmd), pwd());
	else if (ft_equalstr(args[0], "cd") && !args[1])
		return (freetab(args), free(cmd));
	else if (ft_equalstr(args[0], "cd") && args[1])
	{
		if (tab_len(args) > 2)
		{
			printf("minishell: cd: too many arguments");
			(freetab(args), free(cmd));
			return ;
		}
		cd(sh, args[1]);
		(freetab(args), free(cmd));
	}
	else if (ft_equalstr(args[0], "echo"))
		(echo(args), freetab(args), free(cmd));
}

int	main(void)
{
	t_sh	shell;
	char	*command;

	shell.current_dir = get_cwd();
	if (!shell.current_dir)
		return (0); //RETURN ERROR HERE
	print_minishell_art();
	signal_initializer();
	while (1)
	{
		command = get_input();
		builtin_dealer(&shell, command);
	}
	return (0);
}
