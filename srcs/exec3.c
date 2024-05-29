/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 19:03:47 by trimize           #+#    #+#             */
/*   Updated: 2024/05/29 13:58:45 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	helper_12(t_sh *sh, t_exe *exe)
{
	freetab(sh->env);
	free(sh->sp_bool);
	freetab(sh->args);
	free(sh->current_dir);
	freetab(sh->variables);
	free(sh->pid);
	close(sh->pipe[0]);
	close(sh->pipe[1]);
	exe->i = open(sh->emoji_path, O_RDONLY);
	get_next_line(exe->i, 1);
	close(exe->i);
	free(sh->emoji_path);
	if (sh->op_pipe)
	{
		close(sh->pipe_par[0]);
		close(sh->pipe_par[1]);
	}
	close(sh->true_stdin);
	close(sh->true_stdout);
}

void	exec_cmd_12(t_sh *sh, t_exe *exe, char **args)
{
	int	a;

	a = ft_atoi(args[1]);
	write(2, "exit", ft_strlen("exit"));
	if (args[1] && !is_num_str(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		a = 2;
	}
	else if (ft_strchr(args[1], '-'))
		a = ft_atoi(args[1]);
	else if (ft_strchr(args[1], '+'))
		a = ft_atoi(args[1]);
	if (find_sp(args, sh) > 2 || (tab_len(args) - 1) > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		sh->bool_result = 0;
		sh->last_cmd_st = 1;
		return ;
	}
	helper_12(sh, exe);
	exit(a);
}

void	exec_cmd_13(t_sh *sh)
{
	size_t	i;

	i = 0;
	close(sh->pipe[1]); //dd
	close(sh->pipe[0]);
	if (sh->op_pipe)
	{
		close(sh->pipe_par[0]);
		close(sh->pipe_par[1]);
	}
	while (i <= sh->nb_cmd - 1)
		waitpid(sh->pid[i++], &sh->last_cmd_st, 0);
	sh->last_cmd_st = WEXITSTATUS(sh->last_cmd_st);
	if (sh->last_cmd_st == 131)
		write(2, "Quit (core dumped)\n", 19);
	sh->position = tab_len(sh->args) - 1;
}

void	helper_14(t_sh *sh, char **args, int *i, int *y)
{
	int	tmp;

	tmp = *i;
	if (args[*y] && ft_equalstr(args[*y], "<"))
	{
		*i += find_sp(&args[*i], sh) + 1;
		while (args[*i + 1] && !check_special_redirect(args[*i + 1]))
			(*i)++;
	}
	else if (args[*y] && ft_equalstr(args[*y], ">"))
	{
		*i += find_sp(&args[*i], sh) + 1;
		while (args[*i + 1] && !check_special_redirect(args[*i + 1]))
			(*i)++;
	}
	else if (args[*y] && ft_equalstr(args[*y], ">>"))
	{
		*i += find_sp(&args[*i], sh) + 1;
		while (args[*i + 1] && !check_special_redirect(args[*i + 1]))
			(*i)++;
	}
	sh->position += *i - tmp;
	*y = find_sp(&args[*i], sh) + *i;
}

void	exec_cmd_14(t_sh *sh, char **args)
{
	int	i;
	int	y;

	i = 0;
	y = find_sp(&args[i], sh);
	while (ft_equalstr(args[y], "<")
		|| ft_equalstr(args[y], ">") || ft_equalstr(args[y], ">>"))
		helper_14(sh, args, &i, &y);
	if (ft_equalstr(args[y], "|"))
		close(sh->pipe[1]);
	else
	{
		waitpid(sh->pid[sh->nb_cmd - 1], &sh->last_cmd_st, 0);
		sh->last_cmd_st = WEXITSTATUS(sh->last_cmd_st);
	}
	if (args[y])
		sh->position++;
	else
		sh->position = tab_len(sh->args) - 1;
}
