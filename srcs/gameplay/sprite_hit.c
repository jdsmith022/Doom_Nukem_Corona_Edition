#include "../../includes/doom.h"
#include "../../includes/gameplay.h"
#include "../../includes/hud.h"
#include "../../includes/font.h"
#include "../../includes/sprites.h"

static void		check_hit_new(t_doom *doom)
{
	int			i;

	i = doom->visible_sprites -1;
	while (i >= 0)
	{
		if (doom->lib.sprites[doom->lib.sprite_order[i]].distance < 150 &&\
		sprite_has_action(doom->lib.sprites[doom->lib.sprite_order[i]]) &&\
		sprite_in_shooting_area(doom, doom->lib.sprite_order[i]) != -1)
			doom->own_event.virus_hit_index = doom->lib.sprite_order[i];
		i--;
	}
}

void			check_sprite_hit(t_doom *doom)
{
	t_ray	ray;

	check_hit_new(doom);
	if (doom->own_event.virus_hit_index != -1)
		check_select_spray_sprite(doom);
	doom->own_event.virus_hit_index = -1;
}
