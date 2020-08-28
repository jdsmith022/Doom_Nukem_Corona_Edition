/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   instruction_font.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/23 15:41:14 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/28 19:10:05 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/font.h"

static void	set_instruction_text_3(t_doom *doom, t_font *lib)
{
	lib[8].str = "Watch out! You tripped over the crate! \
	Jump to stand up.";
	lib[8].font_rect.x = WIDTH / 2 - 220;
	lib[8].font_rect.y = HEIGHT / 2 - 25;
	lib[8].font_color = doom->lib.font_lib.font_color.red;
	lib[9].str = "You're corona level has increased!";
	lib[9].font_rect.x = WIDTH / 2 - 130;
	lib[9].font_rect.y = HEIGHT / 2 + 10;
	lib[9].font_color = doom->lib.font_lib.font_color.green;
}

static void	set_instruction_text_2(t_doom *doom, t_font *lib)
{
	lib[3].str = "Scissor lift operations:";
	lib[3].font_rect.x = WIDTH / 2 - 100;
	lib[3].font_rect.y = HEIGHT / 2 - 45;
	lib[3].font_color = doom->lib.font_lib.font_color.red;
	lib[4].str = "Forward = W			Backwards = S			\
	Left = A				Right = D";
	lib[4].font_rect.x = WIDTH / 2 - 220;
	lib[4].font_rect.y = HEIGHT / 2 - 20;
	lib[4].font_color = doom->lib.font_lib.font_color.white;
	lib[5].str = "UP = up arrow key				DOWN = down arrow key";
	lib[5].font_rect.x = WIDTH / 2 - 180;
	lib[5].font_rect.y = HEIGHT / 2 + 5;
	lib[5].font_color = doom->lib.font_lib.font_color.white;
	lib[6].str = "Exit = Return scissor lift to lowest level and press X.";
	lib[6].font_rect.x = WIDTH / 2 - 200;
	lib[6].font_rect.y = HEIGHT / 2 + 27;
	lib[6].font_color = doom->lib.font_lib.font_color.white;
	lib[7].str = "You're too close to the wall! Move and try again.";
	lib[7].font_rect.x = WIDTH / 2 - 200;
	lib[7].font_rect.y = HEIGHT / 2;
	lib[7].font_color = doom->lib.font_lib.font_color.red;
	set_instruction_text_3(doom, lib);
}

static void	set_instruction_text(t_doom *doom, t_font *lib, int len)
{
	SDL_Rect	font_rect;

	lib[0].len = len;
	lib[0].str = "Key press player movements";
	lib[0].font_rect.x = WIDTH / 2 - 120;
	lib[0].font_rect.y = HEIGHT / 2 - 40;
	lib[0].font_color = doom->lib.font_lib.font_color.blue;
	lib[1].str = "Forward = W			Backwards = S			\
	Left = A				Right = D";
	lib[1].font_rect.x = WIDTH / 2 - 210;
	lib[1].font_rect.y = HEIGHT / 2 - 8;
	lib[1].font_color = doom->lib.font_lib.font_color.white;
	lib[2].str = "Jump = Spacebar					Bend = X";
	lib[2].font_rect.x = WIDTH / 2 - 120;
	lib[2].font_rect.y = HEIGHT / 2 + 20;
	lib[2].font_color = doom->lib.font_lib.font_color.white;
	set_instruction_text_2(doom, lib);
	set_instruction_text_4(doom, lib);
}

void		save_instruction_font(t_doom *doom, int *len)
{
	TTF_Font	*font;
	int			font_size;

	*len = 26;
	doom->lib.font_lib.instruction_font = \
		(t_font*)ft_memalloc(sizeof(t_font) * (*len));
	if (doom->lib.font_lib.instruction_font == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
	set_instruction_text(doom, doom->lib.font_lib.instruction_font, *len);
	font = doom->lib.font_lib.font_18;
	font_to_sdl(doom, doom->lib.font_lib.instruction_font, font);
}
