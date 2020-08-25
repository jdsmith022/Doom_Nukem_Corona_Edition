
#include "../../includes/doom.h"

static void		free_sld_libs(SDL_Surface **lib, int len)
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

void			free_sdl_lib(t_doom *doom)
{
	SDL_Surface	**lib;
	int			len;

	if (doom->lib.tex_lib)
	{
		lib = doom->lib.tex_lib;
		len = doom->lib.len_tex_lib;
		free_sld_libs(lib, len);
	}
	if (doom->lib.obj_lib)
	{
		lib = doom->lib.obj_lib;
		len = doom->lib.len_obj_lib;
		free_sld_libs(lib, len);
	}
	if (doom->lib.sky_lib)
	{
		lib = doom->lib.sky_lib;
		len = doom->lib.len_sky_lib;
		free_sld_libs(lib, len);
	}
}
