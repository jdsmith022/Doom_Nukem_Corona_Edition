/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_hud_draw.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rsteigen <rsteigen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/30 21:54:23 by rsteigen      #+#    #+#                 */
/*   Updated: 2020/08/30 21:54:24 by rsteigen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/hud.h"
#include "../../includes/sprites.h"

static void		draw_add_on(t_doom *doom, int sprite_i)
{
	t_line bar;

	scale_bar(doom, &bar, sprite_i);
	if (sprite_i == doom->player.right_select || \
	(doom->player_handed == right && doom->own_event.shoot == TRUE \
	&& sprite_i != CROSS_HAIR))
	{
		bar.start.x += 450;
		bar.end.x += 450;
	}
	if (sprite_i == CROSS_HAIR)
	{
		bar.start.y = HEIGHT / 2 - 20;
		bar.end.y = HEIGHT / 2 + 20;
	}
	draw_stripes_bar(doom, bar, sprite_i);
}

static void			add_mist_to_sanitizer(t_doom *doom)
{
	int				diff;

	diff = 0;
	if (doom->own_event.mist == TRUE)
	{
		clock_gettime(doom->game_time, &doom->own_event.sprite_timer);
		doom->own_event.mist = FALSE;
	}
	else
	{
		diff = find_time_difference(doom, doom->own_event.sprite_timer.tv_sec);
		if (diff == 0)
			draw_add_on(doom, doom->player.spraying_hand);
	}
}

void		draw_player_adds(t_doom *doom)
{
	size_t			sprite_i;

	if (doom->player_sprite != set)
		set_player_sprite(doom);
	if (doom->own_event.scissor_lift == TRUE)
	{
		sprite_i = SCISSOR;
		draw_add_on(doom, sprite_i);
	}
	if (doom->own_event.shoot == TRUE)
	{
		add_mist_to_sanitizer(doom);
		sprite_i = doom->player.spray_hand;
		draw_add_on(doom, sprite_i);
		draw_add_on(doom, CROSS_HAIR);
	}
	else if (doom->own_event.select == TRUE)
	{
		if (doom->own_event.hold_x <= WIDTH / 2)
			sprite_i = doom->player.left_select;
		else
			sprite_i = doom->player.right_select;
		draw_add_on(doom, sprite_i);
		draw_add_on(doom, CROSS_HAIR);
	}
}
