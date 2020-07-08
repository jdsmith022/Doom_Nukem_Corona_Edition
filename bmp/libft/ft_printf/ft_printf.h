/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: efrank <efrank@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/27 15:00:54 by efrank         #+#    #+#                */
/*   Updated: 2019/11/12 16:27:07 by efrank        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <limits.h>
# include <math.h>
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include "../src/libft.h"

# define PFARG "%fscdpxXouib"

typedef struct		s_flags
{
	short			zero;
	short			hashtag;
	short			min;
	short			plus;
	short			space;
	short			h;
	short			l;
}					t_flags;

typedef struct		s_arg
{
	char			type;
	void			*data;
	double			dbl;
	long double		ldbl;
	char			*format_str;
	int				*print_count;
	int				precision;
	int				width;
	t_flags			flags;
}					t_arg;

int					get_unsignedintlen(unsigned long long n);
int					check_modulo(const char *string);
int					get_index(const char *string, int i);
int					get_hex_length(unsigned long long num);
int					get_oct_length(unsigned long long num);
int					get_float_length(long double num, int precision);
int					get_pointer_length(unsigned long long num);
int					valid_arg(const char *s);
long long			get_int_type(t_arg arg);
unsigned long long	get_unsigned_type(t_arg arg);
void				put_strwidth(t_arg arg, char c, int *print_count);
void				put_charwidth(t_arg arg, char c, int *print_count);
void				put_unsignedwidth(t_arg arg, char c, int *print_count);
void				put_intwidth(t_arg arg, char c, int *print_count);
void				put_floatwidth(t_arg arg, char c, int *print_count);
void				print_char(t_arg arg, int *print_count);
void				print_modulo(t_arg arg, int *print_count);
void				print_string(t_arg arg, int *print_count);
void				print_decimal(t_arg arg, int *print_count);
void				print_float(t_arg arg, int *print_count);
void				print_pointer(t_arg arg, int *print_count);
void				print_hex(t_arg arg, int *print_count);
void				print_width(t_arg arg, int *print_count);
void				print_precision(t_arg arg, int *print_count);
void				get_flags(t_arg *arg_list, int size);
void				print_unsigned(t_arg arg, int *print_count);
void				print_oct(t_arg arg, int *print_count);
void				nbr_zero(t_arg arg, int *print_count);
void				print_binary(t_arg arg, int *print_count);
void				print_output(t_arg *arg_list, const char *string,
					int *print_count);
t_arg				put_data(t_arg arg, const char *s, va_list ap);
t_arg				*get_data_list(const char *string, t_arg *arg_list,
					va_list ap);
t_flags				put_flags(t_arg arg);
int					ft_printf(const char *string, ...);

#endif
