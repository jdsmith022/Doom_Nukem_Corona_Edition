#include "../../includes/doom.h"
#include "../../includes/hud.h"
#include "../../includes/gameplay.h"

static void	check_select_sprite(t_doom *doom)
{
	if (doom->lib.sprites[doom->own_event.virus_hit_index].action == 4)
		doom->own_event.corona_hit = TRUE;
	else if (doom->lib.sprites[doom->own_event.virus_hit_index].action == 13)
	{
		doom->own_event.toilet_paper = TRUE;
		doom->lib.sprites[doom->own_event.virus_hit_index].action = 8;
	}
	else if (doom->lib.sprites[doom->own_event.virus_hit_index].action == 12)
	{
		doom->own_event.trolly = TRUE;
		doom->lib.sidedef[17].action = 0;
		doom->lib.sprites[doom->own_event.virus_hit_index].action = 8;
	}
	else if (doom->lib.sprites[doom->own_event.virus_hit_index].action == 14)
	{
		printf("Grocery fetched\n");
		printf("With texture index: %d\n", doom->lib.sprites[doom->own_event.virus_hit_index].textures[0]);
		uint8_t type = *(int *)doom->lib.obj_lib[doom->lib.sprites[doom->own_event.virus_hit_index].textures[0]]->userdata;
		doom->lib.sprites[doom->own_event.virus_hit_index].action = 15;
		printf("%d\n", type);
		add_item_to_basket(doom, &doom->groceries->basket, type);
		set_positions(&doom->groceries->basket);
	}
}

static void	virus_hit(t_doom *doom)
{
	doom->lib.sprites[doom->own_event.virus_hit_index].visible = 17;
	doom->lib.sprites[doom->own_event.virus_hit_index].textures[0] = 17;
	doom->lib.sprites[doom->own_event.virus_hit_index].textures[1] = 17;
	doom->lib.sprites[doom->own_event.virus_hit_index].textures[2] = 17;
	doom->lib.sprites[doom->own_event.virus_hit_index].textures[3] = 17;
	doom->lib.sprites[doom->own_event.virus_hit_index].action = 5;
	doom->own_event.virus_red_i = doom->own_event.virus_hit_index;
	doom->own_event.virus_red = TRUE;
}

static void	check_spray_sprite(t_doom *doom)
{
	if (doom->lib.sprites[doom->own_event.virus_hit_index].action == 4)
		virus_hit(doom);
	else if (doom->lib.sprites[doom->own_event.virus_hit_index].action == 9 && \
	doom->lib.sprites[doom->own_event.virus_hit_index].distance < 50.0)
	{
		doom->own_event.spray_shopper = TRUE;
		doom->lib.font_lib.bools.text = TRUE;
	}
}

void		check_select_spray_sprite(t_doom *doom)
{
	if (doom->lib.sprites[doom->own_event.virus_hit_index].distance < 100.0)
	{
		if (doom->own_event.shoot == TRUE)
			check_spray_sprite(doom);
		else if (doom->own_event.select == TRUE)
			check_select_sprite(doom);
	}
	doom->own_event.virus_hit_index = -1;
}
