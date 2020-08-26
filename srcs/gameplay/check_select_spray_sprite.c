#include "../../includes/doom.h"
#include "../../includes/hud.h"

static void	check_select_sprite(t_doom *doom)
{
	if (doom->lib.sprites[doom->own_event.virus_hit_index].action == 4)
		doom->own_event.corona_hit = TRUE;
	else if (SPRITES[doom->own_event.virus_hit_index].action == 13)
	{
		doom->own_event.toilet_paper = TRUE;
		SPRITES[doom->own_event.virus_hit_index].action = 8;
	}
	else if (SPRITES[doom->own_event.virus_hit_index].action == 12)
	{
		doom->own_event.trolly = TRUE;
		doom->lib.sidedef[17].action = 0;
		SPRITES[doom->own_event.virus_hit_index].action = 8;
	}
	else if (SPRITES[doom->own_event.virus_hit_index].action == 14)
	{
		printf("Grocery fetched\n");
		printf("With texture index: %d\n", SPRITES[doom->own_event.virus_hit_index].textures[0]);
		SPRITES[doom->own_event.virus_hit_index].action = 15;
	}
}

static void	virus_hit(t_doom *doom)
{
	SPRITES[doom->own_event.virus_hit_index].visible = 17;
	SPRITES[doom->own_event.virus_hit_index].textures[0] = 17;
	SPRITES[doom->own_event.virus_hit_index].textures[1] = 17;
	SPRITES[doom->own_event.virus_hit_index].textures[2] = 17;
	SPRITES[doom->own_event.virus_hit_index].textures[3] = 17;
	SPRITES[doom->own_event.virus_hit_index].action = 5;
	doom->own_event.virus_red_i = doom->own_event.virus_hit_index;
	doom->own_event.virus_red = TRUE;
}

static void	check_spray_sprite(t_doom *doom)
{
	if (SPRITES[doom->own_event.virus_hit_index].action == 4)
		virus_hit(doom);
	else if (SPRITES[doom->own_event.virus_hit_index].action == 9 && \
	SPRITES[doom->own_event.virus_hit_index].distance < 50.0)
	{
		doom->own_event.spray_shopper = TRUE;
		doom->lib.font_lib.bools.text = TRUE;
	}
}

void		check_select_spray_sprite(t_doom *doom)
{
	if (SPRITES[doom->own_event.virus_hit_index].distance < 100.0)
	{
		if (doom->own_event.shoot == TRUE)
			check_spray_sprite(doom);
		else if (doom->own_event.select == TRUE)
			check_select_sprite(doom);
	}
	doom->own_event.virus_hit_index = -1;
}
