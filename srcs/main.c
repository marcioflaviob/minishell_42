/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 22:51:29 by trimize           #+#    #+#             */
/*   Updated: 2024/04/02 18:10:20 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	builtin_dealer(t_sh *sh, char *cmd)
{
	char	**args;

	args = ft_better_split(cmd);

	//int i = 0;
	//printf("\nBEFORE\n");
	//while (args[i])
	//{
	//	printf("Arg %d: %s\n", i, args[i]);
	//	i++;
	//}
	//printf("\n\n");

	//dollar_sign_dealer(&args);
	//quotes_removal(&args);

	//i = 0;
	//printf("\nAFTER\n");
	//while (args[i])
	//{
	//	printf("Arg %d: %s\n", i, args[i]);
	//	i++;
	//}
	//printf("\n\n");

	if (ft_equalstr(args[0], "pwd"))
		(freetab(args), free(cmd), pwd());
	else if (ft_equalstr(args[0], "cd") && !args[1])
		return (freetab(args), free(cmd));
	else if (ft_equalstr(args[0], "cd") && args[1])
	{
		if (tab_len(args) > 3)
		{
			printf("minishell: cd: too many arguments\n");
			(freetab(args), free(cmd), get_input(sh));
			return ;
		}
		cd(sh, args[1], sh);
		(freetab(args), free(cmd));
	}
	else if (ft_equalstr(args[0], "echo"))
		(echo(args), freetab(args), free(cmd));
	get_input(sh);
}

int	main(void)
{
	t_sh	shell;
	int		permission_fd;
	char	*buffer;

	permission_fd = open("./assets/permission", O_RDWR);
	if (permission_fd == -1)
		(write(2, "Failed opening permission file", 30));
	else
	{
		buffer = get_next_line(permission_fd);
		if (buffer[15] == '1')
			new_terminal(&shell, buffer);
		else
		{
			shell.current_dir = get_cwd();
			if (!shell.current_dir)
				return (0); //RETURN ERROR HERE
			shell.emoji_path = ft_strjoin(shell.current_dir, "/assets/emojis");
			(print_minishell_art(), free(buffer), set_env(&shell));
			signal_initializer();
			get_input(&shell);
			free(shell.current_dir);
		}
	}
}
