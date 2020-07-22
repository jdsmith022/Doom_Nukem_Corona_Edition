/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_editor_font.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/22 14:40:40 by jesmith       #+#    #+#                 */
/*   Updated: 2020/07/22 15:15:49 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

static void	font_to_surface(t_doom *doom, char *str, SDL_Color font_color, size_t len)
{
	TTF_Font	*font;
	char		*string;
	SDL_Surface	*font_surface;
	size_t		index;


	index = 0;
	TTF_Init();
	font = TTF_OpenFont("srcs/UI/text/amatic/AmaticSC-Regular.ttf", 38);
	while (index < len)
	{
		font_surface = TTF_RenderText_Solid(font, string, doom->lib.font_lib[index].font_color);
		if (font_surface == NULL)
			doom_exit_failure(doom, MALLOC_ERR);
		doom->lib.font_lib[index].font_surface = font_surface;
		index++;
	}
}

static void	string_for_editor(t_doom *doom)
{
	SDL_Rect	font_rect;
	size_t		index;
	char		*str;

	index = 0;
	str = "Select texture";
	doom->lib.font_lib[index].font_rect.x = 300;
	doom->lib.font_lib[index].font_rect.y = 300;
	index++;
	str= "Select objects";
	doom->lib.font_lib[index].font_rect.x = 300;
	doom->lib.font_lib[index].font_rect.y = 300;
	index++;
	font_to_surface(doom, str, doom->lib.game_editor_font->black, index);

}

void		save_game_editor_font(t_doom *doom, int *len)
{
	t_font		*font_lib;

	*len = 6;
	font_lib = doom->lib.font_lib;
	font_lib = (t_font*)ft_memalloc(sizeof(t_font) * (*len));
	if (font_lib == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
	doom->lib.font_lib = font_lib;
	set_font_color(doom, *len);
}
