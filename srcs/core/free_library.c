#include "../../includes/doom.h"

static void		void_free_lib(void *lib)
{
	ft_bzero(lib, sizeof(lib));
	free(lib);
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
	// if (doom->lib.font_lib->font_surface)
	// {
	// 	lib = &doom->lib.font_lib->font_surface;
	// 	len = doom->lib.len_font_lib;
	// 	free_sld_lib(lib, len);
	// }
	if (doom->lib.sky_lib)
	{
		lib = doom->lib.sky_lib;
		len = doom->lib.len_sky_lib;
		free_sld_lib(lib, len);
	}
}
