/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrandao <mbrandao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 22:51:29 by trimize           #+#    #+#             */
/*   Updated: 2024/04/06 23:29:10 by mbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	builtin_dealer(t_sh *sh, char *cmd)
{
	sh->args = ft_better_split(cmd);
	//function to add the variables
	dollar_sign_dealer(&sh->args, sh);
	quotes_removal(&sh->args);
	// first_arg(sh);

	int i = 0;
	printf("\nBEFORE\n");
	while (sh->args[i])
	{
		printf("Arg %d: %s\n", i, sh->args[i]);
		i++;
	}
	printf("\n\n");


	i = 0;
	printf("\nAFTER\n");
	while (sh->args[i])
	{
		printf("Arg %d: %s\n", i, sh->args[i]);
		i++;
	}
	printf("\n\n");

	if (ft_equalstr(sh->args[0], "pwd"))
		(freetab(sh->args), free(cmd), pwd());
	else if (ft_equalstr(sh->args[0], "cd") && !sh->args[1])
		return (freetab(sh->args), free(cmd));
	else if (ft_equalstr(sh->args[0], "cd") && sh->args[1])
	{
		if (tab_len(sh->args) > 3)
		{
			printf("minishell: cd: too many arguments\n");
			(freetab(sh->args), free(cmd), get_input(sh));
			return ;
		}
		cd(sh, sh->args[1], sh);
		(freetab(sh->args), free(cmd));
	}
	else if (ft_equalstr(sh->args[0], "echo"))
		(echo(sh->args), freetab(sh->args), free(cmd));
	get_input(sh);
}

// int	main(void)
// {
// 	t_sh	shell;
// 	int		permission_fd;
// 	char	*buffer;

// 	// sh.variables = (char **)malloc(1 * sizeof(char));
// 	// sh.variables[0] = NULL;
// 	// pipe(sh.pipe_read);
// 	// pipe(sh.pipe_write);
// 	permission_fd = open("./assets/permission", O_RDWR);
// 	if (permission_fd == -1)
// 		(write(2, "Failed opening permission file", 30));
// 	else
// 	{
// 		buffer = get_next_line(permission_fd);
// 		if (buffer[15] == '1')
// 			new_terminal(&shell, buffer);
// 		else
// 		{
// 			shell.current_dir = get_cwd();
// 			if (!shell.current_dir)
// 				return (0); //RETURN ERROR HERE
// 			shell.emoji_path = ft_strjoin(shell.current_dir, "/assets/emojis");
// 			(print_minishell_art(), free(buffer), set_env(&shell));
// 			signal_initializer();
// 			get_input(&shell);
// 			// free(shell.current_dir);
// 		}
// 	}
// 	// get_input(&shell);
// }

int	main()
{
	t_sh	sh;
	
	sh.current_dir = get_cwd();
	if (!sh.current_dir)
		return (0); //RETURN ERROR HERE
	sh.emoji_path = ft_strjoin(sh.current_dir, "/assets/emojis");
	set_env(&sh);
	// print_minishell_art();
	signal_initializer();
	while (1)
	{
		get_input(&sh);
		// dollar_sign_dealer(&sh.args, &sh);
		// while (wildcard(&sh))
		// 	;
		// replace_var(&sh, &sh.args);
		// quotes_removal(&sh.args);
		set_sp_bool(&sh);
		int i = 0;
		while (i < (tab_len(sh.args) - 1))
		{
			printf("%d", sh.sp_bool[i++]);
			printf("\n");
		}
		// print_tab(sh.args);
	}
}

