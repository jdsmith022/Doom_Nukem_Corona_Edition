#include "../../includes/doom.h"
#include "../../includes/game_editor.h"
#include "../../includes/sprites.h"
#include "../../includes/render.h"

static void	set_points_textures(t_doom *doom, t_point *i,
				t_point *change, SDL_Surface *texture)
{
	change->x = (double)texture->w / 48.0;
	change->y = (double)texture->h / 48.0;
	i->x = 0;
	i->y = 0;
}

void		put_textures_sidedef(int x, int y, int index, t_doom *doom)
{
	int				save_x;
	Uint32			shift;
	t_point			i;
	t_point			change;
	SDL_Surface		*texture;

	save_x = x;
	index = doom->game_design.sd_tex_index[doom->game_design.tex_index];
	texture = doom->lib.tex_lib[index];
	shift = texture->format->BitsPerPixel == 24 ? 3 : 4;
	set_points_textures(doom, &i, &change, texture);
	while ((int)i.y < texture->h)
	{
		put_texture(doom, (Uint32)index, (Uint32)((y * WIDTH + x) * 4),\
		(Uint32)(((int)i.y * texture->w + (int)i.x) * shift));
		x++;
		i.x += change.x;
		if ((int)i.x >= texture->w)
		{
			x = save_x;
			y++;
			i.x = 0;
			i.y += change.y;
		}
	}
}

static void	set_points_images(t_doom *doom, t_point *i,
				t_point *change, int index)
{
	change->x = (double)doom->game_design.sym_lib[index]->w / 32.0;
	change->y = (double)doom->game_design.sym_lib[index]->h / 32.0;
	i->x = 0;
	i->y = 0;
}

void		put_images(int x, int y, int index, t_doom *doom)
{
	int		save_x;
	Uint32	shift;
	t_point i;
	t_point change;

	save_x = x;
	shift =\
		doom->game_design.sym_lib[index]->format->BitsPerPixel == 24 ? 3 : 4;
	set_points_images(doom, &i, &change, index);
	while ((int)i.y < doom->game_design.sym_lib[index]->h)
	{
		put_symbol(doom, (Uint32)index, (Uint32)((y * WIDTH + x) * 4),\
		(Uint32)(((int)i.y *\
			doom->game_design.sym_lib[index]->w + (int)i.x) * shift));
		x++;
		i.x += change.x;
		if ((int)i.x >= doom->game_design.sym_lib[index]->w)
		{
			x = save_x;
			y++;
			i.x = 0;
			i.y += change.y;
		}
	}
}
