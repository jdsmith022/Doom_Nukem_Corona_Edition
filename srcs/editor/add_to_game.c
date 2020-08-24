#include "../../includes/doom.h"
#include "game_editor.h"

t_sidedef	*new_level_sidedef(t_doom *doom, t_sidedef *sidedef, int w_len)
{
	t_sidedef	*new;
	int			i;

	new = (t_sidedef*)malloc(sizeof(t_sidedef) * w_len);
	if (new == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
	i = 0;
	while (i < w_len)
	{
		new[i] = sidedef[i];
		i++;
	}
	return (new);
}

t_sprite	*new_level_object(t_doom *doom, t_sprite *object, int o_len)
{
	t_sprite	*new;
	int			i;
	int 		side;

	if (o_len > 0)
	{
		new = (t_sprite*)malloc(sizeof(t_sprite) * (o_len + 1));
		if (new == NULL)
			doom_exit_failure(doom, MALLOC_ERR);
		i = 0;
		while (i < o_len)
		{
			// side = 0;
			// while (side < 4)
			// {
			// 	printf("start_x %f start_y %f end_x %f endy %f\n", object[i].lines[side].start.x, object[i].lines[side].start.y, object[i].lines[side].end.x , object[i].lines[side].end.y);
			// 	side++;
			// }
			new[i] = object[i];
			i++;
		}
		return (new);
	}
	return (NULL);
}

t_sector	*new_level_sector(t_doom *doom, t_sector *sector, int s_len)
{
	t_sector	*new;
	int			i;

	new = (t_sector*)malloc(sizeof(t_sector) * (s_len + 1));
	if (new == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
	i = 0;
	while (i <= s_len)
	{
		new[i] = sector[i];
		i++;
	}
	return (new);
}

t_sector	*light_correction(t_sector *sector, int len)
{
	int i;

	i = 0;
	while (i <= len)
	{
		if (sector[i].light_level != 0)
			sector[i].light_level /= 10.0;
		sector[i].light = TRUE;
		i++;
	}
	return (sector);
}

void		add_to_game(t_doom *doom)
{
	if (SECTOR != NULL && EDIT.w_len > 2)
	{
		if (EDIT.pl_x > 0 && EDIT.pl_y > 0)
		{
			coor_pos(doom);
			box_in_sectors(doom);  // give these walls a flag so that they are not drawn if the sector is outside
			free(doom->lib.sector); //rm when there are multiple levels		
			free(doom->lib.sidedef); //rm when there are multiple levels
			free(doom->lib.sprites); //rm when there are multiple levels		
			doom->lib.sector = new_level_sector(doom,\
				SECTOR, EDIT.s_len + 1);
			doom->lib.sidedef = new_level_sidedef(doom,\
				SIDEDEF, EDIT.w_len + 1);
			doom->lib.sprites = new_level_object(doom,\
				OBJECT, EDIT.o_len); //wat moet hier in als er geen sprites zijn
			doom->total_sprites = EDIT.o_len;
			doom->lib.sector = light_correction(\
				doom->lib.sector, EDIT.s_len);
			doom->pos.x = EDIT.pl_x;
			doom->pos.y = EDIT.pl_y;
			doom->i_sector = EDIT.pl_sec;
			doom->player_height = doom->player_height \
			+ doom->lib.sector[EDIT.pl_sec].height_floor;
			doom->light = TRUE;
		}
	}
}
