/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hud_font.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jessicasmith <jessicasmith@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/22 23:02:29 by jessicasmit   #+#    #+#                 */
/*   Updated: 2020/08/08 18:15:37 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/hud.h"

static void	set_levels(t_doom *doom, t_font *lib)
{
	int		level;
	char	*corona_level;
	char	*cat;

	level = doom->hud->corona_level;
	corona_level = ft_itoa(level);
	cat = ft_strcat(corona_level, "%");
	lib[4].str = corona_level;
	lib[4].font_rect.x = 175;
	lib[4].font_rect.y = HEIGHT - 35;
	if (level > 84)
		lib[4].font_color = doom->lib.font_lib.font_color.red;
	else
		lib[4].font_color = doom->lib.font_lib.font_color.white;
	level = doom->hud->sanitizer_level;
	corona_level = ft_itoa(level);
	cat = ft_strcat(corona_level, "%");
	lib[5].str = corona_level;
	lib[5].font_rect.x = WIDTH - 250;
	lib[5].font_rect.y = HEIGHT - 35;
	if (level < 15)
		lib[5].font_color = doom->lib.font_lib.font_color.red;
	else
		lib[5].font_color = doom->lib.font_lib.font_color.white;
}

static void	set_text(t_doom *doom, t_font *lib, int len)
{
	SDL_Rect	font_rect;

	lib[0].len = len;
	lib[0].str = "Corona Level";
	lib[0].font_rect.x = 10;
	lib[0].font_rect.y = HEIGHT - 35;
	lib[0].font_color = doom->lib.font_lib.font_color.green;
	lib[1].str = "Sanitizer Level";
	lib[1].font_rect.x = WIDTH - 175;
	lib[1].font_rect.y = HEIGHT - 35;
	lib[1].font_color = doom->lib.font_lib.font_color.blue;
	lib[2].str = "Shopping List";
	lib[2].font_rect.x = WIDTH - 160;
	lib[2].font_rect.y = 15;
	lib[2].font_color = doom->lib.font_lib.font_color.red;
	lib[3].str = "Basket";
	lib[3].font_rect.x = 10;
	lib[3].font_rect.y = 15;
	lib[3].font_color = doom->lib.font_lib.font_color.red;
	set_levels(doom, lib);
}

void		save_hud_font(t_doom *doom, int *len)
{
	char		*font_path;
	int			font_size;

	*len = 6;
	doom->lib.font_lib.hud_font = (t_font*)ft_memalloc(sizeof(t_font) * (*len));
	if (doom->lib.font_lib.hud_font == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
	set_text(doom, doom->lib.font_lib.hud_font, *len);
	font_path = "srcs/font/font_style/JosefinSans-Bold.ttf";
	font_size = 22;
	font_to_sdl(doom, doom->lib.font_lib.hud_font, font_path, font_size);
	printf("done\n");
}
