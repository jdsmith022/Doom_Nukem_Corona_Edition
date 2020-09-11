/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   finished_text_2.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 15:14:43 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/09 02:28:24 by JessicaSmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/hud.h"
#include "../../includes/gameplay.h"

char		*successful_shop(t_doom *doom, t_font *lib)
{
	char *status;

	lib[1].font_rect.x = WIDTH / 7.6;
	lib[2].font_rect.x = WIDTH / 4;
	status = "Well done! You found all you're groceries";
	lib[1].font_color = doom->lib.font_lib.font_color.blue;
	lib[2].str = "without contracting Covid-19!";
	lib[2].font_color = doom->lib.font_lib.font_color.blue;
	return (status);
}

char		*set_greedy_font(t_doom *doom, t_font *lib)
{
	char *status;

	lib[1].font_rect.x = WIDTH / 7.5;
	lib[1].font_rect.y = HEIGHT / 2 - 25;
	lib[2].font_rect.x = WIDTH / 4;
	lib[2].font_rect.y = HEIGHT / 2 + 25;
	status = "You took more than what was on your list!";
	lib[1].font_color = doom->lib.font_lib.font_color.red;
	lib[2].str = "Think of others and try again.";
	lib[2].font_color = doom->lib.font_lib.font_color.blue;
	return (status);
}

char		*corona_level_too_height(t_doom *doom, t_font *lib)
{
	char *status;

	status = "Oh no! Looks like you contracted Covid-19!";
	lib[1].font_color = doom->lib.font_lib.font_color.green;
	lib[2].str = "Self-quarantine immeidately!";
	lib[2].font_color = doom->lib.font_lib.font_color.green;
	return (status);
}
