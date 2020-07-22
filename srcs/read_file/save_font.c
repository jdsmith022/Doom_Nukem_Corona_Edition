/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   save_font.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: JessicaSmith <JessicaSmith@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/08 15:21:36 by JessicaSmit   #+#    #+#                 */
/*   Updated: 2020/07/22 21:13:44 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// #include "../../includes/doom.h"

// static void	font_to_surface(t_doom *doom)
// {
// 	TTF_Font	*font;
// 	char		*string;
// 	SDL_Color	font_color;
// 	SDL_Surface	*font_surface;

// 	TTF_Init();
// 	font = TTF_OpenFont("srcs/UI/text/amatic/AmaticSC-Regular.ttf", 38);
// 	string = "Fuck yeah font!";
// 	font_color.r = 255;
// 	font_color.g = 255;
// 	font_color.b = 255;
// 	doom->lib.font_lib[0].font_rect.x = 300;
// 	doom->lib.font_lib[0].font_rect.y = 300;
// 	font_surface = TTF_RenderText_Solid(font, string, font_color);
// 	if (font_surface == NULL)
// 		doom_exit_failure(doom, MALLOC_ERR);
// 	doom->lib.font_lib[0].font_surface = font_surface;
// }

// void		save_font(t_doom *doom, int *len)
// {
// 	t_font		*font_lib;

// 	set_font_color(doom);

// 	*len = 1;
// 	font_lib = doom->lib.font_lib;
// 	font_lib = (t_font*)ft_memalloc(sizeof(t_font) * (*len));
// 	if (font_lib == NULL)
// 		doom_exit_failure(doom, MALLOC_ERR);
// 	doom->lib.font_lib = font_lib;
// 	font_to_surface(doom);
// }
