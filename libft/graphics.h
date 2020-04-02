/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   graphics.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jessicasmith <jessicasmith@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/02 09:32:32 by jessicasmit    #+#    #+#                */
/*   Updated: 2020/02/17 19:21:27 by mminkjan      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// #ifndef GRAPHICS_H
// # define GRAPHICS_H

// # include "libft.h"
// # include "../minilibx_macos/mlx.h"

// # define ONE_START 0x0B171A
// # define ONE_MIDDLE 0xE6DADA
// # define ONE_END 0xFFFFFF

// # define TWO_START 0x000000
// # define TWO_MIDDLE 0xB21F1F
// # define TWO_END 0xfdbb2d

// # define THREE_START 0xFFF8DE
// # define THREE_MIDDLE 0xF7971E
// # define THREE_END 0x956900

// # define SCROLL_UP 5
// # define SCROLL_DOWN 4
// # define MOUSE_PRESS 1

// # define ESC 53
// # define ARROW_UP 125
// # define ARROW_DOWN 126
// # define ARROW_LEFT 124
// # define ARROW_RIGHT 123
// # define SPACE 49
// # define RESET 51

// # define MALLOC_ERR "error: malloc"

// typedef struct	s_color
// {
// 	int			start;
// 	int			end;
// 	double		hue;
// 	double		saturation;
// 	double		value;
// }				t_color;

// typedef struct	s_events
// {
// 	double		zoom;
// 	int			freeze;
// 	int			color_set;
// 	int			color_grade;
// 	int			mouse_press;
// 	double		mouse_x;
// 	double		mouse_y;
// 	double		hold_x;
// 	double		hold_y;
// }				t_events;

// // typedef struct	s_mlx
// // {
// // 	void		*win_ptr;
// // 	void		*mlx_ptr;
// // 	void		*image_ptr;
// // 	int			bits_ppixel;
// // 	int			size_line;
// // 	char		*addr_str;
// // 	char		*title;
// // 	double		max;
// // 	double		mid;
// // 	double		min;
// // 	t_events	*events;
// // 	t_color		color;
// // }				t_mlx;

// void			mlx_setup(t_mlx *mlx);
// int				mlx_exit(char *s);

// int				hsv_color(double calc_nb);
// int				rgb_color(t_mlx *mlx, double calc_nb);
// int				get_bit_value(int start, int end, double percentage);
// double			percentage(t_mlx *mlx, double current);
// // void			put_pixel(t_mlx *mlx, int color, int x, int y);
// #endif
