#include "../../includes/doom.h"
#include "../../includes/game_editor.h"
#include "../../includes/sprites.h"

void	change_texture(t_doom *doom, int *txt, int change)
{
	if (doom->lib.len_tex_lib > *txt + change && *txt + change >= 0)
		doom->game_design.cur_tex += change;
}


// void	object_texture(t_doom *doom, int change)
// {
// 	static int		index;

// 	if (index + change <= LEVEL_SPRITE_LEN && \
// 	index + change >= 0)
// 	{
// 		index += change;
// 		doom->game_design.cur_tex = level_sprites[index].index;
// 		doom->game_design.index_obj = index;
// 		if (doom->game_design.cur_obj >= \
// 		doom->game_design.sector[doom->game_design.cur_sec].i_objects && \
// 		doom->game_design.cur_obj < \
// 		doom->game_design.sector[doom->game_design.cur_sec].i_objects + \
// 		doom->game_design.sector[doom->game_design.cur_sec].n_objects)
// 		{
// 			add_specifications(&(doom->game_design), doom->game_design.cur_obj);
// 			add_obj_lines(doom->game_design.object\
// 				[doom->game_design.cur_obj].pos.x, \
// 				doom->game_design.object[doom->game_design.cur_obj].pos.y,\
// 				doom->game_design, \
// 				&(doom->game_design.object[doom->game_design.cur_obj].lines));
// 		}
// 	}
// }

// void	object_change(t_doom *doom, int change)
// {
// 	if (doom->game_design.cur_obj + change < \
// 	doom->game_design.sector[doom->game_design.cur_sec].i_objects + \
// 	doom->game_design.sector[doom->game_design.cur_sec].n_objects && \
// 	doom->game_design.cur_obj > \
// 	doom->game_design.sector[doom->game_design.cur_sec].i_objects - change)
// 		doom->game_design.cur_obj += change;
// }

void	sidedef_object(t_doom *doom)
{
	doom->game_design.sidedef_bar = doom->game_design.sidedef_bar == 0 ? 1 : 0;
	doom->game_design.object_bar = doom->game_design.object_bar == 1 ? 0 : 1;
}
