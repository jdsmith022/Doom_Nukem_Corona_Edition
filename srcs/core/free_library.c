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

// static void		free_sdl(SDL_Surface **lib, int len)
// {
// 	size_t index;

// 	index = 0;
// 	while (index < len)
// 	{
// 		ft_bzero(lib[index], sizeof(lib[index]));
// 		free(lib[index]);
// 	}
// 	free(lib);
// }

void		free_sdl_lib(t_doom *doom)
{
	SDL_Surface	**lib;

	if (doom->lib.tex_lib)
	{
		lib = doom->lib.tex_lib;
		void_free_lib(lib);
	}
	if (doom->lib.obj_lib)
	{
		lib = doom->lib.obj_lib;
		void_free_lib(lib);
	}
	if (doom->lib.font_lib->font_surface)
	{
		lib = &doom->lib.font_lib->font_surface;
		void_free_lib(lib);
	}
	if (doom->lib.sky_lib)
	{
		lib = doom->lib.sky_lib;
		void_free_lib(lib);
	}
}
