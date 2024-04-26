/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:43:56 by mbrandao          #+#    #+#             */
/*   Updated: 2024/04/26 19:45:06 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "../includes/minishell.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

int		has_end(char *str);
char	*line_dealer(char *updated);
char	*get_next_line(int fd);

#endif
