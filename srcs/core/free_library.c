#include "../../includes/doom.h"

static void		void_free_lib(void *lib)
{
	ft_bzero(lib, sizeof(lib));
	free(lib);
}

static void	free_font_lib(t_doom *doom)
{
	t_font		*font;

	if (doom->lib.game_editor_font)
	{
		font = doom->lib.game_editor_font;
		void_free_lib(font);
	}
	if (doom->lib.hud_font)
	{
		font = doom->lib.hud_font;
		void_free_lib(font);
	}
	//add other font libs to be freed
}

void		free_struct_lib(t_doom *doom)
{
	t_sector	*sector;
	t_sidedef	*sidedef;
	t_sprite	*sprites;

	if (doom->lib.sector)
	{
		sector = doom->lib.sector;
		void_free_lib(sector);
	}
	if (doom->lib.sidedef)
	{
		sidedef = doom->lib.sidedef;
		void_free_lib(sidedef);
	}
	if (doom->lib.sprites)
	{
		sprites = doom->lib.sprites;
		void_free_lib(sprites);
	}
	free_font_lib(doom);
}

static void		free_sld_lib(SDL_Surface **lib, int len)
{
	size_t index;

	index = 0;
	while (index < len)
	{
		ft_bzero(lib[index], sizeof(lib[index]));
		free(lib[index]);
		index++;
	}
	free(lib);
}

void		free_sdl_lib(t_doom *doom)
{
	SDL_Surface	**lib;
	int			len;

	if (doom->lib.tex_lib)
	{
		lib = doom->lib.tex_lib;
		len = doom->lib.len_tex_lib;
		free_sld_lib(lib, len);
	}
	if (doom->lib.obj_lib)
	{
		lib = doom->lib.obj_lib;
		len = doom->lib.len_obj_lib;
		free_sld_lib(lib, len);
	}
	if (doom->lib.sky_lib)
	{
		lib = doom->lib.sky_lib;
		len = doom->lib.len_sky_lib;
		free_sld_lib(lib, len);
	}
}
