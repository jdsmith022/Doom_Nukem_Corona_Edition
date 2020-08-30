#include "../../includes/doom.h"
#include "game_editor.h"

static t_sidedef	*new_level_sidedef(t_doom *doom,\
					t_sidedef *sidedef, int w_len)
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

static t_sprite	*new_level_object(t_doom *doom,\
				t_sprite *object, int o_len)
{
	t_sprite	*new;
	int			i;
	int 		side;

	free(doom->lib.sidedef);
	if (o_len > 0)
	{
		new = (t_sprite*)malloc(sizeof(t_sprite) * (o_len + 1));
		if (new == NULL)
			doom_exit_failure(doom, MALLOC_ERR);
		i = 0;
		while (i < o_len)
		{
			new[i].lines = (t_line*)ft_memalloc(sizeof(t_line) * 4);
			new[i].textures = (int*)ft_memalloc(sizeof(int) * 4);
			new[i] = object[i];
			i++;
		}
		return (new);
	}
	return (NULL);
}

static t_sector	*new_level_sector(t_doom *doom,\
				t_sector *sector, int s_len)
{
	t_sector	*new;
	int			i;

	free(doom->lib.sector);
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

static t_sector	*light_correction(t_sector *sector, int len)
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

void		rmove(t_sprite *sprite, t_doom *doom)
{
	int i;

	i = 0;
	while (i < doom->total_sprites)
	{
		free(sprite[i].lines);
		free(sprite[i].textures);
		i++;
	}
	free(sprite);
}

void		add_to_game(t_doom *doom)
{
	if (doom->game_design.sector != NULL && doom->game_design.w_len > 2)
	{
		if (doom->game_design.pl_x > 0 && doom->game_design.pl_y > 0)
		{
			coor_pos(doom, 0);
			box_in_sectors(doom);
			rmove(doom->lib.sprites, doom);
			doom->lib.sector = new_level_sector(doom,\
				doom->game_design.sector, doom->game_design.s_len + 1);
			doom->lib.sidedef = new_level_sidedef(doom,\
				doom->game_design.sidedef, doom->game_design.w_len + 1);
			doom->lib.sprites = new_level_object(doom,\
				doom->game_design.object, doom->game_design.o_len);
			doom->total_sprites = doom->game_design.o_len;
			doom->lib.sector = light_correction(\
				doom->lib.sector, doom->game_design.s_len);
			doom->pos.x = doom->game_design.pl_x;
			doom->pos.y = doom->game_design.pl_y;
			doom->i_sector = doom->game_design.pl_sec;
			doom->player_height = doom->player_height \
			+ doom->lib.sector[doom->game_design.pl_sec].height_floor;
			doom->light = TRUE;
		}
	}
}
