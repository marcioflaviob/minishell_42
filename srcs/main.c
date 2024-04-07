/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 22:51:29 by trimize           #+#    #+#             */
/*   Updated: 2024/04/07 16:59:38 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//void	builtin_dealer(t_sh *sh, char *cmd)
//{
//	sh->args = ft_better_split(cmd);
//	//function to add the variables
//	dollar_sign_dealer(&sh->args, sh);
//	quotes_removal(&sh->args);

//	//int i = 0;
//	//printf("\nBEFORE\n");
//	//while (args[i])
//	//{
//	//	printf("Arg %d: %s\n", i, args[i]);
//	//	i++;
//	//}
//	//printf("\n\n");


//	//i = 0;
//	//printf("\nAFTER\n");
//	//while (args[i])
//	//{
//	//	printf("Arg %d: %s\n", i, args[i]);
//	//	i++;
//	//}
//	//printf("\n\n");

//	if (ft_equalstr(sh->args[0], "pwd"))
//		(freetab(sh->args), free(cmd), pwd());
//	else if (ft_equalstr(sh->args[0], "cd") && !sh->args[1])
//		return (freetab(sh->args), free(cmd));
//	else if (ft_equalstr(sh->args[0], "cd") && sh->args[1])
//	{
//		if (tab_len(sh->args) > 3)
//		{
//			printf("minishell: cd: too many arguments\n");
//			(freetab(sh->args), free(cmd), get_input(sh));
//			return ;
//		}
//		cd(sh, sh->args[1], sh);
//		(freetab(sh->args), free(cmd));
//	}
//	else if (ft_equalstr(sh->args[0], "echo"))
//		(echo(sh->args), freetab(sh->args), free(cmd));
//	get_input(sh);
//}

int	main(void)
{
	t_sh	shell;
	//int		permission_fd;
	//char	*buffer;

	shell.true_stdin = dup(STDIN_FILENO);
	shell.true_stdout = dup(STDOUT_FILENO);
	shell.fd_input = -2;
	shell.fd_output = -2;
	shell.last_cmd_st = 0;
	shell.wrong_file = NULL;
	shell.variables = (char **)malloc(1 * sizeof(char));
	shell.variables[0] = NULL;
	shell.refresh = 0;
	//permission_fd = open("./assets/permission", O_RDWR);
	//if (permission_fd == -1)
	//	(write(2, "Failed opening permission file", 30));
	//else
	{
		//buffer = get_next_line(permission_fd);
		//if (buffer[15] == '1')
		//	new_terminal(&shell, buffer);
		//else
		{
			shell.current_dir = get_cwd();
			if (!shell.current_dir)
				return (0); //RETURN ERROR HERE
			shell.emoji_path = ft_strjoin(shell.current_dir, "/assets/emojis");
			printf("emojis path : %s\n\n", shell.emoji_path);
			//(print_minishell_art(), free(buffer));
			set_env(&shell);
			signal_initializer();
			get_input(&shell);
			free(shell.current_dir);
		}
	}
	return (0);
}

