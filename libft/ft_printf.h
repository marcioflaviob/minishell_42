/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:28:43 by trimize           #+#    #+#             */
/*   Updated: 2023/12/08 17:22:07 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <unistd.h>
# include <stdarg.h>

void	ft_putnbr_n(int n);
void	printspace(int nb);
int		ft_printf(const char *str, ...);
int		isflag(char c, char *flags);
int		ft_lenunsint(unsigned int n);
int		ft_flag0u(const char *str, va_list args);
int		get_hexnumber(long long int nbr, char *b);
int		ft_lenint2(int n);
int		ft_rev(char *res, int n);
int		hexasharp(const char *str, unsigned int nbr, char *b);
int		sspace(const char *str, va_list args);
int		dispace(const char *str, va_list args);
int		hex8(unsigned int nbr, char *b);
int		w_plus(const char *str, va_list args);
int		w_space(const char *str, va_list args);
int		ft_error0(const char *str);
int		ft_errorplus(const char *str);

typedef struct s_var
{
	int	v_i;
	int	width;
	int	error;

}	t_var;

t_var	*ft_varnew(int i);
void	checkwidth(const char *str, t_var *var);
int		case0dot(const char *str, va_list args, t_var *var);
int		hex2(unsigned int nbr, char *b, t_var *var);
int		ft_putnbr_unsigned2(unsigned int n, t_var *var);
int		hex(long long int nbr, char *b, t_var *var);
int		case_flag0(const char *str, va_list args, t_var *var);
int		ft_flag0x(const char *str, va_list args);
int		ft_flag0upperx(const char *str, va_list args);
int		switch_case_flags(const char *str, va_list args, t_var *var);
int		filler2(int len, const char *str, t_var *var);
int		case_flagdot2(const char *str, va_list args, t_var *var);
int		filler(const char *str, t_var *var, int len, va_list args);
int		switch_case(char c, va_list args, t_var *var);
int		case_flagplus(const char *str, va_list args, t_var *var);
int		caseminusdot(const char *str, t_var *var, va_list args);
int		case_flagsharp(const char *str, va_list args, t_var *var);
int		case_flagspace(const char *str, va_list args, t_var *var);
int		ft_flagdotupperx(const char *str, va_list args, t_var *var);
int		ft_flagdotx(const char *str, va_list args, t_var *var);
int		flagdotdi(const char *str, va_list args, int y, t_var *var);
int		case_flagdot(const char *str, va_list args, t_var *var);
int		case_flagminus(const char *str, va_list args, t_var *var);
int		ft_flagdotu(const char *str, va_list args, t_var *var);
int		flag0di(const char *str, va_list args, t_var *var);
int		switch_case3(int n, va_list args, t_var *var);
int		switch_case2(va_list args, t_var *var);
int		case_flag02(int i, char const *str, t_var *var, va_list args);
int		case_flagminus2(int y, t_var *var, int c, int a);
int		flagdotdi2(int y, int tmp, t_var *var, int i);
int		flagdotdi3(int y, int tmp, t_var *var, int i);
int		flagdotdi4(t_var *var, int tmp);
int		case_flagdot4(int i, const char *str, char *tmp, t_var *var);
int		case_flagdot3(t_var *var, char *tmp);
int		case_flagdot5(t_var *var);
int		filler3(int len, const char *str, va_list args, t_var *var);
int		ft_flagdotu2(int y, unsigned int tmp, t_var *var, int i);
int		ft_putnbr_unsigned3(unsigned int n, char *res, int i);
int		ft_flagdotx2(unsigned int a, unsigned int i, t_var *var, int y);

#endif