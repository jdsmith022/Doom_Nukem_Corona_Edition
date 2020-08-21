#include "../../includes/doom.h"

static void	check_select_sprite(t_doom *doom)
{
	if (SPRITES[doom->own_event.virus_hit_index].action == 11 && \
	SPRITES[doom->own_event.virus_hit_index].distance < 100.0)
	{
		// printf("index: %d\n", sprite_i);
		doom->own_event.toilet_paper = TRUE;
		doom->own_event.virus_hit_index = -1;
		printf("YOU GOT TOILET PAPER!!!!\n");
	}
	else if (SPRITES[doom->own_event.virus_hit_index].action == 12 \
	&& SPRITES[doom->own_event.virus_hit_index].distance < 100.0)
	{
			// printf("index: %d\n", sprite_i);
			doom->own_event.trolly = TRUE;
			doom->lib.sidedef[17].action = 0;
			doom->own_event.virus_hit_index = -1;
			printf("YOU GOT THE TROLLY!\n");
	}
}

static void check_spray_sprite(t_doom *doom)
{
	if (SPRITES[doom->own_event.virus_hit_index].action == 9 && \
	SPRITES[doom->own_event.virus_hit_index].distance < 100.0)
	{
		doom->own_event.spray_shopper = TRUE;
		doom->lib.font_lib.bools.text = TRUE;
		doom->own_event.virus_hit_index = -1;
		printf("HIT SHOPPER!!!!\n");
	}

}

void	check_select_shoot_sprite(t_doom *doom)
{
	if (doom->own_event.shoot == TRUE)
		check_spray_sprite(doom);
	else if (doom->own_event.select == TRUE)
		check_select_sprite(doom);
}
