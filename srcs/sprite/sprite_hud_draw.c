#include "../../includes/doom.h"
#include "../../includes/hud.h"
#include "../../includes/gameplay.h"
#include "../../includes/sprites.h"

static void		draw_add_on(t_doom *doom, int sprite_i, int right_select)
{
	t_line bar;

	scale_bar(doom, &bar, sprite_i);
	if (sprite_i == right_select || \
	(doom->player_handed == right && doom->own_event.shoot == TRUE))
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

static void			add_mist_to_sanitizer(t_doom *doom, int spraying_hand, int right_select)
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
			draw_add_on(doom, spraying_hand, right_select);
	}
}

static void	set_player_sprite(t_doom *doom, int *spray_hand, int *spraying_hand,
				int *left_select, int *right_select)
{
	printf("doom->sprite: %d -- hand: %d\n", doom->player_sprite, doom->player_handed);
	if (doom->player_sprite == player_1)
	{
		if (doom->player_handed == right)
		{
			*spray_hand = 102;
			*spraying_hand = 108;
		}
		else
		{
			*spray_hand = 103;
			*spraying_hand = 107;
		}
		*left_select = 98;
		*right_select = 99;
	}
	else if (doom->player_sprite == player_2)
	{
		if (doom->player_handed == right)
		{
			*spray_hand = 104;
			*spraying_hand = 110;
		}
		else
		{
			*spray_hand = 105;
			*spraying_hand = 109;
		}
		*left_select = 100;
		*right_select = 101;
	}
	else if (doom->player_sprite == player_3)
	{
		if (doom->player_handed == right)
		{
			*spray_hand = 106;
			*spraying_hand = 111;
		}
		else
		{
			*spray_hand = 29;
			*spraying_hand = 30;
		}
		*left_select = 74;
		*right_select = 75;
	}
	doom->player_sprite = set;
}

void		draw_player_adds(t_doom *doom)
{
	size_t			sprite_i;
	static int		spray_hand;
	static int		spraying_hand;
	static int		left_select;
	static int		right_select;

	if (doom->player_sprite != set)
		set_player_sprite(doom, &spray_hand, &spraying_hand, &left_select, &right_select);
	if (doom->own_event.scissor_lift == TRUE)
	{
		sprite_i = SCISSOR;
		draw_add_on(doom, sprite_i, right_select);
	}
	if (doom->own_event.shoot == TRUE)
	{
		add_mist_to_sanitizer(doom, spraying_hand, right_select);
		sprite_i = spray_hand;
		draw_add_on(doom, sprite_i, right_select);
		draw_add_on(doom, CROSS_HAIR, right_select);
	}
	else if (doom->own_event.select == TRUE)
	{
		if (doom->own_event.hold_x <= WIDTH / 2)
			sprite_i = left_select;
		else
			sprite_i = right_select;
		draw_add_on(doom, sprite_i, right_select);
		draw_add_on(doom, CROSS_HAIR, right_select);
	}
}
