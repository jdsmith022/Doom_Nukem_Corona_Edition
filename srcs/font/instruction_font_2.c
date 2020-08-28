/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   instruction_font_2.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 15:10:35 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/28 19:28:33 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/font.h"

static void	set_instruction_text_6(t_doom *doom, t_font *lib)
{
	lib[20].str = "Make sure you're read to checkout!";
	lib[20].font_rect.x = WIDTH / 2 - 150;
	lib[20].font_rect.y = HEIGHT / 2 + 165;
	lib[20].font_color = doom->lib.font_lib.font_color.red;
	lib[21].str = "HEY! Don't shoot at me brat!";
	lib[21].font_rect.x = WIDTH / 2 - 125;
	lib[21].font_rect.y = HEIGHT / 2 + 165;
	lib[21].font_color = doom->lib.font_lib.font_color.red;
	lib[22].str = "Oh thank you! Now I'm clean!";
	lib[22].font_rect.x = WIDTH / 2 - 130;
	lib[22].font_rect.y = HEIGHT / 2 + 165;
	lib[22].font_color = doom->lib.font_lib.font_color.blue;
	lib[23].str = "Rude! I'm getting the manager!";
	lib[23].font_rect.x = WIDTH / 2 - 135;
	lib[23].font_rect.y = HEIGHT / 2 + 165;
	lib[23].font_color = doom->lib.font_lib.font_color.red;
	lib[24].str = "Health pack: Corona decreased.";
	lib[24].font_rect.x = WIDTH / 2 - 130;
	lib[24].font_rect.y = HEIGHT / 2 + 165;
	lib[24].font_color = doom->lib.font_lib.font_color.white;
	lib[25].str = "Face mask: Corona decreased.";
	lib[25].font_rect.x = WIDTH / 2 - 130;
	lib[25].font_rect.y = HEIGHT / 2 + 165;
	lib[25].font_color = doom->lib.font_lib.font_color.white;
}

static void	set_instruction_text_5(t_doom *doom, t_font *lib)
{
	lib[15].str = "Press E again to exit collection mode.";
	lib[15].font_rect.x = WIDTH / 2 - 175;
	lib[15].font_rect.y = HEIGHT / 2 + 25;
	lib[15].font_color = doom->lib.font_lib.font_color.white;
	lib[16].str = "Make sure to get everything on your shopping\
	list!";
	lib[16].font_rect.x = WIDTH / 2 - 220;
	lib[16].font_rect.y = HEIGHT / 2 + 75;
	lib[16].font_color = doom->lib.font_lib.font_color.red;
	lib[17].str = "Press T and use the cursor to remove items from\
	your basket.";
	lib[17].font_rect.x = WIDTH / 5;
	lib[17].font_rect.y = HEIGHT / 2 + 115;
	lib[17].font_color = doom->lib.font_lib.font_color.white;
	lib[18].str = "Press T again to exit removal mode.";
	lib[18].font_rect.x = WIDTH / 2 - 145;
	lib[18].font_rect.y = HEIGHT / 2 + 125;
	lib[18].font_color = doom->lib.font_lib.font_color.white;
	lib[19].str = "Keep Safe! Please collect a basket.";
	lib[19].font_rect.x = WIDTH / 2 - 150;
	lib[19].font_rect.y = HEIGHT / 2 + 165;
	lib[19].font_color = doom->lib.font_lib.font_color.red;
	set_instruction_text_6(doom, lib);
}

void		set_instruction_text_4(t_doom *doom, t_font *lib)
{
	lib[10].str = "Keep a look out for the Covid-19 virus! Look around with \
	your mouse!";
	lib[10].font_rect.x = WIDTH / 2 - 300;
	lib[10].font_rect.y = HEIGHT / 2 - 125;
	lib[10].font_color = doom->lib.font_lib.font_color.green;
	lib[11].str = "Press R to enter spray mode and left mouse click\
	to spray sanitizer.";
	lib[11].font_rect.x = WIDTH / 7.5;
	lib[11].font_rect.y = HEIGHT / 2 - 100;
	lib[11].font_color = doom->lib.font_lib.font_color.white;
	lib[12].str = "Press R again to exit spray mode.";
	lib[12].font_rect.x = WIDTH / 2 - 145;
	lib[12].font_rect.y = HEIGHT / 2 - 75;
	lib[12].font_color = doom->lib.font_lib.font_color.white;
	lib[13].str = "Don't worry! You can fill santizer at refill stations,\
	but don't be greedy!";
	lib[13].font_rect.x = WIDTH / 2 - 300;
	lib[13].font_rect.y = HEIGHT / 2 - 25;
	lib[13].font_color = doom->lib.font_lib.font_color.blue;
	lib[14].str = "Press E to enter collection mode and left mouse\
	click to collect item.";
	lib[14].font_rect.x = WIDTH / 7.5;
	lib[14].font_rect.y = HEIGHT / 2;
	lib[14].font_color = doom->lib.font_lib.font_color.white;
	set_instruction_text_5(doom, lib);
}
